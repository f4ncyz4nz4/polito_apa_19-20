//
// Created by loren on 09/01/2020.
//

#include "data.h"

Data dataload(FILE *fin){
    Data d;
    fscanf(fin,"%d/%d/%d %d:%d",&d.aa,&d.mm,&d.gg,&d.h,&d.min);

    return d;
}
int DataCmp(Data a,Data b){
    int A,B;
    if(a.aa==b.aa && a.mm==b.mm && a.gg==b.gg)
        return 0;
    A=(a.aa*365)+(a.mm*30)+(a.gg);
    B=(b.aa*365)+(b.mm*30)+(b.gg);
    if(A>B)
        return 1;
    else
        return -1;
}
void Dataprint(FILE *fout,Data a){
    fprintf(fout,"%d/%d/%d %d:%d   ",a.aa,a.mm,a.gg,a.h,a.min);
}
Data Datascan(FILE *fin){
    Data a;
    fscanf(fin,"%d/%d/%d %d:%d",&a.aa,&a.mm,&a.gg,&a.h,&a.min);
    return a;
}
Data DataNULL(){
    Data d;
    d.aa=0;d.mm=0;d.gg=0;d.min=0;d.h=0;
    return d;
}
Data DataMax(){
    Data d;
    d.aa=3000;d.mm=30;d.gg=20;d.min=0;d.h=0;
    return d;
}
Data DataMin(){
    Data d;
    d.aa=0;d.mm=30;d.gg=30;d.min=0;d.h=0;
    return d;
}

