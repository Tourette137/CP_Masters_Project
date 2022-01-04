// Bucket sort in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NARRAY 1000000   // Array size

static int NBUCKET = 1000;  // Number of buckets
static int INTERVAL; // Each bucket capacity

// 0 -> INSERTION_SORT | 1 -> QUICK_SORT
#define METHOD 1


struct Node {
    int data;
    struct Node *next;
};

void BucketSort(int arr[]);

struct Node *InsertionSort(struct Node *list);

struct Node *last_node(struct Node *head);
struct Node *quick_sort(struct Node *first, struct Node *last);
struct Node *parition(struct Node *first, struct Node *last);



void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

// Sorting function
void BucketSort(int arr[]) {
    int i, j;
    struct Node **buckets;

    // Create buckets and allocate memory size
    buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

    // Initialize empty buckets
    for (i = 0; i < NBUCKET; ++i) {
        buckets[i] = NULL;
    }

    // Fill the buckets with respective elements
    for (i = 0; i < NARRAY; ++i) {
        struct Node *current;
        int pos = getBucketIndex(arr[i]);
        current = (struct Node *)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    // Print the buckets along with their elements
    /*
    for (i = 0; i < NBUCKET; i++) {
        printf("Bucket[%d]: ", i);
        printBuckets(buckets[i]);
        printf("\n");
    }
    */

    // Sort the elements of each bucket
    for (i = 0; i < NBUCKET; ++i) {
        if (METHOD == 0) {
            buckets[i] = InsertionSort(buckets[i]);
        } 
        else if (METHOD == 1) {
            struct Node *last = last_node(buckets[i]);
            buckets[i] = quick_sort(buckets[i], last);
        }
    }

    /*
    printf("-------------\n");
    printf("Bucktets after sorting\n");
    for (i = 0; i < NBUCKET; i++) {
        printf("Bucket[%d]: ", i);
        printBuckets(buckets[i]);
        printf("\n");
    }
    */

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

//Find last node of linked list
struct Node *last_node(struct Node *head) {

	struct Node *temp = head;
	while (temp != NULL && temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;
}

// Function to sort the elements of each bucket
struct Node *quick_sort(struct Node *first, struct Node *last) {

	if (first == last)
	{
		return NULL;
	}
	struct Node *pivot = parition(first, last);
	if (pivot != NULL && pivot->next != NULL)
	{
		quick_sort(pivot->next, last);
	}
	if (pivot != NULL && first != pivot)
	{
		quick_sort(first, pivot);
	}

    return first;
}

//Set of given last node position to its proper position
struct Node *parition(struct Node *first, struct Node *last) {

	//Get first node of given linked list
	struct Node *pivot = first;
	struct Node *front = first;
	int temp = 0;
	while (front != NULL && front != last)
	{
		if (front->data < last->data)
		{
			pivot = first;
			//Swap node value
			temp = first->data;
			first->data = front->data;
			front->data = temp;
			//Visit to next node
			first = first->next;
		}
		//Visit to next node
		front = front->next;
	}
	//Change last node value to current node
	temp = first->data;
	first->data = last->data;
	last->data = temp;
	return pivot;
}

// Function to sort the elements of each bucket
struct Node *InsertionSort(struct Node *list) {
    struct Node *k, *nodeList;
    if (list == 0 || list->next == 0) {
        return list;
    }

    nodeList = list;
    k = list->next;
    nodeList->next = 0;
    while (k != 0) {
        struct Node *ptr;
        if (nodeList->data > k->data) {
            struct Node *tmp;
            tmp = k;
            k = k->next;
            tmp->next = nodeList;
            nodeList = tmp;
            continue;
        }

        for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
            if (ptr->next->data > k->data)
                break;
        }

        if (ptr->next != 0) {
            struct Node *tmp;
            tmp = k;
            k = k->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
            continue;
        } else {
            ptr->next = k;
            k = k->next;
            ptr->next->next = 0;
            continue;
        }
    }
    return nodeList;
}

// todo: Meter um Quicksort em vez de um InsertionSort


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

/**
 * @brief Function to find maximum int in arr[] of size n
 * 
 * @param arr array
 * @param n   number of elements in array
 * @return int largest number in array
 */
int largest(int arr[], int n)
{
    int i;
    
    // Initialize maximum element
    int max = arr[0];
 
    // Traverse array elements from second and
    // compare every element with current max 
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
 
    return max;
}

/**
 * @brief Sees if array is sorted
 * 
 * @param s array
 * @param n number os elements in array
 * @return int - tells if an array is sorted, and if so, in wich direction
 */
int isArraySorted(int s[], int n) {
    int a = 1, d = 1, i = 0;

    while ((a == 1 || d == 1) && i < n - 1) {
        if (s[i] < s[i+1])
            d = 0;
        else if (s[i] > s[i+1])
            a = 0;
        i++;
    }

    if (a == 1)
        return 1;
    else if (d == 1)
        return 2;
    else
        return 0;
}


// Driver code
int main (void) {

    clock_t t;

    // Definir o número de Buckets incial
    //omp_set_num_threads(NBUCKET);

    // Número máximo dos inteiros que array tem
    int max_number = 10000;
    
    // Criar o array dos números
    t = clock();

    int array[NARRAY];

    for (int a = 0; a < NARRAY; a++) 
        array[a] = rand() % max_number;
    
    t = clock() - t;

    printf("It took %f seconds to create the new array \n", ((double)t)/CLOCKS_PER_SEC);


    // Descobrir o maior elemento
    int largestNumber = largest(array, NARRAY);
    printf("Largest number was %d\n", largestNumber);

    // Definir o intervalo do array
    INTERVAL = largestNumber/NBUCKET + 1;
    printf("Interval set to %d\n", INTERVAL);

    if ((largestNumber % NBUCKET) == 0) {
        if (NBUCKET >= INTERVAL)
            NBUCKET++;
        else
            INTERVAL++;
    }

    printf("Size of initial array: %ld\n\n", sizeof(array)/sizeof(int) );

    printf("Initial array: ");
    //print(array);
    printf("-------------\n");

    t = clock();
    BucketSort(array);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("-------------\n");
    printf("Sorted array: ");
    //print(array);

    printf("\nSize of final array: %ld\n", sizeof(array)/sizeof(int) );

    switch(isArraySorted(array, sizeof(array)/sizeof(int)) ) {
        case 1:
            printf("The array is sorted in ascending order.\n");
            printf("BucketSort() took %f seconds to execute \n", time_taken);
            break;
        case 2:
            printf("The array is sorted in descending order.\n");
            printf("BucketSort() took %f seconds to execute \n", time_taken);
            break;
        case 0:
            printf("The array is not sorted.\n");
            break;
    }

    return 0;
}