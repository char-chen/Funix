//Author: Charles Chen
#ifndef DIRECTORY_H
	#define DIRECTORY_H
#include <stdlib.h>
#include "permissions.h"
#define MAX_SUBDIRECTORIES 3

typedef struct Dir
{
  const char* name;
 	int time;
  struct Dir *ptSub[MAX_SUBDIRECTORIES];
 	int numberOfSubdirectories;
 	struct Dir *parent;
	Permissions permission;
	
} Directory;


Directory *createDirectory(const char *directoryName, int time, int umask);

int showPath(Directory *currentDirectory);

void mkdir(Directory *currentDirectory, const char *name, int time, int umask);

void ls(Directory *currentDirectory, int l);

void cd(Directory **current, const char *directoryToEnter);
#endif	
