#!/bin/bash

for i in $(ls *.m)
do
	octave $i
done
