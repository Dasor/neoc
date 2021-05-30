#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "others.h"
#include <unistd.h>
#include <limits.h>

char *getOS(){
 #ifdef __linux__
  
    FILE *fpointer = fopen ("/etc/os-release","r");
    char *line = malloc(sizeof(char)*256); /* or other suitable maximum line size */
    char *token = calloc(sizeof(char),11);
    if ( fpointer != NULL ){
      while (strcmp(token,"PRETTY_NAME") != 0 && fgets(line, 256 , fpointer) != NULL){
        memcpy(token,line,11);
      }
      fclose(fpointer);
      free(token);
    }else{
      printf("cannot read OS");
      return NULL;
    }

    char *string = fixString(line);

  #endif
    return string;
}

char *getHost(){
  char *host = calloc(sizeof(char),HOST_NAME_MAX);  
  if(gethostname(host, HOST_NAME_MAX) == -1){
    printf("Cannot read hostname");
    return NULL;
  }
  return host;


}

char *getUser(){
  char *user = malloc(sizeof(char)*LOGIN_NAME_MAX);
  if(getlogin_r(user,LOGIN_NAME_MAX) == -1){
    printf("Cannot read username");
    return NULL;
  }
  return user;
}
