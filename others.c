
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

char *fixString(char *ptr){
  char *string = ptr;
  string = strchr(string,'"');
  int j, n = strlen(string);
  for (int i = j = 0; i < n; i++){
    if (string[i] != '"'){
      string[j++] = string[i];
    }
  }
  if(string[j-1] == '\n'){
    string[j-1] = '\0';
  }else{
    string[j] = '\0';
  }
  return string;
}

char *fillString(char a, int x){
  char *result = malloc(sizeof(char)*x);
  for(int i = 0; i<x-1; i++){
    result[i]=a;
  }
  
  result[x-1]='\0';

  return result;

}

