#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <limits.h>

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

    if(strcmp(result.version, "x.x")== 0){
      result.version[0] = '\0';
    }  
    fclose(fpointer);
   
  #endif

      return result;
    
}

char *Xnotfound(){
  
  int i = 0;
  int j = 0;
  int w;
  int h;
  char read [1024];
  FILE *fp;
  Display *display = XOpenDisplay(NULL);
  if(display == NULL){
    if(system("xdpyinfo >>/dev/null 2>>/dev/null") == 0 ){
      fp = popen("xdpyinfo | awk /dimensions:/","r");
      fgets(read,1024,fp);
      while(read[i] < 48 || read[i]>57){
        i++;
      }
      while(read[i] != ' '){
        read[j] = read[i];
        j++;
        i++;
       }
      read[j] = '\0';
      char *result = malloc(sizeof(char)*strlen(read)+1);
      strcpy(result,read);
      pclose(fp);
      return result;
    }else if(system("xwininfo -root >>/dev/null 2>>/dev/null") == 0){

      fp = popen("xwininfo -root | grep geometry","r");
      fgets(read,1024,fp);
      while(read[i] < 48 || read[i]>57){
        i++;
      }
      while(read[i] != '+'){
        read[j] = read[i];
        j++;
        i++;
      }
      read[j] = '\0';
      char *result = malloc(sizeof(char)*strlen(read)+1);
      strcpy(result,read);
      pclose(fp);
      return result;
  }  

  }else{
    
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
}

char *getDisplay(){

  FILE *fp;
  char tmp[200];


  if(system("xrandr >>/dev/null 2>>/dev/null") != 0){
    char *result = Xnotfound();
    return result;
  }

  char *line = calloc(sizeof(char),200);
  char *linecpy;
  int i = 0;
  char *result = calloc(sizeof(char),200);
  fp = popen("xrandr | grep \'*\'","r");
  while(fgets(tmp,200,fp) != NULL){
    strcpy(line,tmp);
    linecpy = line +3;
    while(linecpy[i] != ' '){
      i++;
    }
    linecpy[i] = '\0'; 
    result = strcat(result,linecpy);
    result = strcat(result, " ");
    i = 0;
    }
  free(line);
  pclose(fp);
  return result;
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
    return "Unknow";
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
  FILE *fp = popen("lspci | grep VGA","r");
  if(fp == NULL){
    printf("Cannot read GPU\n");
    return "Unknown";
  }
  char read[1024];
  char *tmp;
  int i = 1;
  char *result;
  while(fgets(read,1024,fp) != NULL){
    if((tmp = strchr(read,'[')) == NULL){
      tmp = strrchr(read,':');
      tmp++;
      i = strlen(tmp)+1;
      result = malloc(sizeof(char)*i);
      strcpy(result,tmp);
      result[i-2] = '\0';
    }else{
  
      while(tmp[i] != ']'){
        i++;
      }
  
      result = malloc(sizeof(char)*i+1);
      strncpy(result,tmp,i);
      result[i] = '\0';
      result[0] = ' ';
      pclose(fp);
      return result;

    }
  }
  pclose(fp);
  return result;
}
