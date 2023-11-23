#!/bin/sh
#this script just runs 100 clients, the point is to test if sockets are properly getting closed. it could also be expanded to stress test the server, which is why I'm committing it.
clear
pause_duration=0.1
for i in {1..100}; do
    echo "Running exe $i"
    ./client_run &
    printf '1\ntest\ntest\n'
    sleep "$pause_duration"
    client_pid=$!
    kill $client_pid
    printf '\n'
    
done
exit 0