#!/bin/bash

a=0
b=1
echo -n "Enter no of terms: "
read n

for((i=0;i<n;i++))
do
	echo -n "$a "

	c=$((a+b))
	a=$b
	b=$c
done
echo
