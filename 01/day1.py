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
print(list1)
print(list2)

#Data Array in 
array1 = np.array(list1, dtype=np.int32)
array2 = np.array(list2, dtype=np.int32)


#void quicksort_wrapper(int* array, int size)
lib.quicksort_wrapper(array1.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array1))
lib.quicksort_wrapper(array2.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array2))
print("Sortiertes Array1:", array1)
print("Sortiertes Array2:", array2)
#int calculate_wrapper(int* arr1, int size_arr1, int* arr2, int size_arr2)
distance = lib.calculate_wrapper(array1.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array1), array2.ctypes.data_as(ctypes.POINTER(ctypes.c_int)), len(array2))
print("Calculated distance:",distance)
