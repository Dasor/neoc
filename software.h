#ifndef SOFTWARE_H
#define SOFTWARE_H


typedef struct{

  int height;
  char *logo;
  char *color;

}Logo;

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
