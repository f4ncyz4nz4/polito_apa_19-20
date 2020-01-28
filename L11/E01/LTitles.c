//
// Created by loren on 08/01/2020.
//
#include "LTitles.h"

typedef struct node *link;
struct node { Title t; link next; };
struct list { link head; int N; };
static int CharL(char *a,char *b);
static link newNode(FILE *fin, char* string,int N, link next);

LTitle LTinit(){
    LTitle LT=(LTitle)malloc(sizeof(*LT));
    LT->head=NULL;
    LT->N=0;
    return LT;
}
LTitle LTGet(LTitle LT,FILE *fin){
    char string[20];
    int N;

    fscanf(fin,"%s %d",string,&N);
    if(LTSearch(LT,string)){
        LT=LTMod(fin,LT,string,N);
        return LT;
    } else{
        LT=LTInsOrd(LT,fin,string,N);
        return LT;
    }
}
LTitle LTMod(FILE *fin,LTitle LT, char *string,int N){
    Title t=LTSearchGet(LT,string);
    t=Tmod(fin,t,N);
    return LT;
}
LTitle LTInsOrd (LTitle LT,FILE *fin,char *s,int N){
    link x, p;
    if (LT->head== NULL || CharL(s,GetName(LT->head->t))) {
        LT->head = newNode(fin, s, N, LT->head);
        LT->N++;
        return LT;
    }
    for (x=LT->head->next, p=LT->head;
         x!=NULL && CharL(GetName(x->t),s);
         p=x, x=x->next);
    p->next = newNode(fin,s,N,x);
    LT->N++;
    return LT;
}
static link newNode(FILE *fin, char* string,int N, link next){
    link x;
    x=malloc(sizeof(*x));
    x->t=Tload(fin,string,N);
    x->next=next;
    return x;
}
int LTSearch(LTitle LT, char *k){
    link x;
    for(x=LT->head;x!=NULL;x=x->next){
        if(strcmp(GetName(x->t),k)==0)
            return 1;
    }
    return 0;
}
Title LTSearchGet(LTitle LT, char *k){
    link x;
    for(x=LT->head;x!=NULL;x=x->next){
        if(strcmp(GetName(x->t),k)==0)
            return x->t;
    }
    return NULL;
}
void LTfree(LTitle LT){
    link x,p;
    for(x=LT->head->next,p=LT->head;x!=NULL;p=x,x=x->next){
        Tfree(p->t);
        free(p);
    }
    Tfree(p->t);
    free(p);
    free(LT);
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

int LTempty(LTitle LT){
    if(LT->head==NULL)
        return 1;
    return 0;
}
