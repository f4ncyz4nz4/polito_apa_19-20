#include <stdio.h>

#define MAX 20
void ShellSort(int A[], int N);
void InsertionSort(int A[], int N);
void SelectionSort(int A[], int N);
void DisordinaVett(int vett[],int copia[],int N);

int main() {
    int i,j,dimparole=0,lung=0,vetts[MAX],vetcopy[MAX];
    FILE *fp;

    /*Apertura e gestione file*/
    fp=fopen("sort.txt","r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d",&dimparole);
    for(i=0;i<dimparole;i++){
        fscanf(fp,"%d",&lung);
        for(j=0;j<lung;j++){
            fscanf(fp,"%d",&vetts[j]);
        }
        printf("-------->SEQUENZA %d N=%d\n",i+1,lung);
        DisordinaVett(vetts,vetcopy,lung);
        InsertionSort(vetcopy,lung);
        DisordinaVett(vetts,vetcopy,lung);
        SelectionSort(vetcopy,lung);
        DisordinaVett(vetts,vetcopy,lung);
        ShellSort(vetcopy,lung);
    }
    return 0;
}

void InsertionSort(int A[], int N) {
    int i, j, l=0, r=N-1,x,numscambi=0,itest=0,itint=0,itintc=0,ittot=0;
    for(i = l+1; i <= r; i++,itest++) {
        x = A[i];
        j = i - 1;
        while (j >= l && x<A[j]) {
            A[j+1] = A[j];
            numscambi++;
            j--;
            itintc++;
        }
        itint=itintc;
        itintc=0;
        A[j+1] = x;
    }
    ittot=itest*itint;
    printf("Insertion Sort\nNumero scambi=%d, Iterazioni ciclo esterno=%d, Iterazioni ciclo interno=%d, Iterazioni totali=%d\n",numscambi,itest,itint,ittot);
}
void SelectionSort(int A[], int N) {
    int i, j, l=0, r=N-1, min, temp,numscambi=0,itest=0,itint=0,itintc=0,ittot=0,o=0;
    for(i = l; i < r; i++,itest++) {
        min = i;
        for (j = i + 1; j <= r; j++,itintc++) {
            if (A[j] < A[min])
                min = j;
        }
        if (min !=i) {
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
            numscambi++;
        }
        if(o==0) {
            itint = itintc;
            o=1;
        }
    }
    ittot=itest*itint;
    printf("Selection Sort\nNumero scambi=%d, Iterazioni ciclo esterno=%d, Iterazioni ciclo interno=%d, Iterazioni totali=%d\n",numscambi,itest,itint,ittot);
}
void ShellSort(int A[], int N) {
    int i, j, h=1, l=0,o=0, r= N-1,tmp,numscambi=0,itest=0,itint=0,itintc=0,ittot=0;
    while (h < N/3)
        h = 3*h+1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++,itest++) {
            j = i;
            tmp = A[i];
            while(j >= l + h  && tmp<A[j-h]) {
                A[j] = A[j-h];
                j -=h;
                numscambi++;
                itintc++;
            }
            A[j] = tmp;
            if(o==0) {
                itint = itintc;
                o=1;
            }
        }
        h = h/3;
    }
    ittot=itest*itint;
    printf("Shell Sort\nNumero scambi=%d, Iterazioni ciclo esterno=%d, Iterazioni ciclo interno=%d, Iterazioni totali=%d\n",numscambi,itest,itint,ittot);
}

void DisordinaVett(int vett[],int copia[],int N){
    for (int i = 0; i < N; ++i) {
        copia[i]=vett[i];
    }
}