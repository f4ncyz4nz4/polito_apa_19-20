#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 20
typedef struct{
    char paro[MAX];
    int in;
}Parole;
int ScorrieCopiaParola(char parola[],FILE *ft,Parole p[]);
int ConfrontaParola(FILE *ft,char testo[],char parola[]);
int main() {
    /*Utilizzo una struct per facilitarmi l'output*/
    FILE *fs,*ft;
    int i,j=0,dims;
    char sequenza[MAX];
    Parole parole[10];
    /*Apertua e gestione FILES*/
    fs=fopen("Sequenze.txt","r");
    if(fs==NULL){
        printf("Errore nell'apertura del file Sequenze");
        return -1;
    }
    ft=fopen("Testo.txt","r");
    if(ft==NULL){
        printf("Errore nell'apertura del file Testo");
        return -1;
    }
    /*Il programma prende una per una le parole del file "Sequenze" e le paragona
     * alle parole del file "Testo" fino alla fine dello stesso*/
    fscanf(fs,"%d",&dims);
    for(i=0;i<dims;i++){
        fscanf(fs,"%s",sequenza);
        /*Lo scorrimento delle parole e la loro copiatura viene gestito dalla
         * seguente funzione, tuttavia essa ne continene al suo interno un'ulteriore*/
        if(ScorrieCopiaParola(sequenza,ft,parole)){
            fprintf(stdout,"La sequenza ''%s'' viene contenuta in\n",sequenza);
            while ((j<10) && (parole[j].in!=-1)){
                fprintf(stdout,"--->%s (parola in posizione %d nel testo)\n",parole[j].paro,parole[j].in);
                j++;
            }
        }
        else
            fprintf(stdout,"La sequenza ''%s'' NON viene contenuta in nessuna parola\n",sequenza);
        j=0;
    }
    fclose(fs);
    fclose(ft);
    return 0;
}
int ScorrieCopiaParola(char parola[],FILE *ft,Parole p[]){
    int ind=0,i=0,cambiato=0,uguali=0;
    char testo[MAX];
    /*Inizializzo gli indici delle parole della struct a -1*/
    for (i = 0; i < 10; i++)
        p[i].in=-1;
    i=0;
    /*La ricerca delle occorrenze durerà al massimo 10 parole come indicato dalla consegna*/
    while((i<10) && (!feof(ft))) {
        uguali=ConfrontaParola(ft,testo,parola);
        /*Se la funzione "ConfrontaParola" ritorna vero, si memorizzerà la parola del file "Testo"
         * e il suo indice*/
        if(strlen(testo)>0)
            ind++;
        if (uguali) {
            p[i].in=ind;
            strcpy(p[i].paro,testo);
            i++;
            cambiato=1;
        }
    }
    rewind(ft);
    return cambiato;
}
int ConfrontaParola(FILE *ft,char testo[],char parola[]){
    char ca;
    int i=0,maiusc=-1,fine=0;
    /*Il primo blocco della funzione costruisce carattere per carattere
     * le parole testuali, evitando così la funzione "fscanf" che non
     * riconosce la punteggiatura*/
    /*Inotre si provvederà a portare in minuscolo tutte quelle lettere maiuscole,
     * (in modo che in fase di verifica la funzione "strstr" possa funzionare al meglio)
     * ma solo se anche la parola analizzata del file "Sequenze" è minuscola. Lei comanda*/
    /*Primo blocco*/
    while((!fine) && ((ca=fgetc(ft))!=EOF)){
        if(isalnum(ca)){
            if(islower(parola[0])){
                if(isupper(ca)){
                    ca=tolower(ca);
                    maiusc=i;
                }
            }
            testo[i]=ca;
        }
        else{
            if(isspace(ca) || ispunct(ca)) {
                testo[i] = '\0';
                fine=1;
            }
        }
        i++;
    }
    /*Il secondo blocco si occuperà invece di verificare l'occorrenza tra stringhe,
     * ritornando il valore"1" in caso di successo*/
    /*Alla riga 104-105 si riporterà a maiuscolo le lettere cambiate a riga 89.
     * Il motivo è semplicemente "per completezza e bellezza"*/
    /*Secondo blocco*/
    if((!feof(ft)) && strstr(testo,parola)){
        if(maiusc!=-1)
            testo[maiusc]=toupper(testo[maiusc]);
        return 1;
    }
    return 0;
}
