#include <stdio.h>

extern int* quickSort(int* inArray, int size, int start, int end);
extern long calcDistance(int* inArray1, int size_array1, int* inArray2, int size_array2);

void quicksort_wrapper(int* array, int size)
{
    quickSort(array, size, 0, size-1);
    
}

int calculate_wrapper(int* arr1, int size_arr1, int* arr2, int size_arr2)
{
    long res = calcDistance(arr1, size_arr1, arr2, size_arr2);
    return res;
}
