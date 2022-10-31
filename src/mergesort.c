#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "mergesort.h"

//L'algoritmo di MERGESORT è stato adattato dal sito https:// www.geeksforgeeks.org/?p=3622

/* sorts the linked list by changing next pointers (not memory_usage) */
void MergeSort(struct struct_process** headRef, int flag)
{
    struct struct_process* head = *headRef;
    struct struct_process* a;
    struct struct_process* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    MergeSort(&a, flag);
    MergeSort(&b, flag);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b, flag);
}
 

struct_process* SortedMerge(struct struct_process* a, struct struct_process* b , int flag)
{
    struct struct_process* result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
 
    /* Pick either a or b, and recur */
    if (flag == 1){
        if (a->memory_usage <= b->memory_usage) {
            result = a;
            result->next = SortedMerge(a->next, b, flag);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, flag);
        }
    }
    else {
        if (a->cpu_usage <= b->cpu_usage) {
            result = a;
            result->next = SortedMerge(a->next, b, flag);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, flag);
        }
    }
    return (result);
}
 
/* UTILITY FUNCTIONS */
/* Split the struct_processs of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra struct_process should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct struct_process* source,
                    struct struct_process** frontRef, struct struct_process** backRef)
{
    struct struct_process* fast;
    struct struct_process* slow;
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two struct_processs, and advance 'slow' one struct_process */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}