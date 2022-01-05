#ifndef QUICK_SORT
#define QUICK_SORT

struct Node *last_node(struct Node *head);
struct Node *quick_sort(struct Node *first, struct Node *last);
struct Node *parition(struct Node *first, struct Node *last);

#endif