import ctypes
import numpy as np

lib = ctypes.CDLL('./solve_lib.so')
file = open("input.txt", "r")


lib.quicksort_wrapper.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]

list1 = []
list2 = []

for line in file:
    line = line.rstrip("\n")
    arr = line.split("   ")
    list1.append(int(arr[0]))
    list2.append(int(arr[1])) 

file.close()

#Change the py arr into numpy arr -> Memorylayout needs to be contagious
array1 = np.array(list1, dtype=np.int32)
array2 = np.array(list2, dtype=np.int32)


#invoke quicksort of solve_lib.c
lib.quicksort_wrapper(array1.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array1))
lib.quicksort_wrapper(array2.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array2))
print("Sortiertes Array1:", array1)
print("Sortiertes Array2:", array2)
#invoke calculateDistance of solve_lib.c
distance = lib.calculate_wrapper(array1.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array1), array2.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array2))
print("Calculated distance:",distance)
#invoke calcSimularity of solve_lib.c
#retval = lib.simularity(array1.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), array2.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array1))
retval2 = lib.calculate_simularities_wrapper(array1.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), array2.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array1))
#print(retval)
print(retval2)
