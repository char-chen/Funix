#include <stdio.h>
#include <string.h>
#include "permissions.h"

void createPermissions(Permissions *perm, int umask)
{
	perm->value = umask;
}

void printPermissions(Permissions *perm)
{
	int n = perm->value;
	if(n == 0) 
	{
		printf("rwx"); 
	}
	else if(n == 1) 
	{	
		printf("rw-");
	}
	else if(n == 2) 
	{
		printf("r-w");
	}
	else if(n == 3) 
	{
		printf("r--");
	}
	else if(n == 4)
	{
		printf("-wx");
	}
	else if(n == 5)
	{
		printf("-w-");
	}
	else if(n == 6)
	{
		printf("--w");
	}
	else if(n == 7)
	{
		printf("---");
	}
	else
	{ 
		printf("error");
	}
}
