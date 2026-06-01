setup:
1-bash: make
2-
    terminal1:
        bash: ./server
    terminal2:
        bash: ./client

on terminal2:
    SET <key> <value>
    GET <key>
    DELETE <key>
    LIST
