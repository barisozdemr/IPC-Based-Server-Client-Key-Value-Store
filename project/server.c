#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#include "kv_store.h"

#define SOCKET_PATH "/tmp/kv_socket"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void log_message(const char* msg) {
    FILE* fp = fopen("server.log","a");
    if (!fp) return;
    time_t t = time(NULL);
    char* ts = ctime(&t);
    ts[strlen(ts)-1] = '\0';
    fprintf(fp, "[%s] %s\n", ts, msg);
    fclose(fp);
}

void* client_handler(void* arg)
{
    int client = *(int*)arg;
    free(arg);

    char buffer[1024];
    int n = read(client,buffer,sizeof(buffer)-1);

    if(n <= 0)
    {
        close(client);
        return NULL;
    }

    buffer[n]='\0';

    char response[32768];

    pthread_mutex_lock(&mutex);

    if(strncmp(buffer,"SET",3)==0)
    {
        char key[64];
        char value[256];

        sscanf(buffer,"SET %63s %255[^\n]",key,value);

        kv_set(key,value);
        kv_save();

        strcpy(response,"OK\n");
    }
    else if(strncmp(buffer,"GET",3)==0)
    {
        char key[64];

        sscanf(buffer,"GET %63s",key);

        if(kv_get(key,response))
            strcat(response,"\n");
        else
            strcpy(response,"NOT FOUND\n");
    }
    else if(strncmp(buffer,"DELETE",6)==0)
    {
        char key[64];

        sscanf(buffer,"DELETE %63s",key);

        if(kv_delete(key))
        {
            kv_save();

            strcpy(response,"DELETED\n");
        }
        else
            strcpy(response,"NOT FOUND\n");
    }
    else if(strncmp(buffer,"LIST",4)==0)
    {
        kv_list(response);
    }
    else
    {
        strcpy(response,"INVALID COMMAND\n");
    }

    pthread_mutex_unlock(&mutex);

    log_message(buffer);

    write(client,response,strlen(response));

    close(client);

    return NULL;
}

int main()
{
    int server_fd, client_fd;

    struct sockaddr_un addr;

    unlink(SOCKET_PATH);

    kv_init();
    kv_load();

    server_fd = socket(AF_UNIX,SOCK_STREAM,0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,SOCKET_PATH);

    bind(server_fd,(struct sockaddr*)&addr,sizeof(addr));

    listen(server_fd,10);

    printf("Server running...\n");

    while(1)
    {
        client_fd = accept(server_fd,NULL,NULL);

        int* pclient = malloc(sizeof(int));
        *pclient = client_fd;

        pthread_t tid;

        pthread_create(&tid,NULL,client_handler,pclient);
        pthread_detach(tid);
    }

    close(server_fd);

    return 0;
}