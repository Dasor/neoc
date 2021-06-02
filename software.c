#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "others.h"
#include <unistd.h>
#include <limits.h>
#include <sys/utsname.h>
#include <pwd.h>


#ifdef __linux__

char *getOS(){
  
    FILE *fpointer = fopen ("/etc/os-release","r");
    char read [50];
    char *line;
    char *result;
    char *tmp;
    char *token = calloc(sizeof(char),12);
    if ( fpointer != NULL ){
      while (strcmp(token,"PRETTY_NAME") != 0 && fgets(read, 50 , fpointer) != NULL){
        memcpy(token,read,11);
      }
      fclose(fpointer);
      free(token);
    }else{
      printf("cannot read OS\n");
      return NULL;
    }
    line = malloc(sizeof(char)*strlen(read)+1);
    strcpy(line,read);
    tmp = fixString(line);
    result= malloc(sizeof(char)*strlen(tmp)+1);
    strcpy(result,tmp);
    free(line);
    return result;
}

char *getBits(){

  FILE *fpointer = fopen ("/proc/cpuinfo","r");
  char line [1000];
  char *token = calloc(sizeof(char),6);
  if ( fpointer != NULL ){
    while (strcmp(token,"flags") != 0 && fgets(line, 1000 , fpointer) != NULL){
        memcpy(token,line,5);
      }      

    free(token);
    if(strstr(line," lm ") != NULL){
      fclose(fpointer);
      return "x86_64";  
    }else{
      fclose(fpointer);
      return "x86";
    } 

  }
  
  printf("Cannot read bits\n");
  fclose(fpointer);
  return NULL;

}
char *getHost(){
  char *host = calloc(sizeof(char),HOST_NAME_MAX);  
  if(gethostname(host, HOST_NAME_MAX) != 0){
    printf("Cannot read hostname\n");
    return NULL;
  }
  return host;


}

char *getUser(){
  struct passwd *pws;
  if(( pws = getpwuid(geteuid())) == NULL){
    printf("cannot read user\n");
    return NULL;
    }

    
    return pws->pw_name;
  
}
  #endif

char *getKernel(){
  struct utsname *kernel = malloc(sizeof(struct utsname));
  if(uname(kernel) != 0){
    printf("Cannot read kernel");
    return NULL;
  }
  char *result = malloc(sizeof(char)*256);
  strcpy(result,kernel->release);
  free(kernel);
  return result;
  
}
