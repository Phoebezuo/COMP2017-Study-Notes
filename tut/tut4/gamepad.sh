#/bin/bash


gcc gamepad.c -o gamepad -std=c99

# Creates a unidirectional pipe, write from ./device and read from ./controller
socat pty,raw,echo=0,link=./controller0 pty,raw,echo=0,link=./device0 &

#Saves the pid out
echo $! > socat_pid

#Sleeps and allows for it be set up (Ed only issue)
sleep 1

#Runs the gamepad 
./gamepad ./device0 $1
kill -HUP $(cat socat_pid)
rm socat_pid

