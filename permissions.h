#ifndef PERMISSION_H
	#define PERMISSION_H

typedef struct
{
  short value;
} Permissions; 


void createPermissions(Permissions *permission, int umask);

void printPermissions(Permissions *permission);
#endif
