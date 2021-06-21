#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "others.h"

struct BoardRep{
  
  char *chip;
  char *version;

};

typedef struct BoardRep Board;



Board getBoard(){
 #ifdef __linux__
  
    FILE *fpointer = fopen ("/sys/devices/virtual/dmi/id/board_name","r");
    Board result;
    result.chip = calloc(sizeof(char),256); /* or other suitable maximum line size */

    if ( fpointer != NULL ){
      fgets(result.chip, 256 , fpointer);
    }else{
      printf("cannot read Board");
      result.chip = NULL; 
      result.version = NULL;
      return result;
    }


    result.chip[strlen(result.chip)-1] = '\0'; //deletes \n //

    fclose(fpointer);

    fpointer = fopen ("/sys/devices/virtual/dmi/id/board_version","r");
    result.version = calloc(sizeof(char),4); //I suppose there can´t be a bigger version that x.x// 
    
    if (fpointer != NULL ){
      fgets(result.version, 4 , fpointer);
    }else{
      result.chip = NULL; 
      result.version = NULL;
      printf("cannot read Board");
      return result;
    }

    if(strcmp(result.version, "x.x") == 0 || strcmp(result.version,"\n") == 0){
      result.version[0] = '\0';
    }  
    fclose(fpointer);
   
  #endif

      return result;
    
}

char *getDisplay(){

  int w;
  int h;
  Display *display = XOpenDisplay(NULL);
  if(display == NULL){
    return NULL;
  }

    Screen *screen = DefaultScreenOfDisplay(display);

    w = WidthOfScreen(screen);
    h = HeightOfScreen(screen);
    
    char width [17];
    char height [17];
    sprintf(width,"%d",w);
    sprintf(height,"%d",h);

    char *result = strcat(width, "x");
    result = strcat(result,height);
    XCloseDisplay(display);

    char *resultcpy = malloc(sizeof(char)*strlen(result)+1);
    strcpy(resultcpy,result);
    return resultcpy;
}   




char *getCpu(){

  FILE *fp = fopen("/proc/cpuinfo","r");
  char *token = calloc(sizeof(char),11);
  char read [1024];
  if(fp != NULL){
    while(strcmp(token,"model name") != 0 && fgets(read,1024,fp) != NULL){
      memcpy(token,read,10);
  }
    fclose(fp);
    free(token);
  }else{
    printf("Cannot read Cpu\n");
    return "NULL";
  }

  char *tmp = malloc(sizeof(char)*strlen(read)+1);
  strcpy(tmp,read);
  char *result = strchr(tmp,':');
  char *resultcpy = malloc(sizeof(char)*strlen(result)+1);
  strcpy(resultcpy,result);
  free(tmp);
  return resultcpy;

}

char *getGpu(){
  if(system("lspci >>/dev/null 2>>/dev/null") != -1){
  FILE *fp = popen("lspci | grep VGA","r");
  char read[1024];
  char *tmp;
  int i = 1;
  char *result;
  while(fgets(read,1024,fp) != NULL){
    if((tmp = strchr(read,'[')) == NULL){
      tmp = strrchr(read,':');
      tmp = tmp + 2;
      i = strlen(tmp)+1;
      result = malloc(sizeof(char)*i);
      strcpy(result,tmp);
      result[i-2] = '\0';
    }else{
  
    result = fixString(tmp,'[',']',1);
    pclose(fp);
    return result;

    }
  }
  pclose(fp);
  return result;
  }else{
    return NULL;
  }
}

char *getMemory(){
    int total_memory, used_memory;
    int total, shared, memfree, buffers, cached, reclaimable;

    FILE *meminfo = fopen("/proc/meminfo", "r"); /* get infomation from meminfo */
    if(meminfo == NULL) {
      return NULL;
    }

    /* We parse through all lines of meminfo and scan for the information we need */
    char *line = NULL; // allocation handled automatically by getline()
    size_t len; /* unused */

    /* parse until EOF */
    while (getline(&line, &len, meminfo) != -1) {
        /* if sscanf doesn't find a match, pointer is untouched */
        sscanf(line, "MemTotal: %d", &total);
        sscanf(line, "Shmem: %d", &shared);
        sscanf(line, "MemFree: %d", &memfree);
        sscanf(line, "Buffers: %d", &buffers);
        sscanf(line, "Cached: %d", &cached);
        sscanf(line, "SReclaimable: %d", &reclaimable);
    }

    free(line);

    fclose(meminfo);

    /* use same calculation as neofetch */
    used_memory = (total + shared - memfree - buffers - cached - reclaimable) / 1024;
    total_memory = total / 1024;
    int percentage = (int) (100 * (used_memory / (double) total_memory));

    char *memory = malloc(150);
    snprintf(memory, 150, "%dMiB / %dMiB (%d%%)", used_memory, total_memory, percentage);

    return memory;

}


