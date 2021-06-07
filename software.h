#ifndef OS_H
#define OS_H


struct PackagesRep {

int npacks;
char *manager;

};

typedef struct PackagesRep Pack;

char *getOS();
char *getBits();
char *getHost();
char *getUser();
char *getKernel();
long getUptime();
Pack *getPacks();
char *getShell();
char *getDE();

#endif
