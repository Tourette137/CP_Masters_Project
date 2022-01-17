#include "include/BucketSort.h"
#include "include/QuickSort.h"
#include "include/InsertionSort.h"
#include "include/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Sorting function
void BucketSort(int arr[]) {

    if (SEQ_PAR) {
        // Definir o número de Threads incial
        omp_set_num_threads(OMP_NUM_THREADS);
    }

    int i, j;
    struct Node **buckets;

    // Create buckets and allocate memory size
    buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

    if (SEQ_PAR)
        inicializaSequencialmente(buckets);
    else
        inicializaParalelamente(buckets);


    // Fill the buckets with respective elements
    for (i = 0; i < NARRAY; ++i) {
        struct Node *current;
        int pos = getBucketIndex(arr[i]);
        current = (struct Node *)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    // Sort the elements of each bucket
    if (SEQ_PAR)
        ordenaParalelamente(buckets);
    else
        ordenaSequencialmente(buckets);

    // Put sorted elements on arr
    for (j = 0, i = 0; i < NBUCKET; ++i) {
        struct Node *node;
        node = buckets[i];
        while (node) {
            arr[j++] = node->data;
            node = node->next;
        }
    }

    return;
}


int getBucketIndex(int value) {
    return value / INTERVAL;
}


void print(int ar[]) {
    int i;
    for (i = 0; i < NARRAY; ++i) {
        printf("%d ", ar[i]);
    }
    printf("\n");
}


// Print buckets
void printBuckets(struct Node *list) {
    struct Node *cur = list;
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

void ordenaSequencialmente (struct Node **buckets) {
    for (int i = 0; i < NBUCKET; ++i) {
        if (buckets[i] != NULL) {
            //printf("VOU ORDENAR\n");
            if (METHOD == 0) {
                buckets[i] = InsertionSort(buckets[i]);
            } 
            else if (METHOD == 1) {
                struct Node *last = last_node(buckets[i]);
                buckets[i] = quick_sort(buckets[i], last);
            }
        }
    }
}

void ordenaParalelamente (struct Node **buckets) {

    #pragma omp parallel
    #pragma omp for schedule(dynamic)

    for (int i = 0; i < NBUCKET; ++i) {
        if (buckets[i] != NULL) {
            //printf("VOU ORDENAR\n");
            if (METHOD == 0) {
                buckets[i] = InsertionSort(buckets[i]);
            } 
            else if (METHOD == 1) {
                struct Node *last = last_node(buckets[i]);
                buckets[i] = quick_sort(buckets[i], last);
            }
        }
    }
}

void inicializaSequencialmente (struct Node **buckets) {
    // Initialize empty buckets
    for (int i = 0; i < NBUCKET; ++i) {
        buckets[i] = NULL;
    }
}

void inicializaParalelamente (struct Node **buckets) {
    #pragma omp parallel
    #pragma omp for schedule(dynamic)

    // Initialize empty buckets
    for (int i = 0; i < NBUCKET; ++i) {
        buckets[i] = NULL;
    }
}