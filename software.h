#ifndef SOFTWARE_H
#define SOFTWARE_H


struct LogoRep {

  int height;
  char *logo;
  char *color;

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
