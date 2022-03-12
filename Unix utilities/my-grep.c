#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fptr = NULL;
    char *row = NULL;
    size_t size;
    switch(argc){ // switchcase to determine amount of files 
        case(1)://case 1 no parameters, error occurs
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
        break;
        case(2)://case 2 only word is given
        fptr = stdin; //rows are coming from terminal
        while(getline(&row, &size, fptr) > -1){//get lines until ctrl + d
        if(strstr(row,argv[1])){//test if row and word equals
            printf("%s", row);//print the row
        }
        }
        break;
        default://default case, this means that the word + filenames are given
        for(int i = 2; i<argc; i++){//loop to go through the files
        if((fptr = fopen(argv[i], "r")) == NULL){//error handling
            fprintf(stderr,"wgrep: cannot open file\n");
            exit(0);
        }
        while(getline(&row, &size, fptr) > -1){//loop through the text file until eof
        if(strstr(row,argv[1])){//if the word and row equals
            printf("%s", row);//print the row
        }
        }}
        break;
    }
    free(row);//free memory
    fclose(fptr);//free memory
    return 0;}