#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DP 20
typedef struct{
    char *cod;
    char *s_part;
    char *s_arr;
    char *data;
    char *o_part;
    char *o_arr;
    int rit;
}Tratta;
typedef enum {stampa, leggi, o_data, o_tratta, o_partenza, o_arrivo, ricerca, fine, err}Comandi;
Comandi LeggiComando(void);
int Lettura(Tratta **tratta,Tratta ***punt_tr,Tratta ***punt_par,Tratta ***punt_arr,Tratta ***punt_data,char file[]);
int DataConv(char data[]);
int OraConv(char ora[]);
int Sort(Tratta ***punt,int N,int caso);
void Ricerca(Tratta ***punt,int N,int ordinato);
int strstrparziale(Tratta ***punt,char stringa[],int z);
int Libera(Tratta **tratta,Tratta ***punt_tr,Tratta ***punt_par,Tratta ***punt_arr,Tratta ***punt_data);
int main() {
    Comandi codice;
    Tratta *tratta=NULL,**punt_tr=NULL,**punt_par=NULL,**punt_arr=NULL,**punt_data=NULL;
    int continua=1,N,i,ordinato=0,stamp=0;
    FILE *fp;
    char *stringa,tmp[30];
    N=Lettura(&tratta,&punt_tr,&punt_par,&punt_arr,&punt_data,"Corse.txt");
    while(continua){
        codice=LeggiComando();
        switch (codice) {
            case stampa:
                printf("1 Stampa a video\n2 Stampa su file\n");
                scanf("%d",&stamp);
                if(stamp==1){
                    fp=stdout;
                } else
                    fp=fopen("Corseord.txt","w");
                fprintf(stdout,"1 Stampa per tratta\n2 Stampa per st. di partenza\n3 Stampa per st. di arrivo\n4 Stampa per data\n");
                fscanf(stdin,"%d",&stamp);
                switch (stamp){
                    case 1:for(i=0;i<N;i++) {
                            fprintf(fp, "%s %s %s %s %s %s %d\n", punt_tr[i]->cod, punt_tr[i]->s_part, punt_tr[i]->s_arr, punt_tr[i]->data,punt_tr[i]->o_part, punt_tr[i]->o_arr, punt_tr[i]->rit);
                        }
                        break;
                    case 2:for(i=0;i<N;i++) {
                            fprintf(fp, "%s %s %s %s %s %s %d\n", punt_par[i]->cod, punt_par[i]->s_part, punt_par[i]->s_arr, punt_par[i]->data,punt_par[i]->o_part, punt_par[i]->o_arr, punt_par[i]->rit);
                        }
                        break;
                    case 3:for(i=0;i<N;i++) {
                            fprintf(fp, "%s %s %s %s %s %s %d\n", punt_arr[i]->cod, punt_arr[i]->s_part, punt_arr[i]->s_arr, punt_arr[i]->data,punt_arr[i]->o_part, punt_arr[i]->o_arr, punt_arr[i]->rit);
                        }
                        break;
                    case 4:for(i=0;i<N;i++) {
                            fprintf(fp, "%s %s %s %s %s %s %d\n", punt_data[i]->cod, punt_data[i]->s_part, punt_data[i]->s_arr, punt_data[i]->data,punt_data[i]->o_part, punt_data[i]->o_arr, punt_data[i]->rit);
                        }
                        break;
                    default:
                        fprintf(stderr, "Comando errato\n");
                }
                break;
            case leggi:
                fprintf(stdout,"Scrivere il nome del file su cui leggere\n");
                fscanf(stdin,"%s",tmp);
                stringa=strdup(tmp);
                Libera(&tratta,&punt_tr,&punt_par,&punt_arr,&punt_data);
                N=Lettura(&tratta,&punt_tr,&punt_par,&punt_arr,&punt_data,stringa);
                free(stringa);
                break;
            case o_data:
                Sort(&punt_data,N,0);
                break;
            case o_tratta:
                Sort(&punt_tr,N,1);
                break;
            case o_partenza:
                ordinato=Sort(&punt_par,N,2);
                break;
            case o_arrivo:
                Sort(&punt_arr,N,3);
                break;
            case ricerca:
                Ricerca(&punt_par,N,ordinato);
                break;
            case fine:
                continua = 0;
                break;
            default:
                fprintf(stderr, "Comando errato\n");
        }
    }
    return 0;
}
int Lettura(Tratta **tratta,Tratta ***punt_tr,Tratta ***punt_par,Tratta ***punt_arr,Tratta ***punt_data,char file[]){
    int i,N;
    char tmp[30];
    FILE *fp;
    fp=fopen(file,"r");
    if(fp==NULL)
        exit(-1);
    fscanf(fp,"%d%*c",&N);
    *tratta=(Tratta*)malloc(N* sizeof(Tratta));
    *punt_tr=(Tratta**)malloc(N* sizeof(Tratta*));
    *punt_par=(Tratta**)malloc(N* sizeof(Tratta*));
    *punt_arr=(Tratta**)malloc(N* sizeof(Tratta*));
    *punt_data=(Tratta**)malloc(N* sizeof(Tratta*));
    for(i=0;i<N;i++) {
        fscanf(fp,"%s",tmp);
        (*tratta)[i].cod=strdup(tmp);
        fscanf(fp,"%s",tmp);
        (*tratta)[i].s_part=strdup(tmp);
        fscanf(fp,"%s",tmp);
        (*tratta)[i].s_arr=strdup(tmp);
        fscanf(fp,"%s",tmp);
        (*tratta)[i].data=strdup(tmp);
        fscanf(fp,"%s",tmp);
        (*tratta)[i].o_part=strdup(tmp);
        fscanf(fp,"%s",tmp);
        (*tratta)[i].o_arr=strdup(tmp);
        fscanf(fp,"%d",&((*tratta)[i].rit));
    }
    for(i=0;i<N;i++) {
        (*punt_tr)[i] = (*punt_arr)[i] = (*punt_par)[i] = (*punt_data)[i] = &(*tratta)[i];
    }
    fclose(fp);
    return N;
}
Comandi LeggiComando(void){
    char comand[DP],*T[err]={"stampa","leggi","o_data","o_tratta","o_partenza","o_arrivo","ricerca","fine"};
    Comandi comando_e;
    fprintf(stdout,"Inserire le istruzioni(stampa,leggi,o_data,o_tratta,o_partenza,o_arrivo,ricerca,fine)\n");
    fscanf(stdin,"%s",comand);
    comando_e=stampa;
    while(comando_e<err && strcmp(comand,T[comando_e])!=0){
        comando_e++;
    }
    return comando_e;
}
int Sort(Tratta ***punt,int N,int caso){
    int i,j,ordinato=0;
    Tratta *tmp;
    //Metodo di ordinamento: BUBBLE SORT
    for(i=0;i<N-1;i++){
        for(j=0;j<(N-1)-i;j++){
            switch (caso){
                case 0:
                    if(DataConv((*punt)[j]->data)>DataConv((*punt)[j+1]->data)){
                        tmp=(*punt)[j];
                        (*punt)[j]=(*punt)[j+1];
                        (*punt)[j+1]=tmp;
                    }else if(DataConv((*punt)[j]->data)==DataConv((*punt)[j+1]->data)){
                        if(OraConv((*punt)[j]->o_part)>OraConv((*punt)[j+1]->o_part)){
                            tmp=(*punt)[j];
                            (*punt)[j]=(*punt)[j+1];
                            (*punt)[j+1]=tmp;
                        }
                        else if(OraConv((*punt)[j]->o_part)==OraConv((*punt)[j+1]->o_part)){
                            if(OraConv((*punt)[j]->o_arr)>OraConv((*punt)[j+1]->o_arr)){
                                tmp=(*punt)[j];
                                (*punt)[j]=(*punt)[j+1];
                                (*punt)[j+1]=tmp;
                            }
                        }
                    }
                    break;
                case 1:
                    if(strcmp((*punt)[j]->cod,(*punt)[j+1]->cod)>0){
                        tmp=(*punt)[j];
                        (*punt)[j]=(*punt)[j+1];
                        (*punt)[j+1]=tmp;
                    }
                    break;
                case 2:
                    if(strcmp((*punt)[j]->s_part,(*punt)[j+1]->s_part)>0){
                        tmp=(*punt)[j];
                        (*punt)[j]=(*punt)[j+1];
                        (*punt)[j+1]=tmp;
                    }
                    ordinato=1;
                    break;
                case 3:
                    if(strcmp((*punt)[j]->s_arr,(*punt)[j+1]->s_arr)>0){
                        tmp=(*punt)[j];
                        (*punt)[j]=(*punt)[j+1];
                        (*punt)[j+1]=tmp;
                    }
                    break;
                default: fprintf(stderr,"ERRORE");
            }
        }
    }
    return ordinato;
}
void Ricerca(Tratta ***punt,int N,int ordinato){
    int i,r,l,m,k,trovato=0;
    char stringa[DP];
    fprintf(stdout,"Digitare la stazione di partenza da ricercare\n");
    scanf("%s",stringa);
    switch(ordinato){
        case 0:
            for(i=0;i<N;i++){
                if(strstrparziale(punt,stringa,i)) {
                    fprintf(stdout, "%s %s %s %s %s %s %d\n", (*punt)[i]->cod, (*punt)[i]->s_part, (*punt)[i]->s_arr, (*punt)[i]->data,
                            (*punt)[i]->o_part, (*punt)[i]->o_arr, (*punt)[i]->rit);
                    trovato = 1;
                }
            }
            if(!trovato)
                fprintf(stderr,"Stazione non trovata\n");
            break;
        case 1:
            l=0;r=N-1;
            while((l <= r) && !trovato){
                m = (l+r)/2;
                if(strstrparziale(punt,stringa,m)){
                    trovato=1;
                    fprintf(stdout, "%s %s %s %s %s %s %d\n", (*punt)[m]->cod, (*punt)[m]->s_part, (*punt)[m]->s_arr, (*punt)[m]->data,
                            (*punt)[m]->o_part, (*punt)[m]->o_arr, (*punt)[m]->rit);
                    for(k=m+1;k<=r;k++){
                        if(strstrparziale(punt,stringa,k)) {
                            fprintf(stdout, "%s %s %s %s %s %s %d\n", (*punt)[k]->cod, (*punt)[k]->s_part, (*punt)[k]->s_arr, (*punt)[k]->data,
                                    (*punt)[k]->o_part, (*punt)[k]->o_arr, (*punt)[k]->rit);
                        }
                    }
                    for(k=m-1;k>=l;k--){
                        if(strstrparziale(punt,stringa,k)) {
                            fprintf(stdout, "%s %s %s %s %s %s %d\n", (*punt)[k]->cod, (*punt)[k]->s_part, (*punt)[k]->s_arr, (*punt)[k]->data,
                                    (*punt)[k]->o_part, (*punt)[k]->o_arr, (*punt)[k]->rit);
                        }
                    }
                }
                if(strcmp((*punt)[m]->s_part,stringa)<0)
                    l = m+1;
                else
                    r = m-1;
            }
            if(!trovato)
                fprintf(stderr,"Stazione non trovata\n");
            break;
        default: fprintf(stderr,"ERRORE");
    }
}
int strstrparziale(Tratta ***punt,char stringa[],int z){
    unsigned int i;
    for(i=0;i<(strlen(stringa));i++){
        if(((*punt)[z]->s_part)[i]!=stringa[i])
            return 0;
    }
    return 1;
}
int DataConv(char data[]){
    int gg,mm,aa,tot,M=31;
    sscanf(data,"%d.%d.%d",&gg,&mm,&aa);
    if(mm==4 || mm==6 || mm==9 || mm==11)
        M=30;
    else if(mm==2)
        M=28;
    tot=(aa*365)+(mm*M)+(gg);
    return tot;
}
int OraConv(char ora[]){
    int hh,mm;
    sscanf(ora,"%d:%d",&hh,&mm);
    return mm+(60*hh);
}
int Libera(Tratta **tratta,Tratta ***punt_tr,Tratta ***punt_par,Tratta ***punt_arr,Tratta ***punt_data){
    free(*tratta);
    free(*punt_tr);
    free(*punt_par);
    free(*punt_arr);
    free(*punt_data);
}