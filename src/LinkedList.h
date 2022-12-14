#ifndef __LINKEDLIST
#define __LINKEDLIST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
    void* pElement;
    struct Node* pPreviousNode;
    struct Node* pNextNode;
}typedef Node;

struct LinkedList
{
    Node* pFirstNode;
    Node* pLastNode;
    int size;
}typedef LinkedList;
#endif



//Publicas
LinkedList* ll_newLinkedList(void);
int ll_len(LinkedList* this);// retorna tamanio de ll
int ll_add(LinkedList* this, void* pElement);// agrega nuevo elemento en ll
void* ll_get(LinkedList* this, int index);
int ll_set(LinkedList* this, int index,void* pElement);
int ll_remove(LinkedList* this,int index);
int ll_clear(LinkedList* this);
int ll_deleteLinkedList(LinkedList* this);
int ll_indexOf(LinkedList* this, void* pElement);
int ll_isEmpty(LinkedList* this);
int ll_push(LinkedList* this, int index, void* pElement);
void* ll_pop(LinkedList* this,int index);
int ll_contains(LinkedList* this, void* pElement);
int ll_containsAll(LinkedList* this,LinkedList* this2);
LinkedList* ll_subList(LinkedList* this,int from,int to);
LinkedList* ll_clone(LinkedList* this);
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);
int ll_map(LinkedList* this, int (*pFunc)(void*));
LinkedList* ll_filter(LinkedList* this,  int (*pFunc)(void*));
