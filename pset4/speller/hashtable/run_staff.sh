#!/bin/bash

for f in ../texts/*
do
	echo $f
	~cs50/2019/x/pset4/speller ../dictionaries/large $f | tail -n 10
done