#include <stdio.h>
#include <stdlib.h>
#define size 9999


int main(int argc, char *argv[]){
    FILE *fptr = NULL;
    char buffer[size];
    if(argc<1){//if function is used with no commandline arguments
        exit(0);
    }
    for(int i = 1; i<argc; i++){//looping through the command line arguments starting from 1
        if((fptr = fopen(argv[i], "r")) == NULL){//if the command line argument is not a file or the file cannot
            fprintf(stderr, "my-cat: cannot open file\n");//be opened, error occurs
            exit(1);//exiting with 1
        }//if the file opens
        while(fgets(buffer, size, fptr)){//going through the file 
            printf("%s", buffer);//printing the elementent to the terminal as required
        }
    fclose(fptr);//after done with the file, close it and loop again if there is another file in line.
    }
    
    return 0;
}