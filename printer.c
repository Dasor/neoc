
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hardware.h"
#include "software.h"
#include "main.h"
#include "others.h"
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
  free(computer->board.version);
  free(computer->os);
  free(computer->name);
  free(computer->board.chip);
  free(computer->kernel);
  free(computer->bits);
  free(computer->disk);
  free(computer);
}

void printall(Info *computer){

  int ninfo = 0;  
  char info[15][100];
  char *bars;

  //print all//
  if(computer->user != NULL && computer->name != NULL){
    sprintf(info[ninfo],"%s""%s"RESET"@""%s""%s\n"RESET,color,computer->user,color,computer->name);
    int n = strlen(computer->user)+strlen(computer->name)+2;
    bars = fillString('-',n);
    ninfo++;
  }else if(computer->user == NULL && computer->name == NULL){
    sprintf(info[ninfo],"%s""Unknown"RESET"@""%s""Unknown"RESET,color,color);
    int n = 15;
    bars = fillString('-',n);
    ninfo++;
  }else if(computer->user == NULL){
    sprintf(info[ninfo],"%s""Unkown"RESET"@""%s""%s\n"RESET,color,color,computer->name);
    int n = strlen(computer->user)+8;
    bars = fillString('-',n);
    ninfo++;
  }else if(computer->name == NULL){
    sprintf(info[ninfo],"%s""%s"RESET"@""%s""Unkown\n"RESET,color,computer->user,color);
    int n = 8+strlen(computer->name);
    bars = fillString('-',n); 
    ninfo++;
  }

  sprintf(info[ninfo],RESET"%s\n",bars);
  ninfo++;

  if(computer->os != NULL){
    sprintf(info[ninfo],"%s""OS"RESET": %s %s\n",color,computer->os,computer->bits);
    ninfo++;
  }

  if(computer->board.chip != NULL && computer->board.version != NULL){
    sprintf(info[ninfo],"%s""MotherBoard"RESET": %s %s\n",color,computer->board.chip,computer->board.version);
    ninfo++;
  }

  if(computer->kernel != NULL){
    sprintf(info[ninfo],"%s""Kernel"RESET": %s\n",color,computer->kernel);
    ninfo++;
  }

  if(computer->uptime > 86400){
    sprintf(info[ninfo],"%s""Uptime"RESET": %ld days, %ld hours, %ld mins\n",color,computer->uptime/86400, (computer->uptime % 86400) / 3600, (computer->uptime % 3600) / 60);
    ninfo++;
  }else if(computer->uptime > 3600){
    sprintf(info[ninfo],"%s""Uptime"RESET": %ld hours, %ld mins\n",color,(computer->uptime % 86400) / 3600, (computer->uptime % 3600) / 60);
    ninfo++;
  }else if(computer->uptime == -1){
    sprintf(info[ninfo],"%s""Uptime"RESET": Unkown\n",color);
    ninfo++;
  }else{
    sprintf(info[ninfo],"%s""Uptime"RESET": %ld mins\n",color,(computer->uptime % 3600) / 60);
    ninfo++;
  }
  
  if(computer->pkg != NULL){
    sprintf(info[ninfo],"%s""Packages"RESET": %s\n",color,computer->pkg); 
    ninfo++;
  }

  if(computer->shell != NULL){ 
    sprintf(info[ninfo],"%s""Shell"RESET":%s\n",color,computer->shell);
    ninfo++;
  }

  if(computer->display != NULL){
    sprintf(info[ninfo],"%s""Resolution"RESET": %s\n",color,computer->display);
    ninfo++;
  }

  if(computer->DE != NULL){
    sprintf(info[ninfo],"%s""DE"RESET": %s\n",color,computer->DE);
    ninfo++;
  }

  if(computer->term != NULL){
    sprintf(info[ninfo],"%s""Terminal"RESET": %s\n",color,computer->term);
    ninfo++;
  }

  if(computer->cpu != NULL){
    sprintf(info[ninfo],"%s""CPU"RESET"%s",color,computer->cpu);
    ninfo++;
  }

  if(computer->gpu != NULL){
    sprintf(info[ninfo],"%s""GPU"RESET": %s\n",color,computer->gpu);
    ninfo++;
  }
  
  if(computer->memory != NULL){
    sprintf(info[ninfo],"%s""Memory"RESET": %s\n",color,computer->memory);
    ninfo++;
  }

  if(computer->disk != NULL){
    sprintf(info[ninfo],"%s""Disk"RESET": %s\n" ,color,computer->disk);
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
