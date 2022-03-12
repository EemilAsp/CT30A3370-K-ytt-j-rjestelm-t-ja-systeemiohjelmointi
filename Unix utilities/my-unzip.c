#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    FILE *fptr;
    char buff;
    int count = 0;
    if(argc <= 1){//error handling, checking that theres enough commandline parameters
        fprintf(stderr,"wzip: file1 [file2 ...]\n");
        exit(1);
    }
    for(int i = 1; i < argc; i++){//loop through the files
        if((fptr = fopen(argv[i], "r")) == NULL){//errorhandling
            fprintf(stderr,"wunzip: cannot open file\n");
            exit(1);
        }
        while(fread(&count, sizeof(int), 1, fptr) == 1){//taking the count of chars
            fread(&buff, sizeof(buff), 1, fptr);//taking the first char to unzip
            for(int i = 0; i<count; i++){//writing the char until count i equals count and then continuing to next char
            	fwrite(&buff, sizeof(buff), 1, stdout);
            }
        }
        fclose(fptr);
    }
    return 0;
}