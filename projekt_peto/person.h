//
// Created by boss on 18.3.2016.
//

#ifndef PROJECT_PERSON_H
#define PROJECT_PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <unistd.h>
#include <sys/mman.h>

#include "basic.h"

#define DB_FILE     "shell.db"
#define MAX_INPUT     4
#define MAX_ID_LEN   10
#define MAX_STR_LEN 200

#define NAME_LENGTH     50
#define SHELL_LENGTH   200
#define HOME_LENGTH    200
#define LOGIN_LENGTH    50
#define PASSWORD_LENGTH 50

typedef struct p {
    uint32_t id;
    char name[NAME_LENGTH];
    char login[LOGIN_LENGTH];
    char password[PASSWORD_LENGTH];
    char shell[SHELL_LENGTH];
    char home[HOME_LENGTH];
} person;

/* person management */

void addPerson();

void displayPerson();

void listPersons();

void removePerson();

void editPerson();

int getUserCnt();

/* database */

int openDB();

void closeDB();

void updateDB();

#endif //PROJECT_PERSON_H
