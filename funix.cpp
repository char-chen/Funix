#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funix.h"

void run(Funix *funix) 
{
	init(funix);
  int execute = 1;
	while(execute)
	{
		char *command = (char*)malloc(sizeof(char)*COMMAND_LENGTH+1);
		getCommand(funix, command);
		execute = processCommand(funix, command);
	}
}//runs Funix until the user exits

void init(Funix *funix)
{
	funix->time = 0;
	funix->umask = 0;
	funix->currentDirectory = createDirectory("", 0, 0);
		
}//creates root directory

void getCommand(Funix *funix, char *command)
{	
	writePrompt(funix);
	command = fgets(command, COMMAND_LENGTH, stdin);
}
//gets the input and feeds the command to processCommand()

int processCommand(Funix *funix, char *command) 
{
	const char *commandArgs[MAX_ARGUMENTS];	//a pointer to an array of strings/tokens
	char *p;	//for redirecting the token pointer in the following for-loop
	int argCounter = 0;
	
	//Before tokenizing, we need to get rid of the newline characters not discarded by strtok
	command[strlen(command)-1] = 0;
	for(p=strtok(command," "); p != NULL; p=strtok(NULL, " "))	//tokenizing
	{
		commandArgs[argCounter] = p;
		argCounter++;
	}
	//Checks whether commands entered by user are legal
	//Executes commands if possible  
	if(commandArgs[0] != NULL)
	{
		if(strcmp(commandArgs[0], "exit") == 0)
		{
			return eXit(funix, argCounter, commandArgs);
		}
		else if(strcmp(commandArgs[0], "cd") == 0)
		{
			cd(funix, argCounter, commandArgs);
			return 1;		
		}
		else if(strcmp(commandArgs[0], "ls") == 0)
		{
			ls(funix, argCounter, commandArgs);
			return 1;
		}
		else if(strcmp(commandArgs[0], "mkdir") == 0)
		{
			mkdir(funix, argCounter, commandArgs);
			return 1;
		}
		else if(strcmp(commandArgs[0], "umask") == 0)
		{
			umask(funix, argCounter, commandArgs);
			return 1;
		}
		else if (strcmp(commandArgs[0], "\0") == 0)
		{
			return 1;
		}
		else 
		{
			printf("%s: Command not found.\n", command);
			return 1; 
		}    
	}
	else //commandArgs[0] be NULL ? 
	{
		return 1;
	}
}

void writePrompt(Funix *funix)
{
	//const char *result = funix->currentDirectory->name;
	//printf("%s # ", showPath(funix->currentDirectory, result));	
	printf("/ # ");
}

int eXit(Funix *funix, int argCount, const char *arguments[])
{
	if(argCount == 1) 
	{
		return 0;
	}
	else 
	{
		printf("usage: exit\n");
		funix->time++;
		return 1;
	}			
}

void cd(Funix *funix, int argCount, const char *arguments[])
{
	funix->time++;
	if((argCount == 1) || (argCount > 2))
	{
		printf("usage: cd directoryName\n");
	}
	else	//should have only 2 arguments at this point
	{
		cd(funix->currentDirectory, arguments[1]);		
	}	
}

void ls(Funix *funix, int argCount, const char *arguments[])
{
	funix->time++;
	if(argCount > 2)
	{
		printf("usage: ls [-l]\n");
	}
	else if(argCount == 2)
	{
		if(strcmp(arguments[1], "-l") == 0)
		{
			ls(funix->currentDirectory, 1); 
		}
		else 
			printf("usage: ls [-l]\n");
	}
	else	//only one argument, ls
	{
		ls(funix->currentDirectory, 0);
	}  
}

void mkdir(Funix *funix, int argCount, const char *arguments[])
{
	funix->time++;
	if((argCount == 1) || (argCount > 2))
	{
		printf("usage: mkdir directory_name\n");
	}
	else //only 2 arguments, accepted 
	{
		mkdir(funix->currentDirectory, arguments[1], funix->time, funix->umask);
	}
}

void umask(Funix *funix, int argCount, const char *arguments[])
{
	funix->time++;
	if((argCount == 1) || (argCount > 2))
	{
		printf("usage: umask octal\n");
	}
	else //only 2 arguments, accepted
	{
		if(strlen(arguments[1]) == 1) //Make sure that arguments[1] is between 0 and 7
		{
			if(strcmp(arguments[1], "0") == 0)
			{
				funix->umask = 0;
			}
			else
			{
				int octal = atoi(arguments[1]); 
				if(octal < 8 && octal > 0 )
				{
					funix->umask = octal;
				}
				else 
				{
					printf("umask: octal must be between 0 and 7\n");
				}
			}
		}
		else //atoi only looks at the first character of a string. Hence 1.5 will still be 1.
		{
			printf("umask: octal must be between 0 and 7\n");
		}
	}
}	
