
#include <unistd.h>
#include<string.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include "software.h"
#include "hardware.h"
#include "others.h"


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
  int n = strlen(computer.user)+strlen(computer.name)+2;
  char *bars = fillString('-',n);
  printf("%s@%s\n",computer.user,computer.name);
  printf("%s\n",bars);
  printf("OS: %s %s\n",computer.os,computer.bits);
  printf("MotherBoard: %s %s\n",computer.board.chip,computer.board.version);
  printf("Kernel: %s\n",computer.kernel);
  if(computer.uptime > 86400){
    printf("Uptime : %ld days, %ld hours, %ld mins\n",computer.uptime/86400, (computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
  }else if(computer.uptime > 3600){
    printf("Uptime : %ld hours, %ld mins\n",(computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);
  }else {
    printf("Uptime : %ld mins\n",(computer.uptime % 3600) / 60);
  }
  if(computer.pkg[1].npacks == 0){
    printf("Packages: %d (%s)\n",computer.pkg[0].npacks,computer.pkg[0].manager);
  }else{
    printf("Packages: %d (%s), %d (%s)\n",computer.pkg[0].npacks,computer.pkg[0].manager,computer.pkg[1].npacks,computer.pkg[1].manager);
  }
  printf("Shell:%s\n",computer.shell);
  printf("Resolution: %s\n",computer.display);
  if(computer.DE != NULL){
    printf("DE: %s\n",computer.DE);
  }
  printf("Terminal: %s\n",computer.term);
  printf("CPU%s",computer.cpu);
  printf("GPU: %s\n",computer.gpu);

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
