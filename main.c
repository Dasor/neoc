
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
  int n = strlen(computer.user)+strlen(computer.name)+2;
  char *bars = fillString('-',n);
  printf("%s@%s\n",computer.user,computer.name);
  printf("%s\n",bars);
  printf("OS: %s %s\n",computer.os,computer.bits);
  printf("MotherBoard: %s %s\n",computer.board.chip,computer.board.version);
  printf("Kernel: %s\n",computer.kernel);
  printf ("Uptime : %ld hours, %ld mins\n", (computer.uptime % 86400) / 3600, (computer.uptime % 3600) / 60);

  free(computer.board.version);
  free(computer.os);
  free(computer.name);
  free(computer.board.chip);
  free(computer.kernel);
  free(bars);
  free(computer.bits);
}
