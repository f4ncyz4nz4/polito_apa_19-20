#include "Graph.h"

#define maxWT INT_MAX
#define MAXC 10

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *valido);
static int isDag(Edge *Sol,Edge **B_Sol,int *sol,Edge *edge,int *b_k,int V,int E,int pos,int *N);
static int Check(Edge *sol,int V,int k);
static int EdgeCmp(Edge a,Edge b);
static void TSdfsR(Graph D, int v, int *ts, int *pre, int *time);

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

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    if (G->z == NULL)
        return NULL;
    G->ladj = malloc(G->V*sizeof(link));
    if (G->ladj == NULL)
        return NULL;
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

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
    return G;
}

Graph GRAPHcreateDAG(Graph G,Edge **archi,int N,int card,Edge *edge){
    int i,j,k,peso=0,b_peso=0,ind=0,E=G->E;
    Graph DAG;

    DAG=GRAPHinit(G->V);
    DAG->tab=G->tab;
    for(i=0;i<N;i++){
        for(j=0;j<card;j++){
            peso+=archi[i][j].wt;
        }
        if(peso>b_peso){
            ind=i;
            b_peso=peso;
        }
        peso=0;
    }
    printf("L'insieme di archi a cardinalità minima a peso massimo eliminati sono:\n");
    for(i=0;i<card;i++){
        printf("%s - %s peso:%d\n\n",STsearchByIndex(DAG->tab,archi[ind][i].v),STsearchByIndex(DAG->tab,archi[ind][i].w),archi[ind][i].wt);
    }
    for(j=0;j<card;j++){
        for(i=0;i<E;i++){
            if(EdgeCmp(edge[i],archi[ind][j])) {
                for (k = i; k < E - 1; k++) {
                    edge[k] = edge[k + 1];
                }
                E--;
            }
        }
    }
    for (i = 0; i < E; i++){
        GRAPHinsertE(DAG, edge[i].v, edge[i].w, edge[i].wt);
    }
    GRAPHmaxP(DAG);
    for(i=0;i<E;i++)
        free(archi[i]);
    free(archi);
    return DAG;
}
static int EdgeCmp(Edge a,Edge b){
    if(a.v==b.v)
        if(a.w==b.w)
            if(a.wt==b.wt)
                return 1;
    return 0;
}

Edge ** GRAPHtoDAG(Graph G,int *l,int *N,Edge **edge){
    int k=0,ind,*s=malloc(G->E* sizeof(int));
    link x;
    *N=0;*l=G->E;
    Edge *sol=(Edge*)malloc(G->E *sizeof(Edge));
    Edge **b_sol;

    *edge=(Edge*)malloc(G->E *sizeof(Edge));
    b_sol=(Edge**)malloc(G->E *sizeof(Edge*));
    for(ind=0;ind<G->E;ind++){
        b_sol[ind]=(Edge*)malloc(G->E *sizeof(Edge));
    }

    for(ind=0;ind<G->V;ind++){
        for(x=G->ladj[ind];x!=G->z;x=x->next){
            (*edge)[k++]=EDGEcreate(ind,x->v,x->wt);
        }
    }
    isDag(sol,b_sol,s,*edge,l,G->V,G->E,0,N);
    (*N)++;
    free(sol);
    free(s);
    return b_sol;
}
static int isDag(Edge* Sol,Edge** B_Sol,int *sol,Edge *edge,int *b_k,int V,int E,int pos,int *N){
    int i,k=0,j=0;
    if(pos>=E){
        for(i=0;i<E;i++){
            if(sol[i]==0)
                Sol[k++]=edge[i];
        }
        if(k!=0){
            if((E-k)<*b_k && Check(Sol,V,k)) {
                *N=0;
                for(i=0;i<E;i++){
                    if(sol[i]==1)
                        B_Sol[*N][j++]=edge[i];
                }
                *b_k = (E-k);
            } else if ((E-k)==*b_k && Check(Sol,V,k)){
                (*N)++;
                for(i=0;i<E;i++){
                    if(sol[i]==1)
                        B_Sol[*N][j++]=edge[i];
                }
            }
        }
        return 1;
    }
    sol[pos] = 0;
    isDag(Sol,B_Sol,sol,edge,b_k,V,E,pos+1,N);
    sol[pos] = 1;
    isDag(Sol,B_Sol,sol,edge,b_k,V,E,pos+1,N);
    return 1;
}
static int Check(Edge *sol,int V,int k){
    int i;
    Graph P;

    P = GRAPHinit(V);
    for (i = 0; i < k; i++){
        GRAPHinsertE(P, sol[i].v, sol[i].w, sol[i].wt);
    }
    if(GRAPHdfs(P,0)) {
        GRAPHfree(P);
        return 1;
    }
    GRAPHfree(P);
    return 0;
}

int* DAGrts(Graph D) {
    int v, time = 0, *pre,*ts;
    pre = malloc(D->V*sizeof(int));
    ts = malloc(D->V*sizeof(int));
    if ((pre == NULL) || (ts == NULL))
        return NULL;

    for (v=0; v < D->V; v++) {
        pre[v] = -1;
        ts[v] = -1;
    }
    for (v=0; v < D->V; v++) {
        if (pre[v] == -1)
            TSdfsR(D, v, ts, pre, &time);
    }
    free(pre);
    return ts;
}
void TSdfsR(Graph D, int v, int *ts, int *pre, int *time) {
    link t;
    pre[v] = 0;
    for (t = D->ladj[v]; t != D->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(D, t->v, ts, pre, time);
    ts[(*time)++] = v;
}

void GRAPHmaxP(Graph D){
    int i,j,*d,*rts=NULL,*ts=NULL;
    link t;
    ts = malloc(D->V*sizeof(int));
    d = malloc(D->V*sizeof(int));
    for(i=0;i<D->V;i++)
        d[i]=-1;
    rts=DAGrts(D);
    for(i=0,j=(D->V)-1;i<D->V;i++,j--){
        ts[j]=rts[i];
    }
    /*for(i=0;i<D->V;i++)
        printf("AAA %d\n",ts[i]);*/
    free(rts);
    d[ts[0]]=0;
    for(i=0;i<D->V;i++) {
        for (j = i; j < D->V; j++) {
            for (t = D->ladj[ts[j]]; t != D->z; t = t->next) {
                if (d[t->v] < d[ts[j]] + t->wt) {
                    d[t->v] = d[ts[j]] + t->wt;
                }
            }
        }
        printf("Nodo= %s\n",STsearchByIndex(D->tab,ts[i]));
        for (j = 0; j < D->V; j++) {
            if (d[ts[j]] != -1)
                printf("Distanza massima: %s --> %d\n", STsearchByIndex(D->tab, ts[j]), d[ts[j]]);
            else
                printf("Distanza massima: %s --> inf\n", STsearchByIndex(D->tab, ts[j]));
        }
        printf("\n");
        for(j=0;j<D->V;j++)
            d[j]=-1;
        d[ts[i+1]]=0;
    }
    free(d);
    free(ts);
}

int GRAPHdfs(Graph G, int id) {
    int valido=1;
    int v, time=0, *pre, *post, *st;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    if ((pre == NULL) || (post == NULL) || (st == NULL))
        return 0;

    for (v=0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] =  -1;
    }

    dfsR(G, EDGEcreate(id,id,1), &time, pre, post, st, &valido);
    if(!valido)
        return 0;

    for (v=0; v < G->V; v++) {
        if (pre[v] == -1) {
            dfsR(G, EDGEcreate(v, v, 1), &time, pre, post, st, &valido);
            if (!valido) {
                free(pre);
                free(post);
                free(st);
                return 0;
            }
        }
    }
    free(pre);
    free(post);
    free(st);
    return 1;
}
static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *valido) {
    link t; int v, w = e.w;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next) {
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v, 1), time, pre, post, st, valido);
        else {
            v = t->v;
            if (post[v] == -1)
                *valido = 0;
        }
    }
    post[w] = (*time)++;
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            a[E++] = EDGEcreate(v, t->v, t->wt);
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

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

