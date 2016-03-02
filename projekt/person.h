#ifndef __PERSON_H__
#define __PERSON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic.h"

#define SHELL_LENGTH 200
#define HOME_LENGHT 200
#define NAME_LENGTH 50
#define LOGIN_LENGTH 50
#define PASSWD_LENGTH 50
#define SHELL_FILE "etc/users.bin"

typedef enum a {inactive, active} account;

typedef struct p {
	int uid;
	int gid;
	char name[NAME_LENGTH];
    char login[LOGIN_LENGTH];
    char password[PASSWD_LENGTH];
	char home[HOME_LENGHT];
    char shell[SHELL_LENGTH];
	account active;
} person;

void addPerson(void);

#endif /* __PERSON_H__ */
