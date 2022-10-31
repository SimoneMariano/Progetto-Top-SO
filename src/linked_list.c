#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "utils.h"

void List_print(ListHead *head)
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

ListHead *List_init()
{
  ListHead *head = (ListHead *)malloc(sizeof(ListHead));

  head->first = NULL;
  head->last = NULL;
  head->size = 0;
  return head;
}
struct struct_process *struct_process_init(ListHead *head)
{
  struct struct_process *new_node = (struct struct_process *)malloc(sizeof(struct_process));

  /* put in the data */
  new_node->memory_usage = 0;
  new_node->cpu_usage = 0;
  new_node->pid = 0;
  new_node->next = NULL;
  return new_node;
}

struct_process *List_find(ListHead *head, struct_process *item)
{
  // linear scanning of list
  struct_process *aux = head->first;
  while (aux)
  {
    if (aux == item)
      return item;
    aux = aux->next;
  }
  return 0;
}

void List_insert(struct struct_process *new_node, ListHead **head_ref)
{

  /* link the old list off the new node */
  new_node->next = (*head_ref)->first;

  /* move the head to point to the new node */
  (*head_ref)->first = new_node;

  (*head_ref)->size++;
  return;
}

void List_cleaner(ListHead *head)
{

  if (head->first == NULL || head->last == NULL)
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