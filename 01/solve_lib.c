#include <stdio.h>

extern int* quickSort(int* inArray, int size, int start, int end);
extern long calcDistance(int* inArray1, int size_array1, int* inArray2, int size_array2);
extern long calcSimularities(int* inArray1, int* inArray2, int size);

void quicksort_wrapper(int* array, int size)
{
    quickSort(array, size, 0, size-1);
    
}

int calculate_wrapper(int* arr1, int size_arr1, int* arr2, int size_arr2)
{
    long res = calcDistance(arr1, size_arr1, arr2, size_arr2);
    return res;
}


int calculate_simularities_wrapper(int* arr1, int* arr2, int size)
{
    long res = calcSimularities(arr1, arr2, size);
    return res;
}

/*
in case Assembly is to confusing:
int simularity(int* arr1, int* arr2, int size)
{
    int counter1 = 0;
    int counter2 = 0;
    int sum = 0;
    while (counter1 < size && counter2 < size)
    {
        while (arr1[counter1] != arr2[counter2] && counter1 < size && counter2 < size)
        {
            if (arr1[counter1] < arr2[counter2])
            {
                counter1++;
            }
            else
            {
                counter2++;
            }
        }
        //count the elements in
        int count = 0;
        if (arr1[counter1] == arr2[counter2])
        {
            int element_to_count = arr1[counter1];
            while (arr1[counter1] == element_to_count && counter1 < size)
            {
                counter1++;
                count++;
            }
            while (arr2[counter2] == element_to_count && counter2 < size)
            {
                sum += element_to_count * count;
                counter2++;
            }
        }
    }

    return sum;
}
*/