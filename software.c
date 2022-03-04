#define _GNU_SOURCE
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "others.h"
#include <unistd.h>
#include <limits.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <pwd.h>
#define MAX 1024



typedef struct{

  int npacks;
  char *manager;

}Pack;

char *getOS(){

  FILE *fpointer = fopen ("/etc/os-release","r");
  char read [50];
  char *result;

  if ( fpointer != NULL ){
    while (fgets(read, 50 , fpointer) != NULL && strstr(read,"PRETTY_NAME") == NULL);
  }else{
    printf("cannot read OS\n");
    return NULL;
  }

  fclose(fpointer);
  result = fixString(read,'"','"',1);
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

char *getPacks(){

  //TO DO: read more pkg managers like slackware and gentoo//

  FILE *fp;
  char packs[6];
  Pack *pkg = malloc(sizeof(Pack)*5);
  struct stat stats;
  int j = 0;
  int i = 0;
  char read[1024];

  if(stat("/var/lib/pacman/local",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){
    pkg[j].manager = "pacman";
    pkg[j].npacks = NumOfPackages("/var/lib/pacman/local") - 1;
    j++;
  }if(stat("/var/lib/snapd/snaps",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){
    pkg[j].manager = "snap";
    pkg[j].npacks = NumOfPackages("/snap") - 1;
    j++;
  }if(stat("/var/lib/dpkg",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){
    pkg[j].manager = "dpkg";
    fp = fopen("/var/lib/dpkg/status","r");
    if(fp != NULL){
      while(fgets(read,1024,fp) != NULL){
        if(strstr(read,"Status:") != NULL ){
          i++;
        }
      }
    }
    pkg[j].npacks = i;
    fclose(fp);
    j++;
  }if(stat("/var/lib/rpm",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){
    pkg[j].manager = "rpm";
    fp = popen("rpm -qa | wc -l","r");
    pkg[j].npacks = atoi(fgets(packs,6,fp));
    pclose(fp);
    j++;
  }if(stat("/var/lib/flatpak/app",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){
    pkg[j].manager = "flatpak";
    pkg[j].npacks = NumOfPackages("/var/lib/flatpak/app");
    j++;
  }if(pkg[0].npacks == 0){
    return NULL;
  }

  char *result = calloc(sizeof(char),1024);
  char np [6];
  for(int a = 0; a<j ; a++){
    if(a+1 == j){
      sprintf(np,"%d",pkg[a].npacks);
      result = strcat(result,np);
      result = strcat(result , " ");
      result = strcat(result,"(");
      result = strcat(result,pkg[a].manager);
      result = strcat(result,")");
    }else{
      sprintf(np,"%d",pkg[a].npacks);
      result = strcat(result,np);
      result = strcat(result , " ");
      result = strcat(result,"(");
      result = strcat(result,pkg[a].manager);
      result = strcat(result,"), ");
    }
  }

  free(pkg);
  return result;

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
  }

  return shell;
}

char *getDE(){
  char *result = getenv("XDG_SESSION_DESKTOP");
  if(result == NULL || strcmp(result,"") == 0){
    result = getenv("XDG_CURRENT_DESKTOP");
    if (result == NULL || strcmp(result,"") == 0){
      return NULL;
    }
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
  char *result;
  fp = popen ("ps -o comm= -p \"$(($(ps -o ppid= -p \"$(($(ps -o sid= -p \"$$\")))\")))\" 2>/dev/null", "r");
  if (fp != NULL){
    fgets(tmp,MAX,fp);
    if(tmp == NULL){
      printf("Cannot read Terminal\n");
      return NULL;
    }
    x = strlen(tmp);
    result = malloc(sizeof(char)*x+1);
    strcpy(result,tmp);
    if(result[x-2] == '-'){//weird gnome terminal bug
      result[x-2] = '\0';
    }else{//deleting \n //
      result[x-1] = '\0';
    }
    pclose(fp);
  }else{
    char *pointer = strtok(getenv("TERM"),"-");
    result = malloc(sizeof(char)*strlen(freethispointer)+1);
    strcpy(result,pointer);
  }
  return result;
}
