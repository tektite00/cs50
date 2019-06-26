#!/bin/bash

for f in ../texts/*
do
	echo $f
	./speller $f | tail -n 10
done
