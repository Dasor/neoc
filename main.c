
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


  char *bars;
  if(computer.user != NULL && computer.name != NULL){
    sprintf(info[0],"%s@%s\n",computer.user,computer.name);
    int n = strlen(computer.user)+strlen(computer.name)+2;
    bars = fillString('-',n);
  }else if(computer.user == NULL && computer.name == NULL){
    sprintf(info[0],"Unkown@Unkown\n");
    int n = 15;
    bars = fillString('-',n);
  }else if(computer.user == NULL){
    sprintf(info[0],"Unkown@%s\n",computer.name);
    int n = strlen(computer.user)+8;
    bars = fillString('-',n);
  }else if(computer.name == NULL){
    sprintf(info[0],"%s@Unkown\n",computer.user);
    int n = 8+strlen(computer.name);
    bars = fillString('-',n); 
  }

  sprintf(info[1],"%s\n",bars);

  if(computer.os != NULL){
    sprintf(info[2],"OS: %s %s\n",computer.os,computer.bits);
  }else{
    sprintf(info[2],"OS: Unkown\n");
  }

  if(computer.board.chip != NULL && computer.board.version != NULL){
    sprintf(info[3],"MotherBoard: %s %s\n",computer.board.chip,computer.board.version);
  }else{
    sprintf(info[3],"MotherBoard: Unkown\n");
  }

  if(computer.kernel != NULL){
    sprintf(info[4],"Kernel: %s\n",computer.kernel);
  }else{
    sprintf(info[4],"Kernel: Unkown\n");
  }

  if(computer.uptime > 86400){
    sprintf(info[5],"Uptime : %ld days, %ld hours, %ld mins\n",computer.uptime/86400, (computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
  }else if(computer.uptime > 3600){
    sprintf(info[5],"Uptime : %ld hours, %ld mins\n",(computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
  }else if(computer.uptime == -1){
    sprintf(info[5],"Uptime: Unkown\n");
  }else{
    sprintf(info[5],"Uptime : %ld mins\n",(computer.uptime % 3600) / 60);
  }

  sprintf(info[6],"Packages: %s\n",computer.pkg); 

  if(computer.shell != NULL){
    sprintf(info[7],"Shell:%s\n",computer.shell);
  }else{
    sprintf(info[7],"Shell: Unkown\n");
  }

  if(computer.display != NULL){
    sprintf(info[8],"Resolution: %s\n",computer.display);
  }else{
    sprintf(info[8],"Resolution: Unkown\n");
  }

  if(computer.DE != NULL){
    sprintf(info[9],"DE: %s\n",computer.DE);
  }

  if(computer.term != NULL){
    sprintf(info[10],"Terminal: %s\n",computer.term);
  }else{
    sprintf(info[10],"Terminal: Unkown\n");
  }

  if(computer.cpu != NULL){
    sprintf(info[11],"CPU%s",computer.cpu);
  }else{
    sprintf(info[11],"CPU: Unkown\n");
  }

  if(computer.gpu != NULL){
    sprintf(info[12],"GPU: %s\n",computer.gpu);
  }else{
    sprintf(info[12],"GPU: Unkown\n");
  }
  
  if(computer.memory != NULL){
    sprintf(info[13],"Memory: %s\n",computer.memory);
  }else{
    sprintf(info[13],"Memory: Unkown\n");
  }

  for(int i = 0; i<13;i++){
    printf("%s",info[i]);
  }

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
}
