#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define inf 99999999

typedef struct list { //List that is responsible of keeping track of data received from user input or textfile
    char row[inf];
    struct list *next;
}LIST;


LIST *reverse(LIST* pHead){ // this function will reverse the order of the linked list
    LIST *prev = NULL;
    LIST *curr = pHead;
    LIST *next;
    while(curr != NULL){ //reversing the linked list
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    pHead = prev; // new head pointer is the previous last pointer
    return pHead;
}

void printToFile(LIST *pHead, char *output){ //printing the resultants to file
    FILE *fptr = NULL;
    if((fptr = fopen(output, "w")) == NULL){ //Incase of error occurs
        fprintf(stderr, "error: cannot open file '%s'\n", output);
        exit(1);
    }
    while(pHead){//while linked list is not NULL
        LIST *ptr = pHead;
        fprintf(fptr, "%s", ptr->row);//printing the data from linked list into the file
        pHead = pHead->next;
        free(ptr);// Making sure that all the memory is freed after text is in file
    }
    fclose(fptr);
    return;
}

void printReverse(LIST *pHead){ //incase the user wants to print data to terminal
    while(pHead){//while linked list not null loopin through
    LIST *ptr = pHead;
    fprintf(stdout, "%s", pHead->row);//print to terminal
    pHead = pHead->next;//next
    free(ptr);// free memory
    }
}

LIST *fromInput(LIST *phead){ //Filling the linked list from user input
    char *row = NULL;
    size_t len = 0;
    FILE *in = stdin;
    while(getline(&row, &len, in) != -1){//reversing user input until user inserts ctrl + d
        LIST *pNew = malloc(sizeof(LIST));
        if(pNew == NULL){ // Error handling if malloc fails
            free(row);
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        strcpy(pNew->row, row); //copying the row received from user to the linked list
        pNew->next = phead;
        phead = pNew;
        }
    free(row);//free memory
    fclose(in);//close inputstream
    return phead;
}

LIST *addToLinkedList(LIST *phead, char *pRow){ //this function adds the elements from the textfile to the linked list
        LIST *pNew, *ptr;
        if ((pNew = (LIST*)malloc(sizeof(LIST))) == NULL){ //Error handling
        fprintf(stderr, "malloc failed.\n");
        exit(1);
    }
    strcpy(pNew->row, pRow);//copying the row to linked list
    pNew->next = NULL;
    if (phead == NULL){//if the first element is null, the node created will be head
        phead = pNew;
        } else {//otherwise looping through the list until we find the end of linked list
            ptr = phead;
            while(ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = pNew;
    }
    return phead;
}

void readFile(LIST *pHead, char *filename, int numb, char *output){//in this function we will determine if the user gave us 
    char *row;// input and outputfile or just inputfile (numb is a boolean 1 or 0)
    size_t len = 0;
    FILE *fptr = NULL;
    if((fptr = fopen(filename, "r")) == NULL){//error handling
        fprintf(stderr, "error: cannot open file '%s'\n", filename);
        exit(1);
    }
    while(getline(&row, &len, fptr) != -1){//while the textfile is not EOF
    		pHead = addToLinkedList(pHead, row);//adding the row to linked list
    		}
    fclose(fptr);//close file
    free(row);//free memory
    pHead = reverse(pHead);//reverse the linked list so that the output will be in reverse order
    if(numb == 1){//if boolean 1, no outputfile given, lets print to terminal
        printReverse(pHead);
        return;
    }else{//otherwise we will write the linked list elements into file
        printToFile(pHead, output);
    }
    
}


int main(int argc, char*argv[]){
    LIST *pHead = NULL;
    
    switch(argc){ //switch case to determine how many commandline variables the user has given
        case(1)://no variables
        pHead = fromInput(pHead);
        printReverse(pHead);
        break;
        case(2)://only input file
        readFile(pHead, argv[1], 1, argv[2]);
        break;
        case(3)://input and outputfile
        if(strcmp(argv[1],argv[2])){// if input and outputfile are the same
                fprintf(stdout, "Input and output file must differ.\n");
                exit(1);
                }
        readFile(pHead, argv[1], 2, argv[2]);
        break;
        default://otherwise too many variables
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    return 0;
}