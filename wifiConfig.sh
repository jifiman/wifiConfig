#!/bin/bash
#set -x
DEVICE=wlan0

CheckPackages()
{	#install hostapd and dhcp server
	if ! dpkg -s hostapd | grep "install ok installed" >/dev/null; then
	sudo apt-get -y install hostapd
	fi

	if ! dpkg -s isc-dhcp-server | grep "install ok installed" >/dev/null; then
		sudo apt-get -y install isc-dhcp-server
	fi
}
ConfigureDhcp()
{
	#configure isc-dhcp-server
	if ! diff /etc/default/isc-dhcp-server isc-dhcp-server;then
		sudo mv /etc/default/isc-dhcp-server /etc/default/isc-dhcp-server.ORIG
		sudo cp isc-dhcp-server /etc/default/isc-dhcp-server  
		echo "isc-dhcp-server settings modified!"
	fi

	if ! diff /etc/dhcp/dhcpd.conf dhcpd.conf;then
		sudo mv /etc/dhcp/dhcpd.conf /etc/dhcp/dhcpd.conf.ORIG
		sudo cp dhcpd.conf /etc/dhcp/dhcpd.conf  
		echo "isc-dhcp-server settings modified!"
	fi
}
ConfigureDevice()
{
	if ! sudo iwconfig 2>/dev/null | grep $DEVICE >/dev/null;then
	echo $DEVICE not found!
	exit 1
	fi
	sudo service isc-dhcp-server stop
	sudo pkill hostapd
	sudo ifconfig $DEVICE down
	sudo ifconfig $DEVICE up 192.168.1.100 netmask 255.255.255.0
	#sleep 2
	sudo service isc-dhcp-server start
	sudo hostapd ./hostapd.conf
		
}
CheckPackages
ConfigureDhcp
ConfigureDevice




