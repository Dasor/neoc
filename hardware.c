
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <limits.h>

struct BoardRep{
  
  char *chip;
  char *version;

};

typedef struct BoardRep Board;



Board getBoard(){
 #ifdef __linux__
  
    FILE *fpointer = fopen ("/sys/devices/virtual/dmi/id/board_name","r");
    char *chip = calloc(sizeof(char),256); /* or other suitable maximum line size */
    Board result;

    if ( fpointer != NULL ){
      fgets(chip, 256 , fpointer);
    }else{
      printf("cannot read Board");
      result.chip , result.version = NULL;
      return result;
    }

    fclose(fpointer);
    int len = strlen(chip); // chip has his own /n but I dont want it//
    chip[len-1] = '\0';
    result.chip = chip;

    FILE *fpointer2 = fopen ("/sys/devices/virtual/dmi/id/board_version","r");
    char *version = calloc(sizeof(char),4); //I suppose there can´t be a bigger version that x.x// 
    
    if (fpointer2 != NULL ){
      fgets(version, 4 , fpointer2);
    }else{
      result.chip , result.version = NULL;
      printf("cannot read Board");
      return result;
    }

    if(strcmp(version, "x.x")== 0){
      free (version);
      version = "\0";
    }

    fclose(fpointer2);
    result.version = version;

  #endif

      return result;
    
}



