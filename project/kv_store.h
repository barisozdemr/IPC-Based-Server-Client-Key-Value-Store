#ifndef KV_STORE_H
#define KV_STORE_H

#define MAX_ENTRIES 100
#define KEY_SIZE 64
#define VALUE_SIZE 256

typedef struct {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
    int used;
} Entry;

void kv_init();
void kv_set(const char* key, const char* value);
int kv_get(const char* key, char* result);
int kv_delete(const char* key);
void kv_list(char* buffer);
void kv_save();
void kv_load();

#endif