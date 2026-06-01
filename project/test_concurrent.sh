#!/bin/bash
./client <<< "SET key1 hello" &
./client <<< "SET key2 world" &
wait
./client <<< "LIST"