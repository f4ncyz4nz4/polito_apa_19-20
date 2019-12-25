#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char **scelte;
    int n_scelte;
}Livello;
int princ_molt(int pos,Livello *val, char **sol,int n,int count);
int main() {
    int i,j,n,N,pos=0,count=0;
    char **sol,stringa[30];
    Livello *val;
    FILE *fp;
    fp=fopen("brani.txt","r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d%*c",&N);
    val=(Livello*)malloc(N* sizeof(Livello));
    sol=(char**)malloc(N* sizeof(char*));
    for(i=0;i<N;i++){
        fscanf(fp,"%d%*c",&n);
        val[i].n_scelte=n;
        val[i].scelte=(char**)malloc(n* sizeof(char*));
        for(j=0;j<n;j++) {
            fscanf(fp, "%s",stringa);
            val[i].scelte[j]=strdup(stringa);
        }
    }
    fclose(fp);
    count=princ_molt(pos,val,sol,N,count);
    printf("Le soluzioni sono %d\n",count);
    for(i=0;i<N;i++){
        free(val[i].scelte);
    }
    free(sol);
    free(val);
    return 0;
}
int princ_molt(int pos,Livello *val,char **sol,int n,int count){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++)
            printf("%s ",sol[i]);
        printf("\n");
        return count+1;
    }
    for(i=0;i<val[pos].n_scelte;i++){
        sol[pos]=(val[pos].scelte[i]);
        count=princ_molt(pos+1,val,sol,n,count);
    }
    return count;
}