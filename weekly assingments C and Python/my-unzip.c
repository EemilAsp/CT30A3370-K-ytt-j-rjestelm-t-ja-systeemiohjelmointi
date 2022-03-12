#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    FILE *fptr;
    char buff;
    int count = 0;
    if(argc <= 1){
        fprintf(stderr,"wzip: file1 [file2 ...]\n");
        exit(1);
    }
    for(int i = 1; i < argc; i++){
        if((fptr = fopen(argv[i], "r")) == NULL){
            fprintf(stderr,"wunzip: cannot open file\n");
            exit(1);
        }
        while(fread(&count, sizeof(int), 1, fptr) == 1){
            fread(&buff, sizeof(buff), 1, fptr);
            for(int i = 0; i<count; i++){
            	fwrite(&buff, sizeof(buff), 1, stdout);
            }
        }
        fclose(fptr);
    }
    return 0;
}