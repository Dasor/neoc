#ifndef LOGOS_H
#define LOGOS_H

typedef struct{

  int height;
  char *logo;
  char *color;

}Logo;

Logo *getLogo(char *string);
#endif
