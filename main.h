
#ifndef MAIN_H
#define MAIN_H


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

#endif
