/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: 
 * Tekijä: Eemil Aspholm
 * Opiskelijanumero: 0567753
 * Päivämäärä: 26.2.2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: www.programiz.com/c-programming,  
 */
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>
#define LEN 200
#define size 61 // koko 61, koska otsikkotiedot tulisi mahtua myös taulukkoon.
#define len 10
typedef struct list
{
    struct tm *date; // pvm ja kello 1.sarake 
    char ename[len]; // tehtävän nimi 2.sarake
    int userid; //käyttäjän tunnistenumero 4.sarake
    int eid; //tehtävän tunnistenumero 3.sarake
    struct list *next;
}LIST;

typedef struct tiedot
{
    char name[len];
    int value;
}TIEDOT;

typedef struct pvtiedot
{
    struct tm pvm;
    int amount;
}PVTIEDOT;

//Listan alkioiden alustus joko "Tyhjäksi" tai 0.
void alustaLista(TIEDOT *ptr){
    for (int i = 1; i<size; i++){
        strcpy(ptr[i].name, "Tyhjä");
        ptr[i].value = 0;
    }
    return;
}

//Taulukon muistinvapautus, mikäli taulukko ei ole NULL
//Vapautetaan myös struct_tm nodelle varattu muisti
LIST *vapautaMuistiTaulukko(LIST *phead){
    LIST *ptr = phead;
    while(ptr != NULL) {
        phead = ptr->next;
        free(ptr->date);
        free(ptr);
        ptr = phead;
    }
    return phead;
}

//Tiedoston nimen kysyvä aliohjelma
char *kysyTiedosto(){
    char tiedosto[20];
    printf("Anna tiedoston nimi: ");
    scanf("%s", tiedosto);
    char *ptr = tiedosto;
    return ptr;
}

void tulostaTulokset(TIEDOT *ptr){
    // muuttujien alustus
    FILE *fp;
    char *tdst;
    char choice;
    char header[] = "Tehtävä;Lkm";
    printf("Tulosta tiedostoon (k/e): ");
    scanf(" %c", &choice);
    if(choice == 'k'){
        tdst = kysyTiedosto();
        if((fp = fopen(tdst, "w")) == NULL){
            perror("Tiedostoon kirjoittaminen epäonnistui.\n");
            exit(0);
        }
        fprintf(fp, "%s\n", header);
        for(int i = 1; i<size; i++){
            fprintf(fp, "%s;%d\n", ptr[i].name, ptr[i].value);
        }
        fclose(fp);
    }
    else if(choice == 'e'){
        printf("%s\n", header);
        for(int i = 1; i<size; i++){
            printf("%s;%d\n", ptr[i].name, ptr[i].value);
        }
    }
    else{
        printf("Et antanut kirjainta 'k' tai 'e'.\n");
        exit(0);
    }
    return;
}

void analysoiTiedot(LIST *phead, TIEDOT *Lista){
    //muuttujien
    LIST *ptr;
    double plkm = 0, thtlkm = 0, kskm = 0;
    int i = 0;
    //tehtävänimet listaan
    for(int luku = 1; luku < size; luku++){
        ptr = phead;
        i++;
    while(ptr != NULL){
        if(ptr->eid == i){ //Lisätään alkioon aina +1, mikäli id ja listan alkion järjestysluku täsmää
            Lista[i].value += 1;
            plkm += 1;
            if ((strcmp(Lista[i].name, ptr->ename) != 0)){ //Testaus onko alkion nimen tilalle vaihdettu oikeanimi
                strcpy(Lista[i].name, ptr->ename);//Tehtävänimi paikalleen
                thtlkm += 1;
            }
            ptr = ptr->next;
        }
        else{
            ptr = ptr->next;
        }
    }}
    kskm = plkm / thtlkm;
    printf("Palautuksia oli yhteensä %.0lf, %.0lf eri tehtävässä, keskimäärin %.0lf per tehtävä.\n\n", plkm, thtlkm, kskm);
    return;
}

LIST *lisaaTaulukkoon(LIST *phead, char *pRow){
    //varataan muisti dynaamisesti aliohjelmassa selkeyttää rakennetta.
    LIST *pNew, *ptr;
    int year, month, day, hour, minute;
    char *p1, *p2, *p3, *p4;
    if ((pNew = (LIST*)malloc(sizeof(LIST))) == NULL){
        perror("Muistin varaus epäonnistui.\n");
        exit(0);
    }
    if ((pNew->date = (struct tm*)malloc(sizeof(struct tm))) == NULL){
        perror("Muistin varaus epäonnistui.\n");
        exit(0);
    } //vapauta myös tämä muisti 

    //tietojen irroitus 8/09/20, 10:46;L01T1;1;6607164 tätä muotoa 
    p1 = strtok(pRow, ";"); // aikatiedot 1.sarake
    p2 = strtok(NULL, ";"); // tehtävänimi 2.sarake
    p3 = strtok(NULL, ";"); // tehtäväid 3.sarake
    p4 = strtok(NULL, ";"); // palauttajanid 4.sarake
    sscanf(p1, "%d/%d/%d, %d:%d", &day, &month, &year, &hour, &minute); // time_t:tä varten string integeriksi
    pNew->date->tm_mday = day;
    pNew->date->tm_mon = month-1;
    pNew->date->tm_year = year+100;
    pNew->date->tm_hour = hour;
    pNew->date->tm_min = minute;
    strcpy(pNew->ename, p2);
    pNew->eid = atoi(p3);
    pNew->userid = atoi(p4);
    pNew->next = NULL;
    if (phead == NULL){
        phead = pNew;
        } else {
            ptr = phead;
            while(ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = pNew;
    }
    return phead;
}

LIST *lueTiedosto(LIST *phead){
    //Alustetaan muuttujat
    int lkm = 0;
    char buf[20], baf[20];
    LIST *ptr;
    FILE *fptr;
    char rivi[LEN];
    char *tdst = kysyTiedosto();
    if ((fptr = fopen(tdst, "r")) == NULL){
        printf("Tiedoston avaus epäonnistui.\n");
        exit(0);
    }
    fgets(rivi, sizeof(rivi), fptr); //luetaan otsikkorivi pois
    while(fgets(rivi, sizeof(rivi), fptr) != NULL) {
        lkm++;
        phead = lisaaTaulukkoon(phead, rivi);
    } 
    fclose(fptr);
    ptr = phead;
    while(ptr->next != NULL) //mennään taulukon viimeiseen solmuun jotta saadaan aikaväli
        {
         ptr = ptr->next;
         }
    strftime(buf, sizeof(buf), "%d.%m.%Y", phead->date);
    strftime(baf, sizeof(baf), "%d.%m.%Y", ptr->date);
    printf("Yhteensä %d palautusta %s - %s väliseltä ajalta.\n\n", lkm, buf, baf);
    return phead;
}

int pvPalautus(LIST *phead, struct tm time){
    LIST *ptr = phead;
    int sum = 0;
    while(ptr){
        if(time.tm_mday == ptr->date->tm_mday && time.tm_mon == ptr->date->tm_mon){
            sum++;
        }
        ptr = ptr->next;
    }
    return sum;
}


PVTIEDOT pvanalyysi(PVTIEDOT *phtr, LIST *phead){
    struct tm alku, loppu;
    time_t ekaEpoch, tokaEpoch, pvEpoch;
    int pvlkm, sum;
    PVTIEDOT *dptr = phtr;
    memset(&alku, 0, sizeof(alku));
    memset(&alku, 0, sizeof(alku));
    printf("Anna alku pvm (pp.mm.vvvv): ");
    scanf("%d.%d.%d", &alku.tm_mday, &alku.tm_mon-1, &alku.tm_year-1900);
    printf("Anna loppu pvm (pp.mm.vvvv): ");
    scanf("%d.%d.%d", &loppu.tm_mday, &loppu.tm_mon-1, &loppu.tm_year-1900);
    // lasketaan päivien määrä annetulla aikavälillä
    pvEpoch = mktime(&alku);
    ekaEpoch = mktime(&alku) / (60*60*24);
    tokaEpoch = mktime(&loppu) / (60*60*24);
    pvlkm = (tokaEpoch - ekaEpoch);
    while(1){
        pvEpoch += 24*60*60; // lisätään aina yksi päivä lisää.
        memcpy(dptr->pvm, localtime(&pvEpoch), sizeof(struct tm));
        dptr->amount = pvPalautus(phead, dptr->pvm);
        sum += dptr->amount;
        if(dptr->pvm.tm_mday == loppu.tm_mday && dptr->pvm.tm_mon == loppu.tm_mon){
            break;
        }
    }
    //printf("Yhteensä %d palautusta %s - %s väliseltä ajalta.\n\n", lkm, alku, loppu);
    return phtr;
}

int main(){
    //muuttujien alustus
    LIST *pHead = NULL;
    TIEDOT Lista[size];
    PVTIEDOT *pvm = NULL;
    alustaLista(Lista);
    int valinta;
    do
    {
        printf("1) Lue tiedosto\n");
        printf("2) Analysoi tiedot\n");
        printf("3) Tulosta tulokset\n");
        printf("4) Suorita päiväanalyysi\n");
        printf("5) Tulosta päiväanalyysin tulokset\n");
        printf("6) Tyhjennä tuloslista\n");
        printf("0) Lopeta\n");
        printf("Valintasi: ");
        scanf("%d", &valinta);
        switch(valinta){
            case 1:
            if (pHead == NULL){
            pHead = lueTiedosto(pHead);
            }
            else{
                pHead = vapautaMuistiTaulukko(pHead);
                pHead = lueTiedosto(pHead);
            }
            break;
            case 2:
            if (pHead == NULL){
                printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
                }
            else{
                alustaLista(Lista);
                analysoiTiedot(pHead, Lista);
            }
            break;
            case 3:
            if(strcmp(Lista->name, "Tyhjä")==0){
                printf("Ei tulostettavaa, analysoi ensin palautustiedosto.\n");
            }
            else{
                tulostaTulokset(Lista);
                }
            break;
            case 4:
            pvm = pvanalyysi(pvm, pHead);

            break;
            case 5:
            break;
            case 6:
            break;
            case 0:
            printf("Kiitos ohjelman käytöstä.\n");
            pHead = vapautaMuistiTaulukko(pHead);
            break;
            default:
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    } while (valinta != 0);
    return 0;
}
/*******************************************************************/
/* eof */