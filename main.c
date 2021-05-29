
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
  char *name;
  char *user;
  char *board;

};

typedef struct PcRep Pc;

int main(){
  Pc computer;
  computer.os = getOS();
  computer.name = getHost();
  computer.user = getUser();
  computer.board = getBoard();
  int n = strlen(computer.user)+strlen(computer.name)+2;
  char *bars = fillString('-',n);
  printf("%s@%s\n",computer.user,computer.name);
  printf("%s\n",bars);
  printf("OS: %s\n",computer.os);
  printf("MotherBoard: %s",computer.board);//computer.board has his own \n//
}
