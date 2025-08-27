#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char cancion[30];
    struct Nodo *sig, *ant;
} Nodo;

void insertar(Nodo **head, char *nombre){
    Nodo* n=malloc(sizeof(Nodo));
    strcpy(n->cancion,nombre);
    n->sig=*head; n->ant=NULL;
    if(*head) (*head)->ant=n;
    *head=n;
}

void recorrer(Nodo *cur){
    while(cur){
        printf("▶ %s\n", cur->cancion);
        cur=cur->sig;
    }
}

int main(){
    Nodo* lista=NULL;
    insertar(&lista,"Song C");
    insertar(&lista,"Song B");
    insertar(&lista,"Song A");
    recorrer(lista);
    return 0;
}