#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "others.h"
#include <unistd.h>
#include <limits.h>
#include <sys/utsname.h>


#ifdef __linux__

char *getOS(){
  
    FILE *fpointer = fopen ("/etc/os-release","r");
    char read [50];
    char *line;
    char *token = calloc(sizeof(char),12);
    if ( fpointer != NULL ){
      while (strcmp(token,"PRETTY_NAME") != 0 && fgets(read, 50 , fpointer) != NULL){
        memcpy(token,read,11);
      }
      fclose(fpointer);
      free(token);
    }else{
      printf("cannot read OS");
      return NULL;
    }
    line = malloc(sizeof(char)*strlen(read)+1);
    strcpy(line,read);
    line = fixString(line);

    return line;
}

char *getBits(){

  FILE *fpointer = fopen ("/proc/cpuinfo","r");
  char *line = malloc(sizeof(char)*1000); /* or other suitable maximum line size */
  char *token = calloc(sizeof(char),6);
  if ( fpointer != NULL ){
    while (strcmp(token,"flags") != 0 && fgets(line, 256 , fpointer) != NULL){
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
  char *user = malloc(sizeof(char)*LOGIN_NAME_MAX);
  if(getlogin_r(user,LOGIN_NAME_MAX) != 0){
    printf("Cannot read username\n");
    return NULL;
  }
  return user;
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
