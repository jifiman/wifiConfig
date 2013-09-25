#!/bin/bash
set -x
#install hostapd and dhcp server
sudo apt-get -y install hostapd isc-dhcp-server

#configure isc-dhcp-server
if [ 'diff /etc/default/isc-dhcp-server isc-dhcp-server' ];then
	mv /etc/default/isc-dhcp-server /etc/default/isc-dhcp-server.ORIG
	cp isc-dhcp-server /etc/default/isc-dhcp-server  
	echo "isc-dhcp-server settings modified!"
fi
if [ 'diff /etc/dhcp/dhcpd.conf dhcpd.conf' ];then
	mv /etc/dhcp/dhcpd.conf /etc/dhcp/dhcpd.conf.ORIG
	cp dhcpd.conf /etc/dhcp/dhcpd.conf  
	echo "isc-dhcp-server settings modified!"
fi



