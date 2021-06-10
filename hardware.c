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
    char *chip = calloc(sizeof(char),256); /* or other suitable maximum line size */
    Board result;

    if ( fpointer != NULL ){
      fgets(chip, 256 , fpointer);
    }else{
      printf("cannot read Board");
      result.chip , result.version = NULL;
      return result;
    }


    chip[strlen(chip)-1] = '\0'; //deletes \n //

    result.chip = malloc(sizeof(char)*strlen(chip)+1);
    strcpy(result.chip,chip);
    free(chip);
    fclose(fpointer);

    FILE *fpointer2 = fopen ("/sys/devices/virtual/dmi/id/board_version","r");
    char *version = calloc(sizeof(char),4); //I suppose there can´t be a bigger version that x.x// 
    
    if (fpointer2 != NULL ){
      fgets(version, 4 , fpointer2);
    }else{
      result.chip , result.version = NULL;
      printf("cannot read Board");
      return result;
    }

    if(strcmp(version, "x.x")== 0){
      result.version = malloc(sizeof(char));
      strcpy(result.version,"\0");
    }else{
      result.version = malloc(sizeof(char)*strlen(version)+1);
      strcpy(result.version,version);
    }
  
    free(version);
    fclose(fpointer2);
   
  #endif

      return result;
    
}

char *Xnotfound(){
  
  int i = 0;
  int j = 0;
  int w;
  int h;
  char read [1024];
  Display *display = XOpenDisplay(NULL);
  if(display == NULL){    
    FILE *fp = popen("command -v xdpyinfo | wc -l","r");
    char num[2];
    fgets(num,2,fp);
    if(strcmp(num,"0") == 0){
      pclose(fp);
      fp = popen("command -v xwininfo | wc -l","r");
      fgets(num,2,fp);
      if(strcmp(num,"0") == 0){
        return "Unkown";
      }else{
        pclose(fp);
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
        return result;
      }
    }else{
      pclose(fp);
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
      return result;
    } 
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

char *getDisplay(){

  FILE *fp;
  char tmp[200];
  char num[2];
  fp = popen("command -v xrandr | wc -l","r");
  fgets(num,2,fp);

  if(strcmp(num,"0") == 0){
    pclose(fp);
    char *result = Xnotfound();
    return result;

  }else{
    pclose(fp);
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
    return NULL;
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
  char read[1024];
  char *tmp;
  int i = 1;
  fgets(read,1024,fp);
  if((tmp = strchr(read,'[')) == NULL){
    tmp = strrchr(read,':');
    tmp++;
    i = strlen(tmp)+1;
    char *result = malloc(sizeof(char)*i);
    strcpy(result,tmp);
    result[i-2] = '\0';
    pclose(fp);
    return result;
  }
  
  while(tmp[i] != ']'){
    i++;
  }
  
  char *result = malloc(sizeof(char)*i+1);
  strncpy(result,tmp,i);
  result[i] = '\0';
  result[0] = ' ';
  pclose(fp);
  return result;

}
