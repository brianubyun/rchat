#!/bin/sh
#this script just runs 100 clients, the point is to test if sockets are properly getting closed. it could also be expanded to stress test the server, which is why I'm committing it.
clear
pause_duration=0.1
for i in {1..100}; do
    echo "Running exe $i"
    ./client_run <<EOF &
    1
    test
    test
    $i
EOF
    #sleep $pause_duration    
done
exit 0