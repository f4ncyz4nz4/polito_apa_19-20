#include <stdio.h>
#define MAX 30
int majority( int *a, int N);
int main() {
    int i,n,ris,vett[MAX];
    printf("Definire lunghezza del vettore\n");
    scanf("%d",&n);
    printf("Definire il vettore\n");
    for(i=0;i<n;i++)
        scanf("%d",&vett[i]);
    ris=majority(vett,n);
    if(ris==-1)
        printf("Non esiste elemento maggioritario\n");
    else
        printf("Elemento maggioritario = %d\n",ris);
    return 0;
}
int majority( int *a, int N){
    int i,occ1,occ2,cnt1=0,cnt2=0;
    //Il caso terminale è rappresentato da un solo elemento,
    // che è maggioritario
    if(N==1)
        return *a;
    //Divido il vettore in due
    occ1=majority(a,N/2);
    occ2=majority(a+(N/2),((N%2)==0) ? N/2:(N/2)+1);
    if(occ1==occ2)
        return occ1;
    //se non c'è un solo elemento maggioritario allora controlla
    // con un for di costo lineare
    if(occ1==-1) {
        for (i = 0; i < N; i++){
            if(occ2==a[i])
                cnt2++;
        }
        if(cnt2>(N/2))
            return occ2;
        return -1;
    }
    if(occ2==-1) {
        for (i = 0; i < N; i++){
            if(occ1==a[i])
                cnt1++;
        }
        if(cnt1>(N/2))
            return occ1;
        return -1;
    }
    if(occ1!=occ2) {
        for (i = 0; i < N; i++) {
            if (occ1 == a[i])
                cnt1++;
        }
        for (i = 0; i < N; i++) {
            if (occ2 == a[i])
                cnt2++;
        }
        if(cnt1==cnt2)
            return -1;
        else{
            if(cnt1>cnt2)
                return occ1;
            else
                return occ2;
        }
    }
}