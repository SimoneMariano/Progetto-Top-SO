#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "utils.h"

// Il seguente file è stato costruito riadattando le funzioni delle linked list utilizzate nel corso

void List_print(ListHead *head) // Funzione di stampa della linked list
{
  struct_process *aux = head->first;
  while (aux)
  {
    struct_process *element = (struct_process *)aux;
    printf("PID: %d, NOME: %s, STATO: %s\nMemUsage: %f\nCpuUsage: %f\n", element->pid, element->name, element->state, element->memory_usage, element->cpu_usage);
    printf("--------------------------------------\n");
    aux = aux->next;
  }
  printf("\n");
}

ListHead *List_init() // Funzione che inizializza la ListHead
{
  ListHead *head = (ListHead *)malloc(sizeof(ListHead)); // allocazione della ListHead

  head->first = NULL;
  head->last = NULL;
  head->size = 0;
  return head;
}
struct struct_process *struct_process_init(ListHead *head) // Funzione che inizializza la struct_process
{
  struct struct_process *new_node = (struct struct_process *)malloc(sizeof(struct_process)); // Allocazione del nodo
  new_node->memory_usage = 0;
  new_node->cpu_usage = 0;
  new_node->pid = 0;
  new_node->next = NULL;
  return new_node;
}

void List_insert(struct struct_process *new_node, ListHead **head_ref) // Inserisce il nodo nella lista
{
  new_node->next = (*head_ref)->first;
  (*head_ref)->first = new_node;
  (*head_ref)->size++;
  return;
}

void List_cleaner(ListHead *head) //Deallocazione lista
{

  if (head->first == NULL|| head->last == NULL)
  {
    return;
  }
  struct_process *aux = head->first;
  struct_process *tmp;

  while (aux != NULL)
  {
    tmp = aux;
    aux = aux->next;
    free(tmp);
  }
}