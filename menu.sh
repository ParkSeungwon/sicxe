#!/bin/sh
echo menu test program
stop=0
while test $stop -eq 0
do
	echo -n 'your choice?'
	read reply
	echo
	case $reply in
		"1")
			date
			;;
		"2")
			stop=1
			;;
		*)
			echo illegal choice
			;;
	esac
done
		
