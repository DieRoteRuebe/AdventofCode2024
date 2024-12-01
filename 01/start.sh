#!bin/bash

gcc -c -fPIC -o solve_lib.o solve_lib.c -march=native
as -o QuicksortASM.o QuicksortASM.s --64
as -o Calculate_Distance.o Calculate_Distance.s --64
as -o Calculate_Simularities.o Calculate_Simularities.s --64
gcc -shared -o solve_lib.so solve_lib.o QuicksortASM.o Calculate_Distance.o Calculate_Simularities.o
python3 day1.py

