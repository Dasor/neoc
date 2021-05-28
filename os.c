#include<string.h>
#include<stdio.h>
#include<stdlib.h>

char *fixString(char *string){
  char *fstring = strchr(string,'"');
  int j, n = strlen(fstring);
  for (int i = j = 0; i < n; i++){
    if (fstring[i] != '"'){
      fstring[j++] = fstring[i];
    }
  }
  if(fstring[j-1] == '\n'){
    fstring[j-1] = '\0';
  }else{
    fstring[j] = '\0';
  }
  return fstring;
}


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
