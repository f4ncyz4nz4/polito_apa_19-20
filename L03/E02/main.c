#include <stdio.h>
int endianness(void);
void stampaCodifica (void *p, int size, int bigEndian);
int main() {
    int bigEndian;
    float  af;
    double ad;
    long double ald;
    printf("La dimensione della variabile float in bits = %d\n", 8*sizeof(float));
    printf("La dimensione della variabile double in bits = %d\n", 8*sizeof(double));
    printf("La dimensione della variabile long in bits = %d\n", 8*sizeof(long double));
    bigEndian=endianness();
    printf("Inserire un numero decimale\n");
    scanf("%Lf",&ald);
    //scanf("%lf",&ad);
    ad=((double)ald);
    af=(float)ald;
    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
    stampaCodifica((void *)&ald,sizeof(ald),bigEndian);
    return 0;
}
int endianness(void){
    int n;
    printf("Premere 1 per la codifica Big Endian, altrimenti 0\n");
    scanf("%d",&n);
    if(n==0)
        return 0;
    return 1;
}
void stampaCodifica (void *p, int size, int bigEndian){
    unsigned char *c;
    int i,j,k,ris[8*size];
    c=(unsigned  char *)p;
    for(i=0;i<8*size;i++)
        ris[i]=0;
    if(bigEndian){
        k=1;
    }
    else {
        k=-1;
        c+=size-1;
    }
    for(i=0;i<size;i++,c+=k){
        for(j=7;j>=0;j--){
            if(((*c) & 1)==0)
                ris[(i*8)+j]=0;
            else {
                ris[(i*8)+j] = 1;
            }
            (*c)=(*c) >> 1;
        }
    }
    i=0;
    switch (size) {
        case sizeof(float):
            printf("------------>Codifica a singola precisione");
            printf("\nSegno:\t");
            printf("%d",ris[i]);
            i++;
            printf("\nMantissa:\t");
            for(;i<9;i++){
                printf("%d",ris[i]);
            }
            printf("\nEsponente:\t");
            for(;i<32;i++){
                printf("%d",ris[i]);
            }
            break;
        case sizeof(double):
            printf("\n------------>Codifica a doppia precisione");
            printf("\nSegno:\t");
            printf("%d",ris[i]);
            i++;
            printf("\nMantissa:\t");
            for(;i<12;i++){
                printf("%d",ris[i]);
            }
            printf("\nEsponente:\t");
            for(;i<64;i++){
                printf("%d",ris[i]);
            }
            break;
        case sizeof(long double):
            printf("\n------------>Codifica a quadrupla precisione");
            printf("\nSegno:\t");
            printf("%d",ris[i]);
            i++;
            printf("\nMantissa:\t");
            for(;i<16;i++){
                printf("%d",ris[i]);
            }
            printf("\nEsponente:\t");
            for(;i<96;i++){
                printf("%d",ris[i]);
            }
            break;
        default:fprintf(stderr,"Errore");
    }
}