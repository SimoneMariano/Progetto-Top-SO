#pragma once
typedef struct struct_process
{
  struct struct_process *next;
  char name[256];
  int pid;
  float cpu_usage;
  float memory_usage;
  char state[2];
} struct_process;

typedef struct ListHead
{
  struct struct_process *first;
  struct struct_process *last;
  int size;
} ListHead;

struct struct_process *struct_process_init(ListHead *head);
void List_print(ListHead *head);
ListHead *List_init();
struct_process *List_find(ListHead *head, struct_process *item);
void List_insert(struct struct_process *new_node, ListHead **head_ref);
void List_cleaner(ListHead *head);