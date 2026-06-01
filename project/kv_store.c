#include <stdio.h>
#include <string.h>
#include "kv_store.h"

#define DATA_FILE "database.txt"

static Entry store[MAX_ENTRIES];

void kv_init() {
    memset(store, 0, sizeof(store));
}

void kv_set(const char* key, const char* value) {

    for(int i=0;i<MAX_ENTRIES;i++) {
        if(store[i].used && strcmp(store[i].key,key)==0) {
            strcpy(store[i].value,value);
            return;
        }
    }

    for(int i=0;i<MAX_ENTRIES;i++) {
        if(!store[i].used) {
            store[i].used=1;
            strcpy(store[i].key,key);
            strcpy(store[i].value,value);
            return;
        }
    }
}

int kv_get(const char* key, char* result) {

    for(int i=0;i<MAX_ENTRIES;i++) {
        if(store[i].used && strcmp(store[i].key,key)==0) {
            strcpy(result,store[i].value);
            return 1;
        }
    }

    return 0;
}

int kv_delete(const char* key) {

    for(int i=0;i<MAX_ENTRIES;i++) {
        if(store[i].used && strcmp(store[i].key,key)==0) {
            store[i].used=0;
            return 1;
        }
    }

    return 0;
}

void kv_list(char* buffer) {

    buffer[0]='\0';

    for(int i=0;i<MAX_ENTRIES;i++) {
        if(store[i].used) {
            strcat(buffer,store[i].key);
            strcat(buffer,"=");
            strcat(buffer,store[i].value);
            strcat(buffer,"\n");
        }
    }
}


void kv_load()
{
    FILE* fp = fopen(DATA_FILE, "r");

    if (!fp)
        return;

    char key[KEY_SIZE];
    char value[VALUE_SIZE];

    while (fscanf(fp, "%63s %255[^\n]\n", key, value) == 2)
    {
        kv_set(key, value);
    }

    fclose(fp);
}


void kv_save()
{
    FILE* fp = fopen(DATA_FILE, "w");

    if (!fp)
        return;

    for (int i = 0; i < MAX_ENTRIES; i++)
    {
        if (store[i].used)
        {
            fprintf(fp, "%s %s\n",
                    store[i].key,
                    store[i].value);
        }
    }

    fclose(fp);
}