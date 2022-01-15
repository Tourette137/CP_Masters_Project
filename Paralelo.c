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
#include <string.h>

// Array size
int NARRAY;

// Number of buckets
int NBUCKET = 100;

// Each bucket capacity
int INTERVAL;

// 0 -> INSERTION_SORT | 1 -> QUICK_SORT
int METHOD;

// See if it is Parallel (1) or Squential (0)
int SEQ_PAR;

// Puts how many threads wants
int OMP_NUM_THREADS;

void printResult (double secondsArray, double secondsSort, int* array, int max_number);
// ./Paralelo quickSort tamanhoArray maximoArray nBuckets nrThreads 


// Driver code
int main (int argc, char **argv) {

    if (argc < 6) {
        // Does nothing
        printf("\e[1;91mNOT ENOUGH ARGUMENTS!\e[0m\n");
        return -1;
    }
        

    // Definir como sendo Paralelo
    SEQ_PAR = 1;

    // Definir método utilizado no sort de cada Bucket
    if (!strcmp(argv[1], "insertionSort"))
        METHOD = 0;
    else if (!strcmp(argv[1], "quickSort"))
        METHOD = 1;
    else if (!strcmp(argv[1], "bubbleSort"))
        METHOD = 2;

    // Definir tamanho máximo do Array
    NARRAY = atoi(argv[2]);

    // Definir número máximo dos inteiros que array tem
    int max_number = atoi(argv[3]);

    // Definir número de Buckets
    NBUCKET = atoi(argv[4]);

    // Definir número de Threads
    OMP_NUM_THREADS = atoi(argv[5]);

    
    
    // Criar o array dos números
    double startArray = omp_get_wtime();

    int *array = (int*) malloc(NARRAY * sizeof(int));

    for (int a = 0; a < NARRAY; a++) 
        array[a] = rand() % max_number;
    
    double endArray = omp_get_wtime();

    double secondsArray = (double)(endArray - startArray);


    // Descobrir o maior elemento
    int largestNumber = largest(array, NARRAY);
    //printf("Largest number was %d\n", largestNumber);

    // Definir o intervalo do array
    if ((largestNumber % NBUCKET) != 0) {
        INTERVAL = largestNumber/NBUCKET + 1;
    } else {
        INTERVAL = largestNumber/NBUCKET;
    }

    // Ver se é necessário acrescentar um bucket ou um interval
    if ((largestNumber % NBUCKET) == 0) {
        if (NBUCKET >= INTERVAL)
            NBUCKET++;
        else
            INTERVAL++;
    }

    // Bucket Sort
    double startSort = omp_get_wtime();

    BucketSort(array);
    
    double endSort = omp_get_wtime();
    double secondsSort = (double)(endSort - startSort);

    // Print result
    printResult(secondsArray, secondsSort, array, max_number);

    return 0;
}

void printResult (double secondsArray, double secondsSort, int* array, int max_number) {

    printf("\n\e[1;96m EXECUTION TYPE: \e[0m PARALLEL\n");

    switch (METHOD) {
        case 0:
            printf("\e[1;95m \tSort type of each Bucket: \e[0m Insertion Sort\n");
            break;
        case 1:
            printf("\e[1;95m \tSort type of each Bucket: \e[0m Quick Sort\n");
            break;
        case 2:
            printf("\e[1;95m \tSort type of each Bucket: \e[0m Bubble Sort\n");
            break;
    }
    
    printf("\e[1;95m \tSize of Array: \e[0m %d\n", NARRAY);

    printf("\e[1;95m \tLargest Size possible of Integer in Array: \e[0m %d\n", max_number);

    printf("\e[1;95m \tNumber of Buckets: \e[0m %d\n", NBUCKET);

    printf("\e[1;95m \tInterval of each Bucket: \e[0m %d\n", INTERVAL);

    printf("\e[1;95m \tNumber of Threads: \e[0m %d\n\n", OMP_NUM_THREADS);

    switch(isArraySorted(array, NARRAY)) {
        case 1:
            printf(" The array is sorted in ascending order.\n\n");
            printf("\e[1;96m ARRAY CREATION TIME: \e[0m %f seconds\n", secondsArray);
            printf("\e[1;96m BUCKET SORT TIME: \e[0m %f seconds\n", secondsSort);
            break;
        case 2:
            printf(" The array is sorted in descending order.\n\n");
            printf("\e[1;96m ARRAY CREATION TIME: \e[0m %f seconds\n", secondsArray);
            printf("\e[1;96m BUCKET SORT TIME: \e[0m %f seconds\n", secondsSort);
            break;
        case 0:
            printf(" The array is not sorted!!!\n");
            break;
    }

}