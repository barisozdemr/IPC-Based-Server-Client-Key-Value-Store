#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/kv_socket"

int main()
{
    while (1)
    {
        int sock = socket(AF_UNIX, SOCK_STREAM, 0);

        struct sockaddr_un addr;
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, SOCKET_PATH);

        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            return 1;
        }

        char command[1024];

        printf("> ");

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        if (strncmp(command, "EXIT", 4) == 0)
        {
            close(sock);
            break;
        }

        write(sock, command, strlen(command));

        char response[2048];
        int n = read(sock, response, sizeof(response)-1);

        if (n > 0)
        {
            response[n] = '\0';
            printf("%s", response);
        }

        close(sock);
    }

    return 0;
}