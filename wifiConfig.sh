#!/bin/bash
#set -x
#install hostapd and dhcp server
if ! dpkg -s hostapd | grep "install ok installed" >/dev/null; then
sudo apt-get -y install hostapd
fi

if ! dpkg -s isc-dhcp-server | grep "install ok installed" >/dev/null; then
	sudo apt-get -y install isc-dhcp-server
fi
#configure isc-dhcp-server
if ! diff /etc/default/isc-dhcp-server isc-dhcp-server>/dev/null;then
	mv /etc/default/isc-dhcp-server /etc/default/isc-dhcp-server.ORIG
	cp isc-dhcp-server /etc/default/isc-dhcp-server  
	echo "isc-dhcp-server settings modified!"
fi

if ! diff /etc/dhcp/dhcpd.conf dhcpd.conf>/dev/null ;then
	mv /etc/dhcp/dhcpd.conf /etc/dhcp/dhcpd.conf.ORIG
	cp dhcpd.conf /etc/dhcp/dhcpd.conf  
	echo "isc-dhcp-server settings modified!"
fi



