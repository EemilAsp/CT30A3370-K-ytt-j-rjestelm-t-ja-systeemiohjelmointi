#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    FILE *fptr = NULL;
    char *row = NULL;
    size_t size;
    switch(argc){
        case(1):
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
        break;
        case(2):
        fptr = stdin;
        while(getline(&row, &size, fptr) > 0){
        if(strstr(row,argv[1])){
            printf("%s", row);
        }
        }
        break;
        default:
        if((fptr = fopen(argv[2], "r")) == NULL){
            fprintf(stderr,"wgrep: cannot open file\n");
            exit(1);
        }
        while(getline(&row, &size, fptr) > 0){
        if(strstr(row,argv[1])){
            printf("%s", row);
        }
        }
        break;
    }
    free(row);
    fclose(fptr);
    return 0;}