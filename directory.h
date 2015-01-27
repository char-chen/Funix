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
	struct Dir *(*pts)[];	//pointer to the array of subdirectories
  struct Dir *ptSub[MAX_SUBDIRECTORIES];
 	int numberOfSubdirectories;
 	struct Dir *parent;
	Permissions permission;
	
} Directory;


Directory *createDirectory(const char *directoryName, int time, int umask);

//char *showPath(Directory *currentDirectory, char *paths);

void mkdir(Directory *currentDirectory, const char *name, int time, int umask);

void ls(Directory *currentDirectory, int l);

void cd(Directory *currentDirectory, const char *directoryToEnter);
#endif	
