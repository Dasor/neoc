
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
  Pack *pkg;
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
    printf("%s@%s\n",computer.user,computer.name);
    int n = strlen(computer.user)+strlen(computer.name)+2;
    bars = fillString('-',n);
  }else if(computer.user == NULL && computer.name == NULL){
    printf("Unkown@Unkown\n");
    int n =15;
    bars = fillString('-',n);
  }else if(computer.user == NULL){
    printf("Unkown@%s\n",computer.name);
    int n = strlen(computer.user)+8;
    bars = fillString('-',n);
  }else if(computer.name == NULL){
    printf("%s@Unkown\n",computer.user);
    int n = 8+strlen(computer.name);
    bars = fillString('-',n); 
  }

  printf("%s\n",bars);

  if(computer.os != NULL){
    printf("OS: %s %s\n",computer.os,computer.bits);
  }else{
    printf("OS: Unkown\n");
  }

  if(computer.board.chip != NULL && computer.board.version != NULL){
    printf("MotherBoard: %s %s\n",computer.board.chip,computer.board.version);
  }else{
    printf("MotherBoard: Unkown\n");
  }

  if(computer.kernel != NULL){
    printf("Kernel: %s\n",computer.kernel);
  }else{
    printf("Kernel: Unkown\n");
  }

  if(computer.uptime > 86400){
    printf("Uptime : %ld days, %ld hours, %ld mins\n",computer.uptime/86400, (computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
  }else if(computer.uptime > 3600){
    printf("Uptime : %ld hours, %ld mins\n",(computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
  }else if(computer.uptime == -1){
    printf("Uptime: Unkown\n");
  }else{
    printf("Uptime : %ld mins\n",(computer.uptime % 3600) / 60);
  }

  if(computer.pkg[1].npacks == 0){
    printf("Packages: %d (%s)\n",computer.pkg[0].npacks,computer.pkg[0].manager);
  }else{
    printf("Packages: %d (%s), %d (%s)\n",computer.pkg[0].npacks,computer.pkg[0].manager,computer.pkg[1].npacks,computer.pkg[1].manager);
  }

  if(computer.shell != NULL){
    printf("Shell:%s\n",computer.shell);
  }else{
    printf("Shell: Unkown\n");
  }

  if(computer.display != NULL){
    printf("Resolution: %s\n",computer.display);
  }else{
    printf("Resolution: Unkown\n");
  }

  if(computer.DE != NULL){
    printf("DE: %s\n",computer.DE);
  }

  if(computer.term != NULL){
    printf("Terminal: %s\n",computer.term);
  }else{
    printf("Terminal: Unkown\n");
  }

  if(computer.cpu != NULL){
    printf("CPU%s",computer.cpu);
  }else{
    printf("CPU: Unkown\n");
  }

  if(computer.gpu != NULL){
    printf("GPU: %s\n",computer.gpu);
  }else{
    printf("GPU: Unkown\n");
  }
  
  if(computer.memory != NULL){
    printf("Memory: %s\n",computer.memory);
  }else{
    printf("Memory: Unkown\n");
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
