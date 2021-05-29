
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <limits.h>

char *getBoard(){
 #ifdef __linux__
  
    int lineNumber = 0;
    FILE *fpointer = fopen ("/sys/devices/virtual/dmi/id/board_name","r");
    int count = 0;
    char *line = calloc(sizeof(char),256); /* or other suitable maximum line size */
    
    if ( fpointer != NULL ){
      while (fgets(line, 256 , fpointer) != NULL && count < lineNumber) /* read a line */{
        count++;
      }
      fclose(fpointer);
    }else{
      printf("cannot read Board");
      return NULL;
    }

  #endif
    return line;
}

