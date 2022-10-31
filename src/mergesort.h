#include "linked_list.h"

void MergeSort(struct struct_process** headRef);
struct_process* SortedMerge(struct struct_process* a, struct struct_process* b);
void FrontBackSplit(struct struct_process* source, struct struct_process** frontRef, struct struct_process** backRef);