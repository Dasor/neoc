#ifndef OS_H
#define OS_H


struct LogoRep {

  int width;
  int height;
  char *logo;

};

typedef struct LogoRep Logo;

char *getOS();
char *getBits();
char *getHost();
char *getUser();
char *getKernel();
long getUptime();
char *getPacks();
char *getShell();
char *getDE();
char *getTerm();
Logo *getLogo(char *string);

#endif
