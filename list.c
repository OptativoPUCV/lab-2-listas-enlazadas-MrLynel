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

List *createList() {
    List *list = (List *)malloc(sizeof(List));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}


void *firstList(List *list) {
    if (list == NULL || list->head == NULL) { 
        return NULL; //la lista esta vacia, retorno null
    }
    list->current = list->head; //actualizo el dato actual 
    return list->current->data; //retorno el dato que se encuentra ahi
}



void *nextList(List *list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) {
        return NULL; //la lista esta vacia, retorno null
    }
    list->current = list->current->next; //actualizo al dato que viene
    return list->current->data; //lo retorno
}



void *lastList(List *list) {
    if (list == NULL || list->tail == NULL) { 
        return NULL;//la lista esta vacia, retorno null
    }
    list->current = list->tail;//actualizo al ultimo elemento
    return list->current->data;//retorno el dato
}


void *prevList(List *list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) {
        return NULL;// si no hay datos retorno null
    }
    list->current = list->current->prev; //actualizo para tener el dato del nodo anterior 
    return list->current->data; //y retorno el dato
}


void pushFront(List *list, void *data) {
    Node *newNode = createNode(data);
    if (list == NULL) {
        return; //si no hay nada return null
    }
    if (list->head == NULL) {
        list->head = newNode;//inicializamos puntero a head
        list->tail = newNode;// lo mismo con el tail
    } else {//en caso de que si hayan elementos
        newNode->next = list->head; //se apunta al head
        list->head->prev = newNode; //se apunta al nuevo nodo
        list->head = newNode; //actualizo
    }

    // No se actualiza current en esta función, ya que depende de la lógica de navegación
}


void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}