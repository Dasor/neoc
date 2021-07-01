
#include <unistd.h>
#include<string.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include "software.h"
#include "hardware.h"
#include "others.h"
#include <math.h>
#define RESET "\033[0m"
#define color computer.logo->color

struct PcRep{
  char *os;
  char *bits;
  char *name;
  char *user;
  Board board;
  char *kernel;
  long uptime;
  char *pkg;
  char *shell;
  char *display;
  char *DE;
  char *term;
  char *cpu;
  char *gpu;
  char *memory;
  char *disk;
  Logo *logo;

};

typedef struct PcRep Pc;
int main(){
  char info[15][100];

  Pc computer;
  computer.os = getOS();
  computer.bits = getBits();
  computer.name = getHost();
  computer.user = getUser();
  computer.board = getBoard();
  computer.kernel = getKernel();
  computer.uptime = getUptime();
  computer.pkg = getPacks();
  computer.shell = getShell();
  computer.display = getDisplay();
  computer.DE = getDE();
  computer.term = getTerm();
  computer.cpu = getCpu();
  computer.gpu = getGpu();
  computer.memory = getMemory();
  computer.disk = getDisk();
  computer.logo = getLogo(computer.os);
  int j = 0;
  char *bars;
  if(computer.user != NULL && computer.name != NULL){
    sprintf(info[j],"%s""%s"RESET"@""%s""%s\n"RESET,color,computer.user,color,computer.name);
    int n = strlen(computer.user)+strlen(computer.name)+2;
    bars = fillString('-',n);
    j++;
  }else if(computer.user == NULL && computer.name == NULL){
    sprintf(info[j],"%s""Unknown"RESET"@""%s""Unknown"RESET,color,color);
    int n = 15;
    bars = fillString('-',n);
    j++;
  }else if(computer.user == NULL){
    sprintf(info[j],"%s""Unkown"RESET"@""%s""%s\n"RESET,color,color,computer.name);
    int n = strlen(computer.user)+8;
    bars = fillString('-',n);
    j++;
  }else if(computer.name == NULL){
    sprintf(info[j],"%s""%s"RESET"@""%s""Unkown\n"RESET,color,computer.user,color);
    int n = 8+strlen(computer.name);
    bars = fillString('-',n); 
    j++;
  }

  sprintf(info[j],RESET"%s\n",bars);
  j++;

  if(computer.os != NULL){
    sprintf(info[j],"%s""OS"RESET": %s %s\n",color,computer.os,computer.bits);
    j++;
  }

  if(computer.board.chip != NULL && computer.board.version != NULL){
    sprintf(info[j],"%s""MotherBoard"RESET": %s %s\n",color,computer.board.chip,computer.board.version);
    j++;
  }

  if(computer.kernel != NULL){
    sprintf(info[j],"%s""Kernel"RESET": %s\n",color,computer.kernel);
    j++;
  }

  if(computer.uptime > 86400){
    sprintf(info[j],"%s""Uptime"RESET": %ld days, %ld hours, %ld mins\n",color,computer.uptime/86400, (computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
    j++;
  }else if(computer.uptime > 3600){
    sprintf(info[j],"%s""Uptime"RESET": %ld hours, %ld mins\n",color,(computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
    j++;
  }else if(computer.uptime == -1){
    sprintf(info[j],"%s""Uptime"RESET": Unkown\n",color);
    j++;
  }else{
    sprintf(info[j],"%s""Uptime"RESET": %ld mins\n",color,(computer.uptime % 3600) / 60);
    j++;
  }
  
  if(computer.pkg != NULL){
    sprintf(info[j],"%s""Packages"RESET": %s\n",color,computer.pkg); 
    j++;
  }

  if(computer.shell != NULL){ 
    sprintf(info[j],"%s""Shell"RESET":%s\n",color,computer.shell);
    j++;
  }

  if(computer.display != NULL){
    sprintf(info[j],"%s""Resolution"RESET": %s\n",color,computer.display);
    j++;
  }

  if(computer.DE != NULL){
    sprintf(info[j],"%s""DE"RESET": %s\n",color,computer.DE);
    j++;
  }

  if(computer.term != NULL){
    sprintf(info[j],"%s""Terminal"RESET": %s\n",color,computer.term);
    j++;
  }

  if(computer.cpu != NULL){
    sprintf(info[j],"%s""CPU"RESET"%s",color,computer.cpu);
    j++;
  }

  if(computer.gpu != NULL){
    sprintf(info[j],"%s""GPU"RESET": %s\n",color,computer.gpu);
    j++;
  }
  
  if(computer.memory != NULL){
    sprintf(info[j],"%s""Memory"RESET": %s\n",color,computer.memory);
    j++;
  }

  if(computer.disk != NULL){
    sprintf(info[j],"%s""Disk"RESET": %s\n" ,color,computer.disk);
    j++;
  }

  int y = 0;
  for(int i = 0; i<computer.logo->height;i++){
    while(computer.logo->logo[y] != '\0'){
      printf("%c",computer.logo->logo[y]);
      y++;
    }
    if(i<j){
      printf("%s",info[i]);
      y++;
    }else{
      printf("\n");
      y++;
    }
  }
  
  printf(RESET);

  free(computer.logo);
  free(computer.memory);
  free(computer.gpu);
  free(computer.cpu);
  free(computer.term);
  free(computer.display);
  free(computer.pkg);
  free(computer.board.version);
  free(computer.os);
  free(computer.name);
  free(computer.board.chip);
  free(computer.kernel);
  free(bars);
  free(computer.bits);
  free(computer.disk);
}
