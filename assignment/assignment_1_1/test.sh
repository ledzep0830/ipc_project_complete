#!/bin/sh

for ((i=0; i<1000000; i++)); do
	./producer 0 1 & ./producer 0 1
done
