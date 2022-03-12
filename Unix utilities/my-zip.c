#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Source: https://github.com/xxyzz/ostep-hw/blob/master/projects/initial-utilities/wzip/wzip.c

int main(int argc, char *argv[]){
    FILE *fptr = NULL;
    char buff, baff;
    int count = 0;

    if(argc <= 1){//error handling if not enough parameters are given
        fprintf(stderr,"wzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    for (int i = 1; i < argc; i++) //loop through command line parameters
	{
        if ((fptr = fopen(argv[i], "r")) == NULL) {//error handling
            fprintf(stderr,"wzip: cannot open file\n");
            exit(1);
        }
        
     while((buff = fgetc(fptr)) != EOF){ //looping through the file letter by letter	
         if(baff == buff){//testing if the same char appears in a row
         	count++; // count the amount of same char in a row
         }else{//if the letter changes to another letter
         	if(baff != '\0'){//and baff is not empty letter
                fwrite(&count,sizeof(count),1,stdout);//writing the count of numbers
                fwrite(&baff, sizeof(buff),1, stdout);//the ascii letter
                }
                baff = buff;//then initialize variable to the new char taken from file
                count = 1; // count is also initialized to be 1.
         }
     }
     fclose(fptr);
	}
	fwrite(&count,sizeof(count),1,stdout); //writing EOF to the file.
        fwrite(&baff, sizeof(buff),1, stdout);
 return 0;
}