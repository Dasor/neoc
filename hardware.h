#ifndef HARDWARE_H
#define HARDWARE_H


struct BoardRep{
  
  char *chip;
  char *version;

};

typedef struct BoardRep Board;

Board getBoard();
char *getDisplay();
char *getDisplays();
char *getCpu();
char *getGpu();
char *getMemory();
char *getDisk();

#endif
