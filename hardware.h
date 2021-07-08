#ifndef HARDWARE_H
#define HARDWARE_H


typedef struct{
  
  char *chip;
  char *version;

}Board;


Board *getBoard();
char *getDisplay();
char *getDisplays();
char *getCpu();
char *getGpu();
char *getMemory();
char *getDisk();

#endif
