all:
        gcc server.c kv_store.c -o server -lpthread
        gcc client.c -o client

clean:
        rm -f server client
        rm -f /tmp/kv_socket