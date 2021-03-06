#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"logos.h"
#include"hardware.h"
#include"software.h"
#include"main.h"

char *fixString(char *ptr,char c1, char c2,short ispointer){
  int n = strlen(ptr);
  int i = 0;
  char *string;
  if(ispointer == 1){//1 for pointer , 0 for array//
    string = malloc(sizeof(char)*n+1);
    strcpy(string,ptr);
  }else{
    string = ptr;
  }
  char *tmp = strchr(string,c1);
  tmp++;
  while(tmp[i] != c2){
    i++;
  }
  tmp[i] = '\0';
  char *result = malloc(sizeof(char)*strlen(tmp)+1);
  strcpy(result,tmp);
  free(string);
  return result;
}

char *fillString(char a, int x){
  char *result = malloc(sizeof(char)*x);
  for(int i = 0; i<x-1; i++){
    result[i]=a;
  }
  
  result[x-1]='\0';

  return result;

}

char *numUntilchar(char *read, char c1){

int i = 0 , j = 0;

 while(read[i] < 48 || read[i]>57){
        i++;
 }
  while(read[i] != c1){
    read[j] = read[i];
    j++;
    i++;
  }
  read[j] = '\0';
  char *result = malloc(sizeof(char)*strlen(read)+1);
  strcpy(result,read);
  return result;

}

int NumOfPackages(char *path){
  struct dirent *ep;
  int i = 0;
  DIR *dp = opendir(path);
  if( dp != NULL){
    while((ep = readdir(dp)) != NULL){
        i++;
      }
    closedir(dp);
    }
  i = i-2;
  return i;
}

