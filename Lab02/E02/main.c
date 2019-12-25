#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
#define DP 15
typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err}Comandi;
Comandi LeggiComando(void);
int SelezionaDati(Comandi codice,char altro[]);
void date(char info[]);
void partenze(char info[]);
void capolinea(char info[]);
void ritardo(char info[]);
void ritardotot(char info[]);
int DataConv(char data[]);
/*Esempio di come ho immaginato l'input del file corse
 * ---> B18 To Mi 21.05.19 6:40 8:30 5 <--- */
int main() {
    Comandi codice;
    int continua=1;
    char altro[MAX];

    while(continua){
        codice=LeggiComando();
        gets(altro);
        continua=SelezionaDati(codice,altro);
    }
    return 0;
}

Comandi LeggiComando(void){
    char comand[DP],*T[r_err]={"data","partenza","capolinea","ritardo","ritardo_totale","fine"};
    Comandi comando_e;

    fprintf(stdout,"Inserire le istruzioni (data//partenza//capolinea//ritardo//ritardo_totale)\n");
    fscanf(stdin,"%s",comand);
    comando_e=r_date;
    while(comando_e<r_err && strcmp(comand,T[comando_e])!=0){
        comando_e++;
    }
    return comando_e;
}
int SelezionaDati(Comandi codice,char altro[]){
    int continua=1;
    switch (codice){
        case r_date:date(altro);
            break;
        case r_partenza:partenze(altro);
            break;
        case r_capolinea:capolinea(altro);
            break;
        case r_ritardo:ritardo(altro);
            break;
        case r_ritardo_tot:ritardotot(altro);
            break;
        case r_fine:continua=0;
            break;
        default:
            fprintf(stderr,"Comando errato\n");
    }
    return continua;
}
void date(char info[]){
    FILE *fp;
    char data1[DP],data2[DP],datarif[DP],riga[MAX+1+1];
    int i,dim,d1,d2,dr;
    /*Apertura e gestione file*/
    fp=fopen("Corse.txt","r");
    if(fp==NULL) {
        fprintf(stderr,"Errore nell'apertura file\n");exit(-1);
    }
    sscanf(info,"%s %s",data1,data2);
    fscanf(fp,"%d%*c",&dim);
    d1=DataConv(data1);
    d2=DataConv(data2);
    for(i=0;i<dim;i++){
        fgets(riga,MAX+1+1,fp);
        sscanf(riga,"%*s %*s %*s %s",datarif);
        dr=DataConv(datarif);
        if(dr>=d1 && dr<=d2){
            fputs(riga,stdout);
        }
    }
    fprintf(stdout,"\n");
    fclose(fp);
}
void partenze(char info[]){
    FILE *fp;
    char partenza[DP],partenzarif[DP],riga[MAX+1+1];
    int i,dim;
    /*Apertura e gestione file*/
    fp=fopen("Corse.txt","r");
    if(fp==NULL) {
        fprintf(stderr,"Errore nell'apertura file\n");exit(-1);
    }
    sscanf(info,"%s",partenza);
    fscanf(fp,"%d%*c",&dim);
    for(i=0;i<dim;i++){
        fgets(riga,MAX+1+1,fp);
        sscanf(riga,"%*s %s",partenzarif);
        if(strcmp(partenza,partenzarif)==0){
            fputs(riga,stdout);
        }
    }
    fprintf(stdout,"\n");
    fclose(fp);
}
void capolinea(char info[]){
    FILE *fp;
    char capolinea[DP],capolinearif[DP],riga[MAX+1+1];
    int i,dim;
    /*Apertura e gestione file*/
    fp=fopen("Corse.txt","r");
    if(fp==NULL) {
        fprintf(stderr,"Errore nell'apertura file\n");exit(-1);
    }
    sscanf(info,"%s",capolinea);
    fscanf(fp,"%d%*c",&dim);
    for(i=0;i<dim;i++){
        fgets(riga,MAX+1+1,fp);
        sscanf(riga,"%*s %*s %s",capolinearif);
        if(strcmp(capolinea,capolinearif)==0){
            fputs(riga,stdout);
        }
    }
    fprintf(stdout,"\n");
    fclose(fp);
}
void ritardo(char info[]){
    FILE *fp;
    char data1[DP],data2[DP],datarif[DP],dest[DP],destrif[DP],riga[MAX+1+1];
    int i,dim,d1,d2,dr,rit;
    /*Apertura e gestione file*/
    fp=fopen("Corse.txt","r");
    if(fp==NULL) {
        fprintf(stderr,"Errore nell'apertura file\n");exit(-1);
    }
    sscanf(info,"%s %s %s",dest,data1,data2);
    fscanf(fp,"%d%*c",&dim);
    d1=DataConv(data1);
    d2=DataConv(data2);
    for(i=0;i<dim;i++){
        fgets(riga,MAX+1+1,fp);
        sscanf(riga,"%*s %*s %s %s %*s %*s %d",destrif,datarif,&rit);
        if(rit!=0 && strcmp(dest,destrif)==0) {
            dr = DataConv(datarif);
            if (dr >= d1 && dr <= d2) {
                fputs(riga, stdout);
            }
        }
    }
    fprintf(stdout,"\n");
    fclose(fp);
}
void ritardotot(char info[]){
    FILE *fp;
    char id[DP],idrif[DP],riga[MAX+1+1];
    int i,dim,rit,ritTot=0;
    /*Apertura e gestione file*/
    fp=fopen("Corse.txt","r");
    if(fp==NULL) {
        fprintf(stderr,"Errore nell'apertura file\n");exit(-1);
    }
    sscanf(info,"%s",id);
    fscanf(fp,"%d%*c",&dim);
    for(i=0;i<dim;i++){
        fgets(riga,MAX+1+1,fp);
        sscanf(riga,"%s %*s %*s %*s %*s %*s %d",idrif,&rit);
        if(strcmp(id,idrif)==0){
            ritTot+=rit;
        }
    }
    fprintf(stdout,"Il ritardo complessivo di %s = %d",id,ritTot);
    fprintf(stdout,"\n");
    fclose(fp);
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