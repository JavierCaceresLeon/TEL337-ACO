#include <stdio.h>
#include <stdlib.h>

#define N 6
int grafo[N][N] = {
    {0,1,1,0,0,0},
    {1,0,0,1,0,0},
    {1,0,0,1,1,0},
    {0,1,1,0,0,1},
    {0,0,1,0,0,1},
    {0,0,0,1,1,0}
};

typedef struct Nodo {
    int val;
    struct Nodo *sig;
} Nodo;

typedef struct { Nodo *f, *r; } Cola;

void encolar(Cola *q,int v){
    Nodo* n=malloc(sizeof(Nodo));
    n->val=v; n->sig=NULL;
    if(q->r) q->r->sig=n; else q->f=n;
    q->r=n;
}

int desencolar(Cola *q){
    if(!q->f) return -1;
    Nodo* t=q->f; int v=t->val;
    q->f=t->sig; if(!q->f) q->r=NULL;
    free(t); return v;
}

void BFS(int s){
    int vis[N]={0}, dist[N]={0};
    Cola q={NULL,NULL};
    vis[s]=1; encolar(&q,s);
    while(q.f){
        int u=desencolar(&q);
        for(int v=0;v<N;v++){
            if(grafo[u][v] && !vis[v]){
                vis[v]=1; dist[v]=dist[u]+1;
                encolar(&q,v);
            }
        }
    }
    for(int i=0;i<N;i++) printf("Atracción %d a distancia %d\n",i,dist[i]);
}

int main(){ BFS(0); return 0; }
