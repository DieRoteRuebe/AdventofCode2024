#!bin/bash

gcc -c -fPIC -o quicksort.o quicksort.c -march=native
as -o QuicksortASM.o QuicksortASM.s --64
gcc -shared -o quicksort.so quicksort.o QuicksortASM.o
python3 day1.py

