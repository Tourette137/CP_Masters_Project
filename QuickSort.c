#include "include/QuickSort.h"
#include "include/BucketSort.h"

#include <stdio.h>
#include <stdlib.h>

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