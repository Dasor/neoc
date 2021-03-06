
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "software.h"
#include "hardware.h"
#include "others.h"
#include "logos.h"

struct InfoRep{
  char *os;
  char *bits;
  char *name;
  char *user;
  Board *board;
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

typedef struct InfoRep Info;

#include "printer.h"

int main(int argc, char *argv[]){

  if(argv[1] != NULL && strcmp(argv[1],"--help") == 0){
    printhelp();
    return 0;
  }
  Info *computer = malloc(sizeof(Info));
  //get all info
  computer->os = getOS();
  computer->bits = getBits();
  computer->name = getHost();
  computer->user = getUser();
  computer->board = getBoard();
  computer->kernel = getKernel();
  computer->uptime = getUptime();
  computer->pkg = getPacks();
  computer->shell = getShell();
  if(argv[1] != NULL && strcmp(argv[1],"--multiple-displays") == 0){
    computer->display = getDisplays();
  }else{
    computer->display = getDisplay();
  }
  computer->DE = getDE();
  computer->term = getTerm();
  computer->cpu = getCpu();
  computer->gpu = getGpu();
  computer->memory = getMemory();
  computer->disk = getDisk();
  if(argc == 3 && strcmp(argv[1],"--logo") == 0){
    computer->logo = getLogo(argv[2]);
  }else{
    computer->logo = getLogo(computer->os);
  }

  printall(computer);
  freeall(computer);

}
