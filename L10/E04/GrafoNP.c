//
// Created by loren on 05/01/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "GrafoNP.h"
#include <string.h>

#define MAXC 10

typedef struct node *link;
struct node{ int v; int wt; link next; };
struct graph {int V; int E; int **madj; link *ladj; ST tab; link z;};
static Edge  EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static link NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void Sort(char **a, int l, int r);
static int CharL(char *a,char *b);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}
static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}
int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    if (t==NULL)
        return NULL;

    for (i=0; i < r; i++) {
        t[i] = malloc(c * sizeof(int));
        if (t[i]==NULL)
            return NULL;
    }
    for (i=0; i < r; i++)
        for (j=0; j < c; j++)
            t[i][j] = val;
    return t;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    G->madj = MATRIXint(V, V, 0);
    if (G->madj == NULL)
        return NULL;
    G->ladj=NULL;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    link x;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    if(G->ladj!=NULL) {
        for (i = 0; i < G->V; i++) {
            for (x = G->ladj[i]; x != G->z; x = x->next) {
                free(x);
            }
            free(x);
        }
        free(G->ladj);
    }
    STfree(G->tab);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V=0, i=0, id1, id2, wt;
    char label1[MAXC],label2[MAXC];
    Graph G;
    while(!feof(fin)){
        fscanf(fin, "%*s %*s %*s %*s %*d%*c");
        V++;
    }
    V=2*V;
    rewind(fin);

    G = GRAPHinit(V);

    while (!feof(fin)) {
        fscanf(fin, "%s %s", label1,label2);
        if(STsearch(G->tab,label1)==-1) {
            STinsert(G->tab, label1, label2, i);
            i++;
        }
        fscanf(fin, "%s %s %*d%*c", label1,label2);
        if(STsearch(G->tab,label1)==-1) {
            STinsert(G->tab, label1, label2, i);
            i++;
        }
    }

    rewind(fin);

    G->V=STsize(G->tab);
    while(fscanf(fin, "%s %*s %s %*s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

Graph GRAPHcreateLIST(Graph G) {
    int  i, j;

    G->ladj = malloc((G->V)*sizeof(link));
    if (G->ladj == NULL)
        return NULL;
    for (i = 0; i < G->V; i++)
        G->ladj[i] = G->z;

    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            if(G->madj[i][j]!=0){
                G->ladj[i] = NEW(j, G->madj[i][j], G->ladj[i]);
            }
        }
    }
    return G;
}

int GRAPHcomplSgMAT(Graph G, char *str1, char *str2, char *str3){
    int id1,id2,id3;
    id1=STsearch(G->tab,str1);
    id2=STsearch(G->tab,str2);
    id3=STsearch(G->tab,str3);
    if(G->madj[id1][id2]!=0)
        if(G->madj[id2][id3]!=0)
            if(G->madj[id3][id1]!=0)
                return 1;
    return 0;
}

int GRAPHcomplSgLIST(Graph G, char *str1, char *str2, char *str3){
    link x;
    int id1,id2,id3,cnt=0;
    id1=STsearch(G->tab,str1);
    id2=STsearch(G->tab,str2);
    id3=STsearch(G->tab,str3);
    for(x=G->ladj[id1];x!=G->z;x=x->next){
        if(x->v==id2)
            cnt++;
    }
    for(x=G->ladj[id2];x!=G->z;x=x->next){
        if(x->v==id3)
            cnt++;
    }
    for(x=G->ladj[id3];x!=G->z;x=x->next){
        if(x->v==id1)
            cnt++;
    }
    if(cnt==3)
        return 1;
    return 0;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void GRAPHstore(Graph G, FILE *fout) {
    int i,j,v,w,E=0;
    char **a,**e;

    a = malloc((G->V) * sizeof(char*));
    if (a == NULL)
        return;
    for(i=0;i<G->V;i++){
        a[i]=strdup(STsearchByIndex(G->tab,i));
    }

    Sort(a,0,G->V);

    for(i=0;i<G->V;i++){
        fprintf(fout,"Vertici: %s\n",a[i]);
    }
    fprintf(fout,"\n");

    e = malloc((G->V) * sizeof(char*));
    for (i=0; i < G->V; i++) {
        v=STsearch(G->tab,a[i]);
        for (w=0; w < G->V; w++) {
            if (G->madj[v][w] != 0) {
                e[E++] = strdup(STsearchByIndex(G->tab, w));
            }
        }
        Sort(e,0,E);
        fprintf(fout,"Vertice:\t%s\n",a[i]);
        for(j=0;j<E;j++)
            fprintf(fout,"Archi: %s   ",e[j]);
        fprintf(fout,"\n-----------------------------------------------------------\n");
        E=0;
    }
    for(i=0;i<G->V;i++)
        free(a[i]);
    free(a);
    for(i=0;i<G->V;i++)
        free(e[i]);
    free(e);
}

static void Sort(char **a,int l,int r){
    int i, j, min;
    char temp[MAXC];
    for(i = l; i < r; i++) {
        min = i;
        for (j = i+1; j < r; j++)
            if (CharL(a[j],a[min]))
                min = j;
        strcpy(temp,a[i]);
        strcpy(a[i],a[min]);
        strcpy(a[min],temp);
    }
}
static int CharL(char *a,char *b){
    int i,N;
    if(strlen(a)>strlen(b))
        N=strlen(b);
    else
        N=strlen(a);
    for(i=0;i<N;i++){
        if(a[i]<b[i])
            return 1;
        if(a[i]>b[i])
            return 0;
    }
    return 0;
}
