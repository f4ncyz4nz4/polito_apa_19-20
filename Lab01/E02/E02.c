#include <stdio.h>
#include <string.h>
#define MAX 30

void AnalisieScritturaParola(char word[],FILE* fpnew,FILE* fpdiz);

int main() {
    FILE *fpsorg,*fpnew,*fpd;
    char parola[MAX],carattere;

    /*Apertura Files e gestione*/
    fpsorg=fopen("sorgente.txt","r");
    if(fpsorg==NULL){
        printf("Errore nell'apertura del file sorgente");
        return -1;
    }
    fpnew=fopen("ricodificato.txt","w");
    if(fpnew==NULL){
        printf("Errore nell'apertura del file da sovrascrivere");
        return -1;
    }
    fpd=fopen("dizionario.txt","r");
    if(fpd==NULL){
        printf("Errore nell'apertura del file dizionario");
        return -1;
    }

    while(fscanf(fpsorg,"%s%c",parola,&carattere)!=EOF){
        AnalisieScritturaParola(parola,fpnew,fpd);
        fprintf(fpnew, "%c",carattere);
    }
    fclose(fpnew);
    fclose(fpsorg);
    fclose(fpd);
    return 0;
}

void AnalisieScritturaParola(char word[],FILE* fpnew,FILE* fpdiz){
    int i,j=0,dimdiz,dimo,dims,dimw,diverso=0,k,trovato=0;
    char sost[MAX],orig[MAX];

    /*Prendo i dati in input*/
    dimw=strlen(word);
    fscanf(fpdiz,"%d%*c",&dimdiz);
    for(i=0;i<dimdiz ;i++){
        fscanf(fpdiz,"%s %s",sost,orig);
        dimo=strlen(orig);
        dims=strlen(sost);
        /*Guardo preliminarmente se c'è corrispondenza tra dizionario e parola originale
         * SE C'È...*/
        if(strstr(word,orig)){
            trovato=0;
            for(;j<dimw && trovato==0;j++){
                /*Guardo la prima lettera della parola originale, se è diversa la scrivo
                 * e la sostituisco con il carattere 'asterisco'*/
                if(orig[0]!=word[j]){
                    fprintf(fpnew, "%c",word[j]);
                    word[j]='*';
                }
                /*Se è uguale invece mi assicuro che sia davvero lei la parola*/
                else{
                    for(k=0;k<dimo && k+j<dimw && k<dimw;k++){
                        if(word[k+j]!=orig[k])
                            diverso=1;
                    }
                    /*Se è lei mi scrivo la parola sostitutiva nel file ($...$) */
                    if(!diverso){
                        for(k=0;k<dims;k++)
                            fprintf(fpnew, "%c",sost[k]);
                        /*E sostituisco la sottostringa della parola originale
                         * con una sequenza di caratteri 'asterisco' */
                        for(k=0;k<dimo;k++){
                            word[j+k]='*';
                        }
                        j=j+dimo-1;
                        trovato=1;
                    }
                    /*nel MALAUGURATO caso in cui alcune lettere corrispondano ma la parola
                     * complessivamente sia diversa, eseguo lo stesso comando di riga 57 e 58.
                     * Il tutto grazie all'uso dell'indice j, importantissimo perchè
                     * scorre mano a mano che si analizza la parola data*/
                    else{
                        fprintf(fpnew, "%c",word[j]);
                        word[j]='*';
                        diverso=0;
                    }
                }
            }
            i=0;
            /*dovendo poi tener conto delle ricorrenze ogni volta che trovo una parola,
             * ri-inizio da capo azzerando 'i' e ripristinando il puntatore al file 'dizionario' */
            rewind(fpdiz);
            fscanf(fpdiz,"%*d%*c");
        }
        /*Essendo 'j' inizialmente uguale a '0' allora con il comando
         * a riga 102 fino a 104 otterrò un duplice effetto:
         *        --SE NON C'È nessuna sottostringa, allora stampa la parola normale
         *        --Se invece dopo una qualsiasi parola da sostituire ci sono altre lettere allora
         *           verranno stampate quelle dato che l'indice 'j' continuerà a puntare l'ultimo carattere
         *           analizzato, della parola originale*/
    }
    for(;j<dimw;j++){
        if(word[j]!='*'){
            fprintf(fpnew, "%c", word[j]);
        }
    }
    rewind(fpdiz);
}
