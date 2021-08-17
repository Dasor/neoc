
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "logos.h"
#include "hardware.h"
#include "software.h"
#include "main.h"
#include "others.h"
#define WHITE "\033[37m"
#define RESET "\033[0m"
#define color computer->logo->color

void freeall(Info *computer){

  free(computer->logo);
  free(computer->memory);
  free(computer->gpu);
  free(computer->cpu);
  free(computer->term);
  free(computer->display);
  free(computer->pkg);
  free(computer->board->version);
  free(computer->os);
  free(computer->name);
  free(computer->board->chip);
  free(computer->board);
  free(computer->kernel);
  free(computer->bits);
  free(computer->disk);
  free(computer);
}

void printall(Info *computer){

  int ninfo = 0;  
  char info[15][100];
  char *bars;
  int numofbars;

  //print all//
  if(computer->user != NULL && computer->name != NULL){
    sprintf(info[ninfo],"%s""%s"WHITE"@""%s""%s\n"WHITE,color,computer->user,color,computer->name);
    numofbars = strlen(computer->user)+strlen(computer->name)+2;
  }else{
    sprintf(info[ninfo],"Unknown@Unknown");
    numofbars = 15;
  }
  
  bars = fillString('-',numofbars);
  ninfo++;

  sprintf(info[ninfo],WHITE"%s\n",bars);
  ninfo++;

  if(computer->os != NULL){
    sprintf(info[ninfo],"%s""OS"WHITE": %s %s\n",color,computer->os,computer->bits);
    ninfo++;
  }

  if(computer->board != NULL){
    sprintf(info[ninfo],"%s""MotherBoard"WHITE": %s %s\n",color,computer->board->chip,computer->board->version);
    ninfo++;
  }

  if(computer->kernel != NULL){
    sprintf(info[ninfo],"%s""Kernel"WHITE": %s\n",color,computer->kernel);
    ninfo++;
  }

  if(computer->uptime > 86400){
    sprintf(info[ninfo],"%s""Uptime"WHITE": %ld days, %ld hours, %ld mins\n",color,computer->uptime/86400, (computer->uptime % 86400) / 3600, (computer->uptime % 3600) / 60);
    ninfo++;
  }else if(computer->uptime > 3600){
    sprintf(info[ninfo],"%s""Uptime"WHITE": %ld hours, %ld mins\n",color,(computer->uptime % 86400) / 3600, (computer->uptime % 3600) / 60);
    ninfo++;
  }else if(computer->uptime == -1){
    sprintf(info[ninfo],"%s""Uptime"WHITE": Unkown\n",color);
    ninfo++;
  }else{
    sprintf(info[ninfo],"%s""Uptime"WHITE": %ld mins\n",color,(computer->uptime % 3600) / 60);
    ninfo++;
  }
  
  if(computer->pkg != NULL){
    sprintf(info[ninfo],"%s""Packages"WHITE": %s\n",color,computer->pkg); 
    ninfo++;
  }

  if(computer->shell != NULL){ 
    sprintf(info[ninfo],"%s""Shell"WHITE":%s\n",color,computer->shell);
    ninfo++;
  }

  if(computer->display != NULL){
    sprintf(info[ninfo],"%s""Resolution"WHITE": %s\n",color,computer->display);
    ninfo++;
  }

  if(computer->DE != NULL){
    sprintf(info[ninfo],"%s""DE"WHITE": %s\n",color,computer->DE);
    ninfo++;
  }

  if(computer->term != NULL){
    sprintf(info[ninfo],"%s""Terminal"WHITE": %s\n",color,computer->term);
    ninfo++;
  }

  if(computer->cpu != NULL){
    sprintf(info[ninfo],"%s""CPU"WHITE":%s\n",color,computer->cpu);
    ninfo++;
  }

  if(computer->gpu != NULL){
    sprintf(info[ninfo],"%s""GPU"WHITE": %s\n",color,computer->gpu);
    ninfo++;
  }
  
  if(computer->memory != NULL){
    sprintf(info[ninfo],"%s""Memory"WHITE": %s\n",color,computer->memory);
    ninfo++;
  }

  if(computer->disk != NULL){
    sprintf(info[ninfo],"%s""Disk"WHITE": %s\n" ,color,computer->disk);
    ninfo++;
  }

  int y = 0;
  for(int i = 0; i<computer->logo->height;i++){
    while(computer->logo->logo[y] != '\0'){
      printf("%c",computer->logo->logo[y]);
      y++;
    }
    if(i<ninfo){
      printf("%s",info[i]);
      y++;
    }else{
      printf("\n");
      y++;
    }
  }
  
  printf(RESET);
  free(bars);
}

void printhelp(){

  printf("Options:\n --logo [distro]       Changes the logo to other distro, ej: ./neoc --logo Gentoo.\n " );
  printf("--help                Prints this help and exits\n ");
  printf("--multiple-displays   Prints displays separately (slower performance)\n");

}
