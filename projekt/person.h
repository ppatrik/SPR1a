#ifndef __PERSON_H__
#define __PERSON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "basic.h"

#define SHELL_LENGTH 200
#define HOME_LENGHT 200
#define NAME_LENGTH 50
#define LOGIN_LENGTH 50
#define PASSWD_LENGTH 50
#define PERSON_LENGTH 558 /* suma dlzok plus 2 inty(po 4 bajty) */
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
	//account active;
} person;

void addPerson(void);
void displayPersons(void);

void openDB();
void updateDB();
void closeDB();

#endif /* __PERSON_H__ */
