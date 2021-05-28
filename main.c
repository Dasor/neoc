
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "os.h"

struct PcRep{
  char *os;


};

typedef struct PcRep Pc;

int main(){
  Pc computer;
  computer.os = getOS();
  printf("%s\n", computer.os);

}
