#include "linked_list.h"
#include "utils.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void List_print(ListHead* head){
  struct_process* aux=head->first;
  while(aux){
    struct_process* element = (struct_process*) aux;
    printf ("PID: %d, NOME: %s, STATO: %s\nMemUsage: %f\nCpuUsage: %f\n", element->pid, element->name, element->state, element->memory_usage, element->cpu_usage);
    printf("---------------------------------\n");
    aux=aux->next;
  }
  printf("\n");
}

void List_init(ListHead* head) {
  head->first=0;
  head->last=0;
  head->size=0;
}

struct_process* List_find(ListHead* head, struct_process* item) {
  // linear scanning of list
  struct_process* aux=head->first;
  while(aux){
    if (aux==item)
      return item;
    aux=aux->next;
  }
  return 0;
}

void List_insert(struct struct_process* new_node, struct struct_process** head_ref) {

    //struct struct_process* new_node = (struct struct_process*)malloc(sizeof(struct_process));
 
    /* put in the data */
    //new_node->memory_usage = new_data;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref) = new_node;

}

struct_process* List_detach(ListHead* head, struct_process* item) {

  struct_process* aux = head->first;
  struct_process* tmp = aux->next;

  while(aux){

    free(aux);
    aux = tmp;
    tmp = tmp->next;

  }

}