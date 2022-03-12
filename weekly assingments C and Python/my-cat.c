#include <stdio.h>
#include <stdlib.h>

#define size 2000


int main(int argc, char *argv[]){
    FILE *fptr = NULL;
    char buffer[size];
    for(int i = 1; i<argc; i++){
        if((fptr = fopen(argv[i], "r")) == NULL){
            fprintf(stderr, "my-cat: cannot open file\n");
            exit(1);
        }
        while(fgets(buffer, size, fptr)){
            printf("%s", buffer);
        }
    fclose(fptr);
    }
    
    return 0;
}