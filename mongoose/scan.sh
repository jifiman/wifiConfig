#!/bin/bash
ifconfig wlan0 down
ifconfig wlan0 up
iwlist wlan0 scan 2>/dev/null | awk '/ESSID:/ {split($0,a,"\""); print a[2]}' 

