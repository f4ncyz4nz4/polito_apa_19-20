//
// Created by loren on 28/01/2020.
//

#include "Graph.h"
#include <limits.h>

#define MAXC 10
#define maxWT INT_MAX

struct graph {int V; int E;int *vert; int **madj; ST tab; };
static Edge  EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void dfsRcc(Graph G, int v, int id, int *cc);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
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
    G->madj = MATRIXint(V, V, 0);
    if (G->madj == NULL)
        return NULL;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int i;

    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);

    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }

    G->vert=calloc(G->V, sizeof(int));
    return G;
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

void  GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < G->V; v++)
        for (w=v+1; w < G->V; w++)
            if (G->madj[v][w] != maxWT)
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL)
        return;

    GRAPHedges(G, a);

    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

}

int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

void GRAPHkcore(Graph G,int k){
    int i,j,continua=1,*g_archi=calloc(G->V, sizeof(int));
    while (continua){
        continua=0;
        for(i=0;i<G->V;i++){
            if(G->vert[i]==0){
                for(j=0;j<G->V;j++){
                    if(G->vert[j]==0){
                        if(G->madj[i][j]==1)
                            g_archi[i]++;
                    }
                }
            }
        }
        //MergeSort(g_archi,G->V);
        for(i=0;i<G->V;i++){
            if(g_archi[i]<k && g_archi[i]!=0){
                G->vert[i]=1;
                continua=1;
            }
        }
        for(i=0;i<G->V;i++)
            g_archi[i]=0;
    }
    printf("I vertici del K-core sono:\n");
    for(i=0;i<G->V;i++){
        if(G->vert[i]==0)
            printf("%s\n",STsearchByIndex(G->tab,i));
    }
}

void GRAPHconneted(int J,Graph G){
    int i,j,N=0,c;
    Edge *edge=malloc((G->E)* sizeof(Edge));
    int *sol=malloc(J* sizeof(int));
    for(i=0;i<G->V-1;i++){
        for(j=i;j<G->V;j++){
            if(G->madj[i][j]==1)
                edge[N++]=EDGEcreate(i,j,1);
        }
    }
    c=GRAPHconnR(G,J,N,edge,sol,0,0);
    if(c){
        printf("Grafo j-edge connected se rimuovi:\n");
        for(i=0;i<J;i++)
            printf("Arco da %s a %s\n",STsearchByIndex(G->tab,edge[sol[i]].v),STsearchByIndex(G->tab,edge[sol[i]].w));
    } else
        printf("Il grafo non è j-edge-connected\n");
}

int GRAPHconnR(Graph G, int j,int N, Edge *edge,int *sol,int start,int pos){
    int v,w,i,cc;
    if(pos>=j) {
        for (i = 0; i < j; i++) {
            v = edge[sol[i]].v;
            w = edge[sol[i]].w;
            G->madj[v][w] = 0;
            G->madj[w][v] = 0;
        }
        cc = GRAPHcc(G);
        if (cc > 1)
            return 1;
        else {
            for (i = 0; i < j; i++) {
                v = edge[sol[i]].v;
                w = edge[sol[i]].w;
                G->madj[v][w] = 1;
                G->madj[w][v] = 1;
            }
        }
        return 0;
    }
    for(i=start;i<N;i++){
        sol[pos]=i;
        if(GRAPHconnR(G,j,N,edge,sol,i+1,pos+1))
            return 1;
    }
    return 0;
}

int GRAPHcc(Graph G) {
    int v, id = 0,cc[G->V];
    for (v = 0; v < G->V; v++)
        cc[v] = -1;

    for (v = 0; v < G->V; v++) {
        if (cc[v] == -1)
            dfsRcc(G, v, id++, cc);
    }
    return id;
}
static void dfsRcc(Graph G, int v, int id, int *cc) {
    int i;
    cc[v] = id;
    for (i=0;i<G->V;i++){
        if(G->madj[v][i]==1)
            if(cc[i] == -1)
                dfsRcc(G, i, id, cc);
    }
}
