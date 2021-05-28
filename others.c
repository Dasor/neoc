
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
