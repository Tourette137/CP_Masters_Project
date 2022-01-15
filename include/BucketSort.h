#ifndef BUCKET_SORT
#define BUCKET_SORT

struct Node {
    int data;
    struct Node *next;
};

void BucketSort(int arr[]);
void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

void ordenaSequencialmente (struct Node **buckets);
void ordenaParalelamente (struct Node **buckets);

void inicializaSequencialmente (struct Node **buckets);
void inicializaParalelamente (struct Node **buckets);

#endif