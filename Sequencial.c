// Bucket sort in C
#include "include/BucketSort.h"
#include "include/BubbleSort.h"
#include "include/InsertionSort.h"
#include "include/QuickSort.h"
#include "include/Utils.h"
#include "include/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Array size
int NARRAY = 1000000;

// Number of buckets
int NBUCKET = 100;

// Each bucket capacity
int INTERVAL;

// 0 -> INSERTION_SORT | 1 -> QUICK_SORT
int METHOD = 1;

// See if it is Parallel (1) or Squential (0)
int SEQ_PAR;

// Puts how many threads wants
int OMP_NUM_THREADS = 4;

// Driver code
int main (void) {
    
    // Definir como sendo Paralelo
    SEQ_PAR = 0;

    // Número máximo dos inteiros que array tem
    int max_number = 100000;
    
    // Criar o array dos números
    double startArray = omp_get_wtime();

    int *array = (int*) malloc(NARRAY * sizeof(int));

    for (int a = 0; a < NARRAY; a++) 
        array[a] = rand() % max_number;
    
    double endArray = omp_get_wtime();

    double secondsArray = (double)(endArray - startArray);
    printf("It took %f seconds to create the new array \n", secondsArray);


    // Descobrir o maior elemento
    int largestNumber = largest(array, NARRAY);
    printf("Largest number was %d\n", largestNumber);

    // Definir o intervalo do array
    if ((largestNumber % NBUCKET) != 0) {
        INTERVAL = largestNumber/NBUCKET + 1;
    } else {
        INTERVAL = largestNumber/NBUCKET;
    }

    printf("Interval set to %d\n", INTERVAL);

    // Ver se é necessário acrescentar um bucket ou um interval
    if ((largestNumber % NBUCKET) == 0) {
        if (NBUCKET >= INTERVAL)
            NBUCKET++;
        else
            INTERVAL++;
    }

    printf("Size of initial array: %d\n\n", NARRAY);

    printf("Initial array: ");
    //print(array);
    printf("-------------\n");

    double startSort = omp_get_wtime();

    BucketSort(array);
    
    double endSort = omp_get_wtime();
    double secondsSort = (double)(endSort - startSort);

    printf("-------------\n");
    printf("Sorted array: ");
    //print(array);

    //printf("\nSize of final array: %ld\n", sizeof(array)/sizeof(int) );

    //switch(isArraySorted(array, sizeof(array)/sizeof(int)) ) {
    
    switch(isArraySorted(array, NARRAY)) {
        case 1:
            printf("The array is sorted in ascending order.\n");
            printf("BucketSort() took %f seconds to sort the array \n", secondsSort);
            break;
        case 2:
            printf("The array is sorted in descending order.\n");
            printf("BucketSort() took %f seconds to sort the array \n", secondsSort);
            break;
        case 0:
            printf("The array is not sorted.\n");
            break;
    }

    return 0;
}