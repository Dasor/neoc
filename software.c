#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "others.h"
#include <unistd.h>
#include <limits.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>


#ifdef __linux__


struct PackagesRep {

int npacks;
char *manager;

};

typedef struct PackagesRep Pack;


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
    free(line); // we free both line and tmp since tmp points ahead of line but on the same memory//
    return result;
}

char *getBits(){

  struct utsname *bits = malloc(sizeof(struct utsname));
  if(uname(bits) != 0){
    printf("Cannot read bits\n");
    return NULL;
  }
  char *result = malloc(sizeof(char)*strlen(bits->machine)+1);
  strcpy(result,bits->machine);
  free(bits);
  return result;   


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
  char *result = malloc(sizeof(char)*strlen(kernel->release)+1);
  strcpy(result,kernel->release);
  free(kernel);
  return result;
  
}

long getUptime(){

  const long minute = 60;
  const long hour = minute *60;
  const long day = hour *24;

  long result;
  struct sysinfo *si = malloc(sizeof(struct sysinfo));
  if(sysinfo(si) != 0){
    printf("cannot read uptime\n");
    return -1;
  }

  result = si->uptime;
  free(si);
  return result;

}

Pack *getPacks(){

//TO DO: read more pkg managers like slackware and gentoo//

 FILE *fp;
  char num [2];
  char packs[5];
  Pack *p = malloc(sizeof(Pack)*2);
  p[1].npacks = 0;
  
  fp = popen("command -v pacman | wc -l", "r"); //Arch
  fgets(num,2,fp);
  if(strcmp(num,"0") == 0){
    fp = popen ("command -v snap | wc -l","r");//debian//
    fgets(num,2,fp);
    if(strcmp(num,"0") == 0){
      fp = popen ("command -v rpm | wc -l ","r");//red hat//
      fgets(num,2,fp);
      fp = popen ("rpm -qa | wc -l","r");
      fgets(packs,5,fp);
      p[0].npacks = atoi(packs);
      p[0].manager = "rpm";
      return p;
      if(strcmp(num,"0") == 0){
        printf("cannot read pkgs\n");
        return NULL;
      }
    }
    fp = popen("find /var/snap/ -maxdepth 1 | wc -l","r");
    fgets(packs,5,fp);
    p[0].npacks = atoi(packs);
    p[0].npacks--;
    fp = popen ("dpkg --list | wc --lines","r");
    fgets(packs,5,fp);
    p[1].npacks = atoi(packs);
    p[0].manager = "snap";
    p[1].manager = "apt";
    return p;
  }

  fp = popen("pacman -Q | wc -l","r");
  fgets(packs,5,fp);
  p[0].npacks = atoi(packs);
  p[0].manager = "pacman";
  return p;
}
