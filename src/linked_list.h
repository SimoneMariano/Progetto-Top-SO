#pragma once

typedef struct struct_process
{
  struct struct_process *next; //Puntatore al prossimo elemento
  char name[256]; //Nome del processo
  int pid; //PID del processo
  float cpu_usage; //Uso della CPU
  float memory_usage; //Uso della memoria
  char state[2]; //Stato del processo
} struct_process;

typedef struct ListHead
{
  struct struct_process *first; //Primo elemento della lista
  struct struct_process *last;  //Ultimo elemento della lista
  int size; //Dimensione della lista
} ListHead;

struct struct_process *struct_process_init(ListHead *head);
void List_print(ListHead *head);
ListHead *List_init();
struct_process *List_find(ListHead *head, struct_process *item);
void List_insert(struct struct_process *new_node, ListHead **head_ref);
void List_cleaner(ListHead *head);