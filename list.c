#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *nuevaLista = (List *)malloc(sizeof(List));
  if (nuevaLista != NULL) {
      nuevaLista->head = NULL;
      nuevaLista->tail = NULL;
      nuevaLista->current = NULL;
  }
  return nuevaLista;
}
//1======================================================================================
void * firstList(List * list) {
  if (list != NULL && list->head != NULL) {
      list->current = list->head;
      return list->current->data;
  }
  return NULL;
}
//2======================================================================================
void * nextList(List * list) {
  if (list != NULL && list->current != NULL && list->current->next != NULL){
      list->current = list->current->next;
      return list->current->data;
  }
  return NULL;
}
//3======================================================================================
void * lastList(List * list) {
  if(list != NULL && list->tail != NULL){
    list->current = list->tail;
    return list->current->data;
  }
  return NULL;
}

void * prevList(List * list) {
  if (list != NULL && list->current != NULL && list->current->prev != NULL){
      list->current = list->current->prev;
      return list->current->data;
  }
  return NULL;
}
//4======================================================================================
void pushFront(List * list, void * data) {
  Node *nuevoNodo = createNode(data);
  if (list != NULL && nuevoNodo != NULL){
    if (list->head == NULL){
      list->head = nuevoNodo;
      list->tail = nuevoNodo;
    }else{
      nuevoNodo->next = list->head;
      list->head = nuevoNodo;
    }
  }
}
//5======================================================================================
void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list != NULL && list->current != NULL){
    Node *nuevoNodo = createNode(data);
    if (nuevoNodo != NULL) {
        nuevoNodo->next = list->current->next;
        nuevoNodo->prev = list->current;
        if (list->current->next != NULL){
            list->current->next->prev = nuevoNodo;
        }else{
            list->tail = nuevoNodo;
        }
        list->current->next = nuevoNodo;
    }
  }
}
//6======================================================================================
void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list != NULL && list->current != NULL){
    Node *nodoEliminar = list->current;
    void *data = nodoEliminar->data;
    if (nodoEliminar->prev != NULL){
      nodoEliminar->prev->next = nodoEliminar->next;
    }else{
      list->head = nodoEliminar->next;
    }
    if (nodoEliminar->next != NULL){
      nodoEliminar->next->prev = nodoEliminar->prev;
    }else{
      list->tail = nodoEliminar->prev;
    }
    list->current = nodoEliminar->next;
    return data;
  }
  return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}