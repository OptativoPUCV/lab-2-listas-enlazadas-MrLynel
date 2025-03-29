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
    List *list = (List *)malloc(sizeof(List));//se asigna memoria
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

void pushCurrent(List *list, void *data) {
    if (list == NULL || list->current == NULL) {//verificar si existe y en caso de que no haya nada no hacer nada
        return;
    }

    Node *newNode = createNode(data); //se creea un nuevo nodo

    newNode->prev = list->current;  //enlazamos y ahora el actual es el previo al nuevo nodo
    newNode->next = list->current->next;  // y el siguiente del actual sera el nuevo nodo

    if (list->current->next != NULL) {   //en caso de existir un nodo se actualiza su puntero del prev
        list->current->next->prev = newNode;
    } else {
        list->tail = newNode; //en caso contrario va al tail
    }

    list->current->next = newNode;// actualizamos el cactual para que apunte al nuevo
}


void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}


void *popCurrent(List *list) {
    if (list == NULL || list->current == NULL) {
        return NULL; // si no hay nada no se retorna nada
    }

    Node *nodeToRemove = list->current; //referencia al que se va a eliminar
    void *data = nodeToRemove->data;  //almaceno el dato del qu se va a elminar

    if (nodeToRemove->prev != NULL) {
        nodeToRemove->prev->next = nodeToRemove->next;
    } else {
        list->head = nodeToRemove->next; //si es justo el head actualizamos
    }

    if (nodeToRemove->next != NULL) {
        nodeToRemove->next->prev = nodeToRemove->prev;
    } else {
        list->tail = nodeToRemove->prev;// en caso de que sea el tail se actualiza
    }

    list->current = nodeToRemove->next; //hacemos que apunte al siguente del eliminado

    free(nodeToRemove);//liberamos memoria

    return data;//retorno el valor
}


void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}