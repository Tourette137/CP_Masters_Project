#include "include/InsertionSort.h"
#include "include/BucketSort.h"

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