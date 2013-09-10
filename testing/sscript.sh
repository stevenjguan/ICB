#! /bin/bash
#Sync Startup
LOG_DIR=/home/root/testing

echo "Initializing network."
modprobe libertas_sdio
ifdown wlan0
ifup wlan0
echo "Network ready."
cd $LOG_DIR
sudo nice --adjustment -20 ./adhoc 4444 > startuplog.txt
echo "Synchronization algorithm done. Starting netcat file transfer."
nc -v -l -p 5555 < startuplog.txt
exit
