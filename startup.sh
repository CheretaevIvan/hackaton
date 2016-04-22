#!/bin/bash

cd /home/root

# configure PIN3 as GPIO OUPUT (TRIG signal)
./init_DIG.sh -o 3 -d output

# configure PIN4 as GPIO INPUT (ECHO signal)
./init_DIG.sh -o 4 -d input

python show_distance.py