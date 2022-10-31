#pragma once
typedef struct struct_process {
	struct struct_process* next;	
	char name[256];
	int pid;
    float cpu_usage;
	float memory_usage;
    char state[256];
} struct_process;
typedef struct ListHead {
  struct struct_process* first;
  struct struct_process* last;
  int size;
} ListHead;

void List_print(ListHead* head);
void List_init(ListHead* head);
struct_process* List_find(ListHead* head, struct_process* item);
void List_insert(struct struct_process* new_node, struct struct_process** head_ref);
struct_process* List_detach(ListHead* head, struct_process* item);