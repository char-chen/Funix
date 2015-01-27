#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "directory.h"

/*char *showPath(Directory *currentDir, char *path) 
{
	if(currentDir->parent != NULL)
	{ 
		path = strcat(currentDir->parent->name, strcat(path, "/"));
		showPath(currentDir->parent, path);
	}
	
	return path;
}	
*/

void ls(Directory *currentDir, int l)
{
	int i;
	int n = currentDir->numberOfSubdirectories;
	if(l)	//the "ls -l" option
	{
		for(i = 0; i < n; i++ )
		{
			printPermissions(&(currentDir->ptSub[i]->permission));
			printf(" %d %s\n", currentDir->ptSub[i]->time, currentDir->ptSub[i]->name);
		}
	}
	else	//the "ls" command
	{
		for(i = 0; i < n; i++)
		{
			printf("%s ", currentDir->ptSub[i]->name);
		}
		printf("\n");
	}	
}

void cd(Directory *currentDir, const char *directory )
{
	if(strcmp(directory, "..") == 0) //Parent directory. Regardless whether if ".." exists
	{
		currentDir = currentDir->parent;	
	}	
	else 
	{
		int exists = 0;
		int i;
		for(i = 0; i < currentDir->numberOfSubdirectories; i++)
		{
			if(strcmp(currentDir->ptSub[i]->name, directory) == 0)
			{
				currentDir = currentDir->ptSub[i]; //successfully changed directory
				exists = 1;
				break;
			}
		}
		if(!exists)
		{
			printf("cd: %s: No such file or directory\n", directory); 
		}
	} 	
}

Directory *createDirectory(const char *dirName, int time, int umask)
{
	Directory *directory = (Directory*)malloc(sizeof(Directory));
	directory->name = dirName;
	directory->time = time;
	//directory->permission = (Permissions)malloc(sizeof(Permissions)); 
	createPermissions(&(directory->permission), umask);
	directory->numberOfSubdirectories = 0;
			
	return directory;
}

void mkdir(Directory *currentDir, const char *name, int time, int umask)
{	
	if(currentDir->numberOfSubdirectories < MAX_SUBDIRECTORIES)	//checks if reached maximum #
	{
		int dupName = 0; //checks if there is already a directory with same name, below
		int i;
		int n = currentDir->numberOfSubdirectories; //so I don't need to keep tying this below
		for(i = 0; i < n; i++)
		{	
			if(strcmp(currentDir->ptSub[n-1]->name, name) == 0)
			{
				dupName = 1;
			}
		}
		if(!dupName)
		{
			Directory *dir = createDirectory(name, time, umask);
			dir->parent = currentDir;	//links with parent directory
			n = ++currentDir->numberOfSubdirectories;
			currentDir->ptSub[n-1] = dir;
		}
		else 
		{
			printf("mkdir: cannot create directory '%s': File exists\n", name);
		}
	}
	else 
	{
		printf("mkdir: / already contains the maximum number of directories\n");
	}									 
}
