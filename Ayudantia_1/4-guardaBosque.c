#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int val;
    struct Nodo *izq, *der;
} Nodo;

Nodo* nuevo(int v){
    Nodo* n=malloc(sizeof(Nodo));
    n->val=v; n->izq=n->der=NULL;
    return n;
}

Nodo* insertar(Nodo* r,int v){
    if(!r) return nuevo(v);
    if(v < r->val) r->izq=insertar(r->izq,v);
    else r->der=insertar(r->der,v);
    return r;
}

void inorder(Nodo* r){
    if(r){ inorder(r->izq); printf("%d ",r->val); inorder(r->der); }
}

int main(){
    Nodo* raiz=NULL;
    raiz=insertar(raiz,5);
    insertar(raiz,2);
    insertar(raiz,8);
    insertar(raiz,1);
    insertar(raiz,3);
    inorder(raiz);
    return 0;
}