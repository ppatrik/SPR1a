#ifndef PATRIKSHELL_HISTORY_H
#define PATRIKSHELL_HISTORY_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <unistd.h>
#include <sys/mman.h>
#include <syslog.h>

#include "runner.h"
#include "config.h"

typedef struct h {
    char command[MAX_CMD_LEN];
} HistoryItem;

int HistoryInit(char *file);

int HistoryClose();

int HistoryPrint();

int HistoryGet(uint32_t history_item_id, char *prikaz);

void HistoryWrite(char *cmd);

#endif //PATRIKSHELL_HISTORY_H
