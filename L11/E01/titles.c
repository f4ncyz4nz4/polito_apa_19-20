//
// Created by loren on 08/01/2020.
//

#include "titles.h"

struct titolo{
    char *nome;
    BST quot_g;
};
static int QBload(FILE *fin, float *qb,int cnt);

char* GetName(Title t){
    return t->nome;
}

void TsearchQ(FILE *fout, Title t){
    float key;
    Data data;
    printf("Inserire il valore della quotazione da cercare\n");
    scanf("%f",&key);
    data=BSTsearch(t->quot_g,key);
    if(DataCmp(data,DataNULL())==0){
        fprintf(fout,"Quotazione non trovata\n");
        return;
    }
    fprintf(fout,"Quotazione trovata in data:");
    Dataprint(fout,data);
    fprintf(fout,"\n");
}
void TsearchMaxMin(FILE *fout, Title t){
    float max,min;
    int cmd;
    Data i,f;
    printf("(0)Max e Min nell'intero periodo\n"
           "(1)Max e Min in un periodo specifico\n");
    scanf("%d",&cmd);
    if(cmd==0){
        max=BSTVisitMax(t->quot_g,DataMin(),DataMax());
        min=BSTVisitMin(t->quot_g,DataMin(),DataMax());
        printf("Valore Massimo=\t%f\n"
               "Valore Minimo=\t%f\n",max,min);
    } else{
        printf("Inserire le date entro le quali cercare il minimo e il massimo\n");
        i=Datascan(fout);
        f=Datascan(fout);
        max=BSTVisitMax(t->quot_g,i,f);
        min=BSTVisitMin(t->quot_g,i,f);
        printf("Valore Massimo=\t%f\n"
               "Valore Minimo=\t%f\n",max,min);
    }
}
void Tprint(FILE *fout, Title t){
    if(t==NULL){
        fprintf(fout,"Titolo non trovato\n");
        return;
    }
    fprintf(fout,"%s\n",t->nome);
    BSTvisit(fout,t->quot_g);
}

Title Tload(FILE *fin,char *string,int N){
    int i,cnt=0;
    Title t;
    Data data,datas;
    float qb=0;
    t=(Title)malloc(sizeof(*t));
    t->nome=strdup(string);
    t->quot_g = BSTinit();
    data = dataload(fin);
    cnt = QBload(fin, &qb, cnt);
    for(i=0;i<N-1;i++) {
        if (DataCmp(datas = dataload(fin), data)==0) {
            cnt = QBload(fin, &qb,cnt);
        } else{
            qb=qb/(float)cnt;
            BSTinsert_leafR(t->quot_g, qb,data);
            qb=0;
            data=datas;
            cnt=0;
            cnt = QBload(fin, &qb,cnt);
        }
    }
    qb=qb/(float)cnt;
    BSTinsert_leafR(t->quot_g, qb,data);
    return t;
}
Title Tmod(FILE *fin,Title t,int N){
    int i,cnt=0;
    Data data,datas;
    float qb=0;

    data = dataload(fin);
    cnt = QBload(fin, &qb, cnt);
    for(i=0;i<N-1;i++) {
        if (DataCmp(datas = dataload(fin), data)==0) {
            cnt = QBload(fin, &qb,cnt);
        } else{
            qb=qb/(float)cnt;
            BSTinsert_leafR(t->quot_g, qb,data);
            qb=0;
            data=datas;
            cnt=0;
            cnt = QBload(fin, &qb,cnt);
        }
    }
    qb=qb/(float)cnt;
    BSTinsert_leafR(t->quot_g, qb,data);
    return t;
}

void TsearchB(Title t,int s){
    if(CamMM(t->quot_g,s))
        BSTbalance(t->quot_g);
}

static int QBload(FILE *fin, float *qb, int cnt){
    int val,n;

    fscanf(fin,"%d %d%*c",&val,&n);
    (*qb)+=(float)(val*n);
    cnt+=n;
    return cnt;
}

void Tfree(Title t){
    free(t->nome);
    BSTfree(t->quot_g);
}
