#define _DEFAULT_SOURCE
#include <sys/statvfs.h>
#include <X11/Xlib.h>
#include <pci/pci.h>
#include <X11/Xatom.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "others.h"
#include "intelgpu.h"
#define GB 1000000000
#define KB 1000000
#define BIG_SIZE 1024
#define MEDIUM_SIZE 256
#define SMALL_SIZE 20

typedef struct{
  
  char *chip;
  char *version;

}Board;


Board *getBoard(){
  
    FILE *fpointer = fopen ("/sys/devices/virtual/dmi/id/board_name","r");
    Board *result = malloc(sizeof(Board));
    result->chip = malloc(sizeof(char)*MEDIUM_SIZE); /* or other suitable maximum line size */

    if ( fpointer != NULL ){
      fgets(result->chip, MEDIUM_SIZE , fpointer);
    }else{
      printf("cannot read Board");
      free(result);
      return NULL;
    }


    result->chip[strlen(result->chip)-1] = '\0'; //deletes \n //
    fclose(fpointer);

    fpointer = fopen ("/sys/devices/virtual/dmi/id/board_version","r");
    result->version = malloc(sizeof(char)*4); //I suppose there can´t be a bigger version that x.x// 
    
    if (fpointer != NULL ){
      fgets(result->version, 4 , fpointer);
    }else{
      printf("cannot read Board");
      free(result);
      return NULL;
    }

    if(strcmp(result->version, "x.x") == 0 || strcmp(result->version,"\n") == 0){
      result->version[0] = '\0';
    }  
    fclose(fpointer);
   
    return result;
    
}

char *getDisplay(){

  Display *display = XOpenDisplay(NULL);
  if(display == NULL){
    return NULL;
}

  Screen *screen = DefaultScreenOfDisplay(display);

  int w = WidthOfScreen(screen);
  int h = HeightOfScreen(screen);
    

  char *result = malloc(sizeof(char)*SMALL_SIZE);
  sprintf(result,"%dx%d",w,h);
  XCloseDisplay(display);

  return result;
}   

char *getDisplays(){


  FILE *fp;
  char read[MEDIUM_SIZE];
  char *resolution;
  char *result = calloc(sizeof(char),BIG_SIZE);

  if(system("xrandr >>/dev/null 2>>/dev/null") != 0){
    printf("You need to have xrandr to get several displays\n");
    return NULL;
  }

  fp = popen("xrandr | grep \'*\'","r"); 
  while(fgets(read,MEDIUM_SIZE,fp) != NULL){
   resolution = numUntilchar(read,' '); 
   strcat(result,resolution);
   strcat(result," ");
   free(resolution);
  } 
  pclose(fp);
  return result;
}



char *getCpu(){

  FILE *fp = fopen("/proc/cpuinfo","r");
  char read [BIG_SIZE];
  if(fp != NULL){
    while(fgets(read,BIG_SIZE,fp) != NULL && strstr(read,"model name") == NULL );
  }else{
    printf("Cannot read Cpu\n");
    return "NULL";
  }

  fclose(fp);
  char *result = fixString(read,':','\n',1); 
  return result;

}

char *getGpu(){

  struct pci_access *pacc;
  struct pci_dev *dev;
  char namebuf[BIG_SIZE];
  char *name = malloc(sizeof(char)*MEDIUM_SIZE);
  char *class;
  char *intelgpu; 
  int i = 0;
  int id;

  pacc = pci_alloc();		/* Get the pci_access structure */
  /* Set all options you want -- here we stick with the defaults */
  pci_init(pacc);		/* Initialize the PCI library */
  pci_scan_bus(pacc);		/* We want to get the list of devices */
  for (dev=pacc->devices; dev; dev=dev->next){
      pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);	/* Fill in header info we need */
      class = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_CLASS, dev->device_class);
       if(strcmp("VGA compatible controller",class) == 0 || strcmp("3D controller",class) == 0){
         strcpy(name,pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id));
         i++;
         id = dev->device_id;
         if(strchr(name,'[') != NULL){
          name = fixString(name,'[',']',0);
          pci_cleanup(pacc);		/* Close everything */
          return name;
         }
       }
    }
  pci_cleanup(pacc);		/* Close everything */
  if(i == 0){ //no gpu
    free(name);
    name = NULL;
  }else{
    intelgpu = find_gpu(id);
    if(intelgpu != NULL){
      free(name);
      name = malloc(sizeof(char)*MEDIUM_SIZE);
      strcpy(name,intelgpu);
      free(intelgpu);
    }
  }
  return name;
}

char *getMemory(){
    int total_memory, used_memory;
    int total, shared, memfree, buffers, cached, reclaimable;

    FILE *meminfo = fopen("/proc/meminfo", "r"); /* get infomation from meminfo */
    if(meminfo == NULL) {
      return NULL;
    }

    /* We parse through all lines of meminfo and scan for the information we need */
    char *line = NULL; // allocation handled automatically by getline()
    size_t len; /* unused */

    /* parse until EOF */
    while (getline(&line, &len, meminfo) != -1) {
        /* if sscanf doesn't find a match, pointer is untouched */
        sscanf(line, "MemTotal: %d", &total);
        sscanf(line, "Shmem: %d", &shared);
        sscanf(line, "MemFree: %d", &memfree);
        sscanf(line, "Buffers: %d", &buffers);
        sscanf(line, "Cached: %d", &cached);
        sscanf(line, "SReclaimable: %d", &reclaimable);
    }

    free(line);

    fclose(meminfo);

    /* use same calculation as neofetch */
    used_memory = (total + shared - memfree - buffers - cached - reclaimable) / 1024;
    total_memory = total / 1024;
    int percentage = (int) (100 * (used_memory / (double) total_memory));

    char *memory = malloc(sizeof(char)*MEDIUM_SIZE);
    snprintf(memory, MEDIUM_SIZE, "%dMiB / %dMiB (%d%%)", used_memory, total_memory, percentage);

    return memory;

}

char *getDisk(){
  int state;
  int block_size;
  double total; 
  double free;
  struct statvfs vfs;
  char *disk = malloc(sizeof(char)*MEDIUM_SIZE);
  state = statvfs("/",&vfs);
  if(state != 0){
    return NULL;
  }
  block_size = vfs.f_bsize;
  total = ((double)vfs.f_blocks * block_size);
  free = ((double)vfs.f_bfree * block_size);
  double percentaje = ( ((total-free)/GB) / (total/GB) ) * 100;
  if(free > GB ){
    snprintf(disk,MEDIUM_SIZE, "%.1lfGB / %.1lfGB (%.0lf%%)",free/GB, total/GB, percentaje);
  }else{
    snprintf(disk,MEDIUM_SIZE, "%1.lfKB / %1.ffGB (%.0lf%%)",free/KB,total/GB,percentaje);
  }
  return disk;

}
