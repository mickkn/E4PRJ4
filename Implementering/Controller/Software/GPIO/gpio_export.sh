#!/bin/sh

gpio unexportall	# Remove all
gpio export 17 in	# Manuel start
gpio mode 17 down	# Internal pull down - active high 
gpio export 22 in	# On/Off
gpio mode 22 down	# Internal pull down - active high
gpio export 14 out	# LED on/off 
gpio mode 14 up		# Internal pull up - active low
gpio export 15 out	# LED wifi
gpio mode 15 up     # Internal pull up - active low
gpio export 18 out	# LED manuel
gpio mode 18 up     # Internal pull up - active low
