#include <stdio.h>
#include <stdlib.h>
typedef struct tratto{
    char colore;
    int punteggio;
}tratto_t;
typedef struct tessera{
    tratto_t oriz,vert;
    int in;
}tessera_t;


tessera_t ruotaTessera(tessera_t t);
tessera_t tessera_void(void);
void salvaTessere(FILE *tiles,int tessere_tot,tessera_t *tessere);
void salvaScacchiera(FILE *board,tessera_t **scacchiera_i,tessera_t *tessere,int R,int C,int *num_scelte);
int disp_sempl(int pos, tessera_t *tessere_val, tessera_t *tessere_sol,
               tessera_t **scacchiera_i,int *mark, int n_tessere_val, int num_scelte, int count,
               int R,int C,int *maxPunti,tessera_t **max_scacchiera);
int rigaValida(tessera_t **scacchiera_i,int i,int C);
int colonnaValida(tessera_t **scacchiera_i,int j,int R);
int calcolaPunteggioRiga(tessera_t **scacchiera_i,int i,int C);
int calcolaPunteggioColonna(tessera_t **scacchiera_i,int j,int R);
void salvaScacchieraMigliore(tessera_t **scacchiera_i,tessera_t **max_scacchiera,int R,int C);

int main() {
    FILE *tiles,*board;
    tessera_t *tessere,**scacchiera_i,**max_scacchiera,*tessere_sol,*tessere_val;
    int tessere_tot,R,C,i,j,dim_val=1,num_scelte=0,count,*mark,max_punti=-1;

    tiles=fopen("tiles.txt","r");
    board = fopen("board.txt","r");
    if(tiles==NULL||board==NULL)
        return -3;

    fscanf(tiles,"%d\n",&tessere_tot);
    tessere = (tessera_t *)malloc(tessere_tot* sizeof(tessera_t));
    salvaTessere(tiles,tessere_tot,tessere);

    fscanf(board,"%d %d\n",&R,&C);
    scacchiera_i = (tessera_t **)malloc(R*sizeof(tessera_t *));
    max_scacchiera = (tessera_t **)malloc(R*sizeof(tessera_t *));
    for(i=0;i<C;i++){
        scacchiera_i[i] = (tessera_t *)malloc(C* sizeof(tessera_t));
        max_scacchiera[i] = (tessera_t *)malloc(C* sizeof(tessera_t));
    }
    salvaScacchiera(board,scacchiera_i,tessere,R,C,&num_scelte);

    tessere_val=(tessera_t *)malloc(tessere_tot* sizeof(tessera_t));
    /*Conto il numero di tessere disponibili per essere posizionate*/
    for(i=0,j=0;i<tessere_tot;i++){
        if(tessere[i].in==-1){
            dim_val++;
            tessere_val[j++]=tessere[i];
        }
    }

    mark = (int *)calloc((dim_val-1),sizeof(int));
    tessere_sol = (tessera_t *)malloc((num_scelte)*sizeof(tessera_t));
    count=disp_sempl(0,tessere_val,tessere_sol,scacchiera_i,mark,dim_val-1,num_scelte,0,R,C,&max_punti,max_scacchiera);

    /*Stampo la scacchiera a punteggio massimo*/
    for(i=0;i<R;i++){
        for(j=0;j<C;j++) {
            printf("%c/%d %c/%d\t", max_scacchiera[i][j].oriz.colore, max_scacchiera[i][j].oriz.punteggio,
                   max_scacchiera[i][j].vert.colore, max_scacchiera[i][j].vert.punteggio);
        }
        printf("\n");
    }
    printf("Punteggio %d",max_punti);

    /*Dealloco vettori e matrici e chiudo i file*/
    fclose(tiles);
    fclose(board);
    free(tessere);
    free(tessere_val);
    free(tessere_sol);
    free(mark);
    for(i=0;i<C;i++) {
        free(scacchiera_i[i]);
        free(max_scacchiera[i]);
    }
    free(scacchiera_i);
    free(max_scacchiera);
    return 0;
}
void salvaTessere(FILE *tiles,int tessere_tot,tessera_t *tessere){
    int i;
    for(i=0;i<tessere_tot;i++){
        fscanf(tiles,"%c %d %c %d\n",&tessere[i].oriz.colore,&tessere[i].oriz.punteggio,
               &tessere[i].vert.colore,&tessere[i].vert.punteggio);
        tessere[i].in=-1;
    }

}
void salvaScacchiera(FILE *board,tessera_t **scacchiera_i,tessera_t *tessere,int R,int C,int *num_scelte){
    int i,j,t_i,r;
    for(i=0;i<R;i++){
        for(j=0;j<C;j++){
            fscanf(board,"%d/%d",&t_i,&r);
            if(t_i==-1){
                scacchiera_i[i][j] = tessera_void();/*La scacchiera iniziale presenterà delle tessere vuote con in=-1 nei punti dove andranno inserite quelle nuove*/
                (*num_scelte)++;
            }
            else{
                if(r==0){
                    tessere[t_i].in=1;/*Marco quella tessera come parte della configurazione iniziale*/
                    scacchiera_i[i][j] = tessere[t_i];
                }
                else {
                    tessere[t_i].in=1;
                    scacchiera_i[i][j]=ruotaTessera(tessere[t_i]);
                }
            }
        }
    }

}
tessera_t ruotaTessera(tessera_t t){
    tratto_t temp;

    temp = t.vert;
    t.vert = t.oriz;
    t.oriz = temp;
    return t;
}
int disp_sempl(int pos, tessera_t *tessere_val, tessera_t *tessere_sol,
               tessera_t **scacchiera_i,int *mark, int n_tessere_val, int num_scelte, int count,
               int R,int C,int *maxPunti,tessera_t **max_scacchiera){
    int i,j,k=0,punti=0;
    if (pos >= num_scelte) {
        /*Riempo la matrice con il vettore tessere_sol generato*/
        for(i=0;i<R;i++){
            for(j=0;j<C;j++){
                if(scacchiera_i[i][j].in==-1) scacchiera_i[i][j]=tessere_sol[k++];
            }
        }
        /*Controllo di validità e calcolo dei punteggi*/
        for(i=0;i<R;i++){
            if(rigaValida(scacchiera_i,i,C)){
                punti+=calcolaPunteggioRiga(scacchiera_i,i,C);
            }
        }
        for(j=0;j<C;j++){
            if(colonnaValida(scacchiera_i,j,R))punti+=calcolaPunteggioColonna(scacchiera_i,j,R);
        }
        /*Verifica di ottimalità*/
        if(punti>*maxPunti) {
            *maxPunti = punti;
            salvaScacchieraMigliore(scacchiera_i,max_scacchiera,R,C);
        }
        return count+1;
    }

    for (i=0; i<n_tessere_val; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            /*Marco l'elemento come preso, ricorro senza ruotare la tessera e poi ricorro ruotandola,dopodichè smarco tale elemento*/
            tessere_sol[pos] = tessere_val[i];
            count = disp_sempl(pos+1, tessere_val, tessere_sol,scacchiera_i,mark,n_tessere_val,num_scelte,count,R,C,maxPunti,max_scacchiera);
            tessere_sol[pos] = ruotaTessera(tessere_val[i]);
            count = disp_sempl(pos+1, tessere_val, tessere_sol,scacchiera_i,mark,n_tessere_val,num_scelte,count,R,C,maxPunti,max_scacchiera);
            mark[i] = 0;
        }
    }
    return count;
}
tessera_t tessera_void(void){
    tessera_t t;
    t.oriz.colore=' ';
    t.oriz.punteggio=-1;
    t.vert.colore=' ';
    t.vert.punteggio=-1;
    t.in=-1;
    return t;
}
int rigaValida(tessera_t **scacchiera_i,int i,int C){
    int j;
    char colore = scacchiera_i[i][0].oriz.colore;/*colore di riferimento*/
    for(j=1;j<C;j++){
        if(scacchiera_i[i][j].oriz.colore!=colore) return 0;
    }
    return 1;
}
int colonnaValida(tessera_t **scacchiera_i,int j,int R){
    int i;
    char colore = scacchiera_i[0][j].vert.colore;/*colore di riferimento*/
    for(i=1;i<R;i++){
        if(scacchiera_i[i][j].vert.colore!=colore) return 0;
    }
    return 1;
}
int calcolaPunteggioRiga(tessera_t **scacchiera_i,int i,int C){
    int j,count=0;
    for(j=0;j<C;j++)count+=scacchiera_i[i][j].oriz.punteggio;
    return count;
}
int calcolaPunteggioColonna(tessera_t **scacchiera_i,int j,int R){
    int i,count=0;
    for(i=0;i<R;i++)count+=scacchiera_i[i][j].vert.punteggio;
    return count;
}
void salvaScacchieraMigliore(tessera_t **scacchiera_i,tessera_t **max_scacchiera,int R,int C){
    int i,j;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            max_scacchiera[i][j] = scacchiera_i[i][j];
        }
    }
}