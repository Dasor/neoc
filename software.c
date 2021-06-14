#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include "others.h"
#include <unistd.h>
#include <limits.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#include <math.h>
#define MAX 1024

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
    tmp = fixString(line,'"','"',0);
    result = malloc(sizeof(char)*strlen(tmp)+1);
    strcpy(result,tmp);
    free(tmp);
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
  char packs[6];
  Pack *pkg = malloc(sizeof(Pack)*2);
  pkg[1].npacks = 0;
  struct stat stats;

  if(stat("/var/cache/pacman",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){
    pkg[0].manager = "pacman";
    fp = popen("pacman -Q | wc -l","r");
    pkg[0].npacks = atoi(fgets(packs,6,fp));
    pclose(fp);
    return pkg;
  }else if(stat("/var/lib/snapd/snaps",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){ 
    pkg[0].manager = "snap";
    pkg[1].manager = "apt";
    fp = popen("find /var/snap/ -maxdepth 1 | wc -l","r");
    pkg[0].npacks = atoi(fgets(packs,6,fp));
    pkg[0].npacks--;
    pclose(fp);

    fp = popen("apt-cache pkgnames | wc -l","r"); 
    pkg[1].npacks = atoi(fgets(packs,6,fp));
    pclose(fp);
    return pkg;
  }else if(stat("/var/lib/rpm",&stats) == 0 || S_ISDIR(stats.st_mode) == 1){
    pkg[0].manager = "rpm";
    fp = popen("rpm -qa | wc -l","r");
    pkg[0].npacks = atoi(fgets(packs,6,fp));
    pclose(fp);
    return pkg;
  }else{
    pkg[0].manager = "Unknown";
    pkg[0].npacks = 0;
    return pkg;
  }
  
}

char *getShell(){

  char *shell; 
  if((shell = strrchr(getenv("SHELL"),'/')) == NULL){
    printf("Cannot read shell\n");
    return NULL;
  }
  shell[0] = ' ';

  if(strcmp(shell," bash") == 0 || strcmp(shell," rbash") == 0){//get bash version
    FILE *fp;
    char tmp[35];
    char *version;
    fp = popen ("bash --version","r");
    fgets(tmp,35,fp);
    version = numUntilchar(tmp,'(');
    shell = strcat(shell, " ");
    shell = strcat(shell,version);
    pclose(fp);
    free(version);
    return shell;
  }

  return shell;
}

char *getDE(){
  char *result = getenv("XDG_CURRENT_DESKTOP");
  if (result == NULL){
    return NULL;
  }
  if(strchr(result,':') != NULL ){
   result = strchr(result,':');
   result++;
  }
  return result;
}

char *getTerm(){
  FILE *fp;
  char tmp[MAX];
  int x;
  fp = popen ("ps -o comm= -p \"$(($(ps -o ppid= -p \"$(($(ps -o sid= -p \"$$\")))\")))\"", "r");
  fgets(tmp,MAX,fp);
  if(tmp == NULL){
    printf("Cannot read Terminal\n");
    return "Unknown";
  }
  x = strlen(tmp);
  char *result = malloc(sizeof(char)*x+1);
  strcpy(result,tmp);
  if(result[x-2] == '-'){//weird gnome terminal bug
    result[x-2] = '\0';
  }else{//deleting \n //
    result[x-1] = '\0';
  }
  pclose(fp);
  return result;
}


