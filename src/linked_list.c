#include "linked_list.h"
#include "utils.h"
#include <assert.h>
#include <string.h>

void List_print(ListHead* head){
  ListItem* aux=head->first;
  printf("[");
  while(aux){
    struct_process* element = (struct_process*) aux;
    printf("%s ", element->name);
    printf("%f\n", element->memory_usage);
    printf("---------------------------------\n");
    aux=aux->next;
  }
  printf("]\n");
}

void List_init(ListHead* head) {
  head->first=0;
  head->last=0;
  head->size=0;
}

ListItem* List_find(ListHead* head, ListItem* item) {
  // linear scanning of list
  ListItem* aux=head->first;
  while(aux){
    if (aux==item)
      return item;
    aux=aux->next;
  }
  return 0;
}

ListItem* List_insert(ListHead* head, ListItem* prev, ListItem* item) {
  if (item->next || item->prev)
    return 0;

  ListItem* next= prev ? prev->next : head->first;
  if (prev) {
    item->prev=prev;
    prev->next=item;
  }
  if (next) {
    item->next=next;
    next->prev=item;
  }
  if (!prev)
    head->first=item;
  if(!next)
    head->last=item;
  ++head->size;
  return item;
}

ListItem* List_detach(ListHead* head, ListItem* item) {

  ListItem* prev=item->prev;
  ListItem* next=item->next;
  if (prev){
    prev->next=next;
  }
  if(next){
    next->prev=prev;
  }
  if (item==head->first)
    head->first=next;
  if (item==head->last)
    head->last=prev;
  head->size--;
  item->next=item->prev=0;
  return item;
}

void bubbleSort(ListItem* item) 
{ 
    int swapped, i;     
    ListItem* lptr = NULL;
    

  
    /* Checking for empty list */
    if (item == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        struct_process* ptr1 = (struct_process*) item;
  
        while (item->next != lptr) 
        { 
          struct_process* ptr1_next = (struct_process*) item->next;
            if (ptr1->memory_usage > ptr1_next->memory_usage) 
            { 
                swap(item, item->next); 
                swapped = 1; 
            } 
            item = item->next; 
        } 
        lptr = item; 
    } 
    while (swapped); 
} 
  
/* function to swap data of two ListItems a and b*/
void swap(struct ListItem *a, struct ListItem *b) 
{ 
    if (a==NULL || b == NULL ){
      return;
    }
    if (a == b){
      return;
    }
    
    struct_process* a_tmp = (struct_process*) a;
    struct_process* b_tmp = (struct_process*) b;

    int pid_tmp;
    float data_tmp;
    char char_tmp[256];

    pid_tmp = a_tmp->pid;
    a_tmp->pid = b_tmp->pid;
    b_tmp->pid = pid_tmp;

    data_tmp = a_tmp->cpu_usage;
    a_tmp->cpu_usage = b_tmp->cpu_usage;
    b_tmp->cpu_usage = data_tmp;

    data_tmp = a_tmp->memory_usage;
    a_tmp->memory_usage = b_tmp->memory_usage;
    b_tmp->memory_usage = data_tmp;

    strcat(char_tmp, a_tmp->name);
    strcat(a_tmp->name, b_tmp->name);
    strcat(b_tmp->name, char_tmp);

    strcat(char_tmp, a_tmp->state);
    strcat(a_tmp->state, b_tmp->state);
    strcat(b_tmp->state, char_tmp);
} 
