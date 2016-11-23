#!/bin/sh
#This is a sample Born shell script.
echo "the name of the script is $0"
echo "the first argument is $1"
echo "a list of all the argument is $*"
echo "the script places the date into a temporary file called $1.$$"
date > $1.$$ #redirect the output of date
