#include <stdio.h>

extern int* quickSort(int* inArray, int size, int start, int end);

void quicksort_wrapper(int* array, int size)
{
    quickSort(array, size, 0, size-1);
}