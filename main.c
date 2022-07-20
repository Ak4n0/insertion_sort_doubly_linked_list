#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;
 
void print(node *list) {
    node *pointer = list;
    while(pointer) {
        printf("%d ", pointer->data);
        pointer = pointer->next;
    }
    putchar('\n');
}
 
void insertion_sort(node **head) {
    // evito una lista vacía
    if(!*head) {
        return;
    }
 
    // se recorre la lista de izquierda a derecha
    for(node *pointer=(*head)->next; pointer; pointer=pointer->next) {
        // nodo auxiliar para recorrer la lista al revés en busca de datos menores
        node *aux = pointer;
        // flag para mantener pointer en su sitio
        bool flag = true;
        // ordenando de forma ascendente
        while(aux->prev && aux->data < aux->prev->data) {
            // se inicia el intercambio de nodos, el actual por el anterior a este --------
            // se empieza por hacer que los nodos en los extremos de la pareja actual apunten
            // a la pareja actual de forma intercambiada. Por ejemplo: sean los cuatro nodos
            // A B [C] D
            // C es el nodo actual a comparar
            // A->next apunta a B
            // D->prev apunta a C
            // en el intercambio
            // A->next debe apuntar a C
            // D->prev debe apuntar a B
            // para que esto sea así se debe comprobar que A y D existan para poder operar
 
            // contiene la dirección del nodo previo al previo del actual. Siendo el actual C, A.
            node *app = aux->prev->prev;
            // si dicho nodo existe, el siguiente a este deberá ser el actual. A->next apunta a C.
            if(app) {
                aux->prev->prev->next = aux;
            }
            // si existe un nodo que sea siguiente al actual, su previo debe apuntar al nodo anterior al actual. D->prev apunta a B.
            if(aux->next) {
                aux->next->prev = aux->prev;
            }
 
            // intercambio entre la pareja de nodos.
            // B->prev apunta a C
            aux->prev->prev = aux;
            // B->next apunta a D
            aux->prev->next = aux->next;
            // C->next apunta a B
            aux->next = aux->prev;
            // C->prev apunta a A
            aux->prev = app;
 
            // el primer intercambio se hará lo más a la derecha de la sublista
            // por lo tanto cuándo se efectua el primer intercambio se debe actualizar
            // pointer para que apunte al nodo intercambiado. El flag va a evitar que
            // si se va hacia la izquierda pointer también vaya a la izquierda.
            if(flag) {
                pointer = aux->next;
                flag = false;
            }
 
            // la cabeza de la lista se debe actualizar si hay algún nodo que ha caído en
            // esa posición
            if(!aux->prev)
                *head = aux;           
        }
    }
}
 
bool add(node **head, int data) {
    node *new = malloc(sizeof(node));
    if(!new) {
        return false;
    }
 
    new->data = data;
    new->next = NULL;
 
    if(*head) {
        node *pointer = *head;
        while(pointer->next) {
            pointer = pointer->next;
        }
        pointer->next = new;
        new->prev = pointer;
    } else {
        new->prev = NULL;
        *head = new;
    }
 
    return true;
}
 
void drop(node **head) {
    node *aux;
    if(!*head) {
        return;
    }
 
    while(*head) {
        aux = *head;
        *head = (*head)->next;
        free(aux);
    }
}
 
int main() {
    node *list = NULL;
    add(&list, 5);
    add(&list, 2);
    add(&list, 4);
    add(&list, 1);
    add(&list, 3);
    add(&list, 0);
 
    print(list);
    
    insertion_sort(&list);
    print(list);
 
    drop(&list);
}
