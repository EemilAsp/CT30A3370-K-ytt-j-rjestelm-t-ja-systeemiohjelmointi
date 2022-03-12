#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define inf 99999999

typedef struct list {
    char row[inf];
    struct list *next;
}LIST;


LIST *reverse(LIST* pHead){
    LIST *prev = NULL;
    LIST *curr = pHead;
    LIST *next;
    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    pHead = prev;
    return pHead;
}

void printToFile(LIST *pHead, char *output){
    FILE *fptr = NULL;
    LIST *ptr = pHead;
    if((fptr = fopen(output, "w")) == NULL){
        printf("error: cannot open file '%s'", output);
        exit(1);
    }
    while(ptr){
        fprintf(fptr, "%s", ptr->row);
        ptr = ptr->next;
    }
    fclose(fptr);
    return;
}

void printReverse(LIST *pHead){
    while(pHead){
    printf("%s", pHead->row);
    pHead = pHead->next;
    }
}

LIST *fromInput(LIST *phead){
    char *row = NULL;
    size_t len = 0;
    while(getline(&row, &len, stdin) >= 0){
        if(strcmp(row, "quit") == 0){
            free(row);
            return phead;
        }
        LIST *pNew = malloc(sizeof(LIST));
        if(pNew == NULL){
            free(row);
            fprintf(stdin, "malloc failed.\n");
        }
        strcpy(pNew->row,row);
        free(row);
        pNew->next = phead;
        phead = pNew;
    }
    return phead;
}

LIST *addToLinkedList(LIST *phead, char *pRow){
        LIST *pNew, *ptr;
        if ((pNew = (LIST*)malloc(sizeof(LIST))) == NULL){
        perror("Malloc failed.\n");
        exit(1);
    }
    strcpy(pNew->row, pRow);
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

void readFile(LIST *pHead, char *filename, int numb, char *output){
    char rivi[inf];
    FILE *fptr = NULL;
    if((fptr = fopen(filename, "r")) == NULL){
        fprintf(stderr, "error: cannot open file '%s'", filename);
        exit(1);
    }
    int i = 0;
    while(fgets(rivi, sizeof(rivi), fptr) != NULL){
            i++;
    		pHead = addToLinkedList(pHead, rivi);
    		}
    fclose(fptr);
    pHead = reverse(pHead);
    if(numb == 1){
        printReverse(pHead);
        return;
    }else{
        printToFile(pHead, output);
    }
    
}


int main(int argc, char*argv[]){
    LIST *pHead = NULL;
    switch(argc){
        case(1):
        pHead = fromInput(pHead);
        break;
        case(2):
        readFile(pHead, argv[1], 1, argv[2]);
        break;
        case(3):
        readFile(pHead, argv[1], 2, argv[2]);
        break;
        default:
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    return 0;
}