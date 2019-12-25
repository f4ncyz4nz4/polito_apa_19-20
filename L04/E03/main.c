#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 30
char *cercaRegexp(char *src, char *regexp);
int main() {
    int i,esiste=0;
    char stringa[MAX],espreg[MAX],*occorrenza;
    FILE *fp;
    fp=fopen("Testo.txt","r");
    if(fp==NULL)
        return -1;
    fprintf(stdout,"Inserire l'espressione regolare\n");
    fscanf(stdin,"%s",espreg);
    while((fscanf(fp,"%s",stringa)!=EOF)){
        for(i=0;i<strlen(stringa);i++) {
            if ((occorrenza = cercaRegexp(stringa+i, espreg)) != NULL) {
                fprintf(stdout, "%s\n", occorrenza);
                esiste = 1;
                //break;
                //Facoltativo nel caso si volesse prendere solo una occorrenza da una singola parola,
                // e non di più (si veda il caso dell'espressione regolare ".")
            }
        }
    }
    if(!esiste)
        fprintf(stdout,"Nessuna occorrenza trovata\n");
    fclose(fp);
    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int cnt=0,i,dim=0,flag=0;
    while(*regexp!='\0') {
        if (isalpha(*regexp)) {
            if (*regexp == src[cnt]) {
                regexp++;
                cnt++;
            }
            else
                return NULL;
        }
        if (*regexp == '.') {
            if (isalpha(src[cnt])) {
                regexp++;
                cnt++;
            }
            else
                return NULL;
        }
        if (*regexp == '\\') {
            regexp++;
            if (*regexp == 'a') {
                if (isalpha(src[cnt]) && islower(src[cnt])) {
                    regexp++;
                    cnt++;
                } else
                    return NULL;
            } else if(*regexp=='A') {
                if (isalpha(src[cnt]) && isupper(src[cnt])) {
                    regexp++;
                    cnt++;
                } else
                    return NULL;
            }
        }
        if (*regexp == '[') {
            regexp++;
            if (*regexp=='^'){
                regexp++;
                for(i=0;regexp[i]!=']';i++);
                dim=i;
                for(i=0;i<dim;i++,regexp++) {
                    if (src[cnt] == *regexp)
                        return NULL;
                }
                regexp++;
                cnt++;
            }
            else{
                for(i=0;regexp[i]!=']';i++);
                dim=i;
                for(i=0;i<dim && !flag;i++,regexp++) {
                    if (src[cnt] == *regexp){
                        regexp+=(dim-i);
                        cnt++;
                        flag=1;
                    }
                }
                if(!flag)
                    return NULL;
            }
        }
    }
    //if(cnt==strlen(src))
    return src;
    //return NULL;
    //Nel caso non si volessero tutte le occorrenze ma solo le parole
    // esattamente grandi come le espressioni regolari
}