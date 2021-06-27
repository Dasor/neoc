#define RESET "\e[0m"
#define C1 "\e[30m"
#define C2 "\e[31m"
#define C3 "\e[32m"
#define C4 "\e[33m"
#define C5 "\e[34m"
#define C6 "\e[35m"
#define C7 "\e[36m"
#define C8 "\e[37m"
#define C9 "\e[1;37m"
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

struct LogoRep {

  int height;
  char *logo;
  char *color;

};

typedef struct LogoRep Logo;

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

char *getPacks(){

//TO DO: read more pkg managers like slackware and gentoo//

  FILE *fp;
  char packs[6];
  Pack *pkg = malloc(sizeof(Pack)*4);
  struct stat stats;
  int j = 0;
  int i = 0;
  char read[1024];

  if(stat("/var/cache/pacman",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){
    pkg[j].manager = "pacman";
    pkg[j].npacks = NumOfPackages("/var/lib/pacman/local") - 1;
    j++;
  }if(stat("/var/lib/snapd/snaps",&stats) == 0 && S_ISDIR(stats.st_mode) == 1){ 
    pkg[j].manager = "snap";
    pkg[j].npacks = NumOfPackages("/snap") - 2;
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

Logo *getLogo(char *string){

  Logo *mylogo = malloc(sizeof(Logo));  

  if(strstr(string,"Arch") != NULL){
    mylogo->logo = 
      C7"                      -`                     \0"\
      C7"                     .o+`                    \0"\
      C7"                    `ooo/                    \0"\
      C7"                   `+oooo:                   \0"\
      C7"                  `+oooooo:                  \0"\
      C7"                  -+oooooo+:                 \0"\
      C7"                `/:-:++oooo+:                \0"\
      C7"               `/++++/+++++++:               \0"\
      C7"              `/++++++++++++++:              \0"\
      C7"             `/+++ooooooooooooo/`            \0"\
      C7"            ./ooosssso++osssssso+`           \0"\
      C7"           .oossssso-````/ossssss+`          \0"\
      C7"          -osssssso.      :ssssssso.         \0"\
      C7"         :osssssss/        osssso+++.        \0"\
      C7"        /ossssssss/        +ssssooo/-        \0"\
      C7"      `/ossssso+/:-        -:/+osssso+-      \0"\
      C7"     `+sso+:-`                 `.-/+oso:     \0"\
      C7"    `++:.                           `-/+/    \0"\
      C7"    .`                                 `/    \0"\
      ;
    mylogo->color = C7;
    mylogo->height = 19;
  }else if(strstr(string,"Debian") != NULL){
    mylogo->logo =
   C9"                                 \0"\
   C9"        _,met$$$$$gg.            \0"\
   C9"     ,g$$$$$$$$$$$$$$$P.         \0"\
   C9"   ,g$$P\"     \"\"\"Y$$.\".          \0"\
   C9"  ,$$P'              `$$$.       \0"\
   C9" ',$$P       ,ggs.     `$$b:     \0"\
   C9" `d$$'     ,$P\"' "C2"  ."C9"    $$$      \0"\
   C9"  $$P      d$'    "C2" , "C9"   $$P      \0"\
   C9"  $$:      $$.  "C2" - "C9"   ,d$$'      \0"\
   C9"  $$;      Y$b._   _,d$P'        \0"\
   C9"  Y$$.    "C2"`."C9"`\"Y$$$$P\"'           \0"\
   C9"  `$$b     "C2" \"-.__ "C9"               \0"\
   C9"   `Y$$                          \0"\
   C9"    `Y$$.                        \0"\
   C9"      `$$b.  		                \0"\
   C9"         `Y$$b.                   \0"\
   C9"           `\"Y$b._               \0"\
   C9"               `\"\"\"              \0"\
   ;
    mylogo->color = C2;
    mylogo->height = 18;
  }else{
    mylogo->logo =
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      "                                                        \0"\
      ;
      mylogo->color = C9;
      mylogo->height = 19;
  }
  return mylogo;
}
