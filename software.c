#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "others.h"
#include <unistd.h>
#include <limits.h>

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
    }else{
      printf("cannot read OS");
      return NULL;
    }

    char *string = fixString(line);

  #endif
    return string;
}

char *getHost(){
  char *host;  
  char hostname[256];
  if(gethostname(hostname, 256) == -1){
    printf("Cannot read hostname");
    return NULL;
  }
  host = hostname;
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
