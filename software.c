#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "others.h"


char *getOS(){
 #ifdef __linux__
  
    int lineNumber = 1;
    FILE *fpointer = fopen ("/etc/os-release","r");
    int count = 0;
    char *line = malloc(sizeof(char)*256); /* or other suitable maximum line size */
    
    if ( fpointer != NULL ){
      while (fgets(line, 256 , fpointer) != NULL && count < lineNumber) /* read a line */{
        count++;
      }
      fclose(fpointer);
    }

    char *string = fixString(line);

  #endif
    return string;
}
