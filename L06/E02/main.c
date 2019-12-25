#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{leggi_t,leggi_f,ricerca,cancella,cancella2,stampa,fine,err}Comandi;
typedef struct{
    char *cod;
    char *nome;
    char *cognome;
    char *data;
    char *via;
    char *citta;
    int cap;
}Item;
typedef struct List{
    Item *val;
    struct List *next;
}Liste, *link;
link NewNode(link next,Item *val);
link Inserimento(link h,Item *val);
Item* Valori(FILE *fp);
Item* Ricerca(link h, char codice[]);
Item* Elimina(link *hp,char codice[]);
Item* Elimina2(link *hp, char d1[], char d2[]);
void StampaItem(Item* pi);
void StampaLista(link h);
int DataConv(char data[]);
Comandi leggiComandi(void);
int main() {
    link head=NULL;
    Comandi codice;
    FILE *fp=NULL;
    Item* trovato=NULL;
    char stringa[30],data1[15],data2[15];
    int continua=1;
    while(continua){
        codice=leggiComandi();
        switch(codice){
            case 0:
                printf("Inserire i dati anagrafici:\n(nome,cognome,data,via,città,cap)\n");
                head=Inserimento(head,Valori(stdin));
                break;
            case 1:
                printf("Inserire il nome del file su cui leggere\n");
                scanf("%s",stringa);
                fp=fopen(stringa,"r");
                if(fp==NULL)
                    return -1;
                while(!feof(fp)){
                    trovato=Valori(fp);
                    head=Inserimento(head,trovato);
                }
                fclose(fp);
                break;
            case 2:
                printf("Inserire il codice della persona da cercare\n");
                scanf("%s",stringa);
                trovato=Ricerca(head,stringa);
                if(trovato!=NULL)
                    StampaItem(trovato);
                else
                    fprintf(stderr,"L'elemento non è presente in lista\n");
                break;
            case 3:
                printf("Inserire il codice della persona da eliminare\n");
                scanf("%s",stringa);
                if(Ricerca(head,stringa)!=NULL){
                    trovato=Elimina(&head,stringa);
                    StampaItem(trovato);
                } else
                    fprintf(stderr,"L'elemento non è presente in lista\n");
                break;
            case 4:
                printf("Inserire le date tra le quali eliminare persone\n");
                scanf("%s%*c%s",data1,data2);
                do{
                trovato=Elimina2(&head,data1,data2);
                if(trovato!=NULL)
                    StampaItem(trovato);
                }while (trovato!=NULL);
                break;
            case 5:
                printf("LISTA:\n");
                StampaLista(head);
                break;
            case 6:
                continua=0;
                break;
            default:
                fprintf(stderr, "Comando errato\n");
        }
    }
    return 0;
}
Comandi leggiComandi(void){
    char comand[20],*T[err]={"leggi_t","leggi_f","ricerca","cancella","cancella2","stampa","fine"};
    Comandi comand_e=leggi_t;
    printf("Inserire comando(leggi_t,leggi_f,ricerca,cancella,cancella2,stampa,fine)\n");
    scanf("%s",comand);
    while((comand_e<err) && (strcmp(comand,T[comand_e])!=0)){
        comand_e++;
    }
    return comand_e;
}

link Inserimento(link h,Item* val){
    link x,p;
    if(h==NULL || DataConv(h->val->data)<DataConv(val->data))
        return NewNode(h,val);
    for(x=h->next,p=h;x!=NULL && DataConv(x->val->data)>DataConv(val->data);p=x,x=x->next);
    p->next=NewNode(x,val);
    return h;
}

link NewNode(link next,Item *val){
    link x;
    x=(link)malloc(sizeof(*x));
    if(x==NULL)
        fprintf(stderr,"Errore malloc");
    x->next=next;
    x->val=val;
    return x;
}
Item* Ricerca(link h, char codice[]){
    link x;
    for(x=h;x!=NULL;x=x->next){
        if(strcmp((x->val->cod),codice)==0){
            return x->val;
        }
    }
    return NULL;
}
Item* Elimina(link *hp,char codice[]){
    link *xp,t;
    Item *val=NULL;
    for(xp=hp;(*xp)!=NULL;xp=&((*xp)->next)){
        if(strcmp((*xp)->val->cod,codice)==0){
            val=(*xp)->val;
            t=(*xp);
            (*xp)=(*xp)->next;
            free(t);
            break;
        }
    }
    return val;
}
Item* Valori(FILE *fp){
    Item *val;
    val=(Item*)malloc(sizeof(Item));
    char tmp[30];
    fscanf(fp,"%s",tmp);
    val->cod=strdup(tmp);
    fscanf(fp,"%s",tmp);
    val->nome=strdup(tmp);
    fscanf(fp,"%s",tmp);
    val->cognome=strdup(tmp);
    fscanf(fp,"%s",tmp);
    val->data=strdup(tmp);
    fscanf(fp,"%s",tmp);
    val->via=strdup(tmp);
    fscanf(fp,"%s",tmp);
    val->citta=strdup(tmp);
    fscanf(fp,"%d",&(val->cap));
    return val;
}
Item* Elimina2(link *hp, char d1[], char d2[]){
    link *xp,t;
    Item *val=NULL;
    int tmp,data1=DataConv(d1),data2=DataConv(d2);
    if(data2>data1){
        tmp=data1;
        data1=data2;
        data2=tmp;
    }
    for(xp=hp;(*xp)!=NULL;xp=&((*xp)->next)){
        if((DataConv((*xp)->val->data))<data1 && (DataConv((*xp)->val->data))>data2){
            val=(*xp)->val;
            t=(*xp);
            (*xp)=(*xp)->next;
            free(t);
            break;
        }
    }
    return val;
}
void StampaItem(Item* pi){
    if(pi==NULL)
        fprintf(stderr,"Null\n");
    else
        fprintf(stdout,"%s %s %s %s %s %s %d\n",pi->cod,pi->nome,pi->cognome,pi->data,pi->via,pi->citta,pi->cap);
}
void StampaLista(link h){
    link x;
    if(h==NULL)
        fprintf(stderr,"Lista vuota\n");
    for(x=h;x!=NULL;x=x->next){
        fprintf(stdout,"%s %s %s %s %s %s %d\n",x->val->cod,x->val->nome,x->val->cognome,x->val->data,x->val->via,x->val->citta,x->val->cap);
    }
}
int DataConv(char data[]){
    int aa=0,mm=0,m=31,gg=0,tot=0;
    sscanf(data,"%d/%d/%d",&gg,&mm,&aa);
    aa-=1900;
    if(mm==11 || mm==4 || mm==6 || mm==9)
        m=30;
    if(mm==2)
        m=28;
    tot=gg+(mm*m)+(365*aa);
    return tot;
}