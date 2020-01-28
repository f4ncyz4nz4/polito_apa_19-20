//
// Created by loren on 08/01/2020.
//
#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode { Data d; float qg; int N; link l; link r;} ;
struct binarysearchtree { link root; link z; };
static link insertR(link h, float x,Data d, link z);
static void treePrintR(FILE *fout,link h, link z);
static Data searchR(link h, float qb, link z);
static void visitmin(link h,link z,Data i, Data f,float *min);
static void visitmax(link h,link z,Data i, Data f,float *max);
static link partR(link h, int r);
static link balanceR(link h, link z);
static link rotL(link h);
static link rotR(link h);
static void visitCmin(link h,link z,int *min);
static void visitCmax(link h,link z,int *max);
static void treeFree(link h, link z);

static link NEW(float qg,Data d,int N, link l, link r) {
    link x = malloc(sizeof (*x));
    x->qg = qg; x->d=d; x->N=N;
    x->l = l; x->r = r;
    return x;
}
BST BSTinit( ) {
    BST bst = malloc(sizeof (*bst)) ;
    bst->root= ( bst->z = NEW(-1, DataNULL(), 0, NULL, NULL));
    return bst;
}

Data BSTsearch(BST bst, float qg){
    return searchR(bst->root, qg, bst->z);
}

float BSTVisitMax(BST bst,Data i,Data f){
    float max=-1000;
    visitmax(bst->root,bst->z,i,f,&max);
    return max;
}
void static visitmax(link h,link z,Data i, Data f,float *max){
    if (h == z)
        return;
    if (DataCmp(h->d,f)==-1 && DataCmp(h->d,i)==1 && h->qg>*max) {
        *max = h->qg;
    }
    visitmax(h->l,z,i,f,max);
    visitmax(h->r,z,i,f,max);
}
float BSTVisitMin(BST bst,Data i,Data f){
    float min=1000;
    visitmin(bst->root,bst->z,i,f,&min);
    return min;
}
void static visitmin(link h,link z,Data i, Data f,float *min){
    if (h == z)
        return;
    if (DataCmp(h->d,f)==-1 && DataCmp(h->d,i)==1 && h->qg<*min) {
        *min = h->qg;
    }
    visitmin(h->l,z,i,f,min);
    visitmin(h->r,z,i,f,min);
}

int CamMM(BST bst,int s){
    int min=1000,max=-1000;
    visitCmin(bst->root,bst->z,&min);
    visitCmax(bst->root,bst->z,&max);
    if((max-min)>=s)
        return 1;
    return 0;
}
void static visitCmin(link h,link z,int *min){
    if ((h->r == z) && (h->l == z) && h->N<*min) {
        *min=h->N;
        return;
    }
    if(h->l!=z)
        visitCmin(h->l,z,min);
    if(h->r!=z)
        visitCmin(h->r,z,min);
}
void static visitCmax(link h,link z,int *max){
    if ((h->r == z) && (h->l == z) && h->N>*max) {
        *max=h->N;
        return;
    }
    if(h->l!=z)
        visitCmax(h->l,z,max);
    if(h->r!=z)
        visitCmax(h->r,z,max);
}

static link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    r = (h->N+1)/2-1;
    h = partR(h, r);
    if(h->l!=z)
        h->l = balanceR(h->l, z);
    if(h->r!=z)
        h->r = balanceR(h->r, z);
    return h;
}
void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}
link partR(link h, int r) {
    int t = h->l->N;
    if (t > r) {
        if(h->l->qg!=-1) {
            h->l = partR(h->l, r);
            h = rotR(h);
        }
    }
    if (t < r) {
        if(h->r->qg!=-1) {
            h->r = partR(h->r, r - t - 1);
            h = rotL(h);
        }
    }
    return h;
}
link static rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}
link static rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

Data static searchR(link h, float qb, link z) {
    if (h == z)
        return DataNULL();
    if (qb==h->qg)
        return h->d;
    if (qb<h->qg)
        return searchR(h->l, qb, z);
    return searchR(h->r, qb, z);
}

void BSTinsert_leafR(BST bst, float qg,Data d) {
    bst->root = insertR(bst->root, qg,d, bst->z);
}
static link insertR(link h, float x,Data d, link z) {
    if (h == z)
        return NEW(x, d, 1, z, z);
    if (x<h->qg) {
        h->l = insertR(h->l,x,d,z);
        h->N++;
    }
    else{
        h->r = insertR(h->r,x,d,z);
        h->N++;
    }
    return h;
}

void BSTvisit(FILE *fout,BST bst){
    if (bst->root==bst->z)
        return;
    treePrintR(fout,bst->root, bst->z);
}
static void treePrintR(FILE *fout,link h, link z) {
    if (h == z)
        return;
    Dataprint(fout,h->d);
    fprintf(fout,"QG:%f\n",h->qg);
    treePrintR(fout,h->l, z);
    treePrintR(fout,h->r, z);
}

void BSTfree(BST bst) {
    if (bst == NULL) return;
    treeFree(bst->root, bst->z);
    free(bst->z); free(bst);
}
static void treeFree(link h, link z) {
    if (h == z) return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}