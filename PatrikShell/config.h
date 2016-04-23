#ifndef PATRIKSHELL_CONFIG_H
#define PATRIKSHELL_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <syslog.h>

#include "errors.h"

#define MAX_CONFIG_VARIABLE_LEN 20
#define CONFIG_LINE_BUFFER_SIZE 100
#define CONFIG_MAX_HISTORY_FILE_LENGTH 256

struct {
    uint32_t execution_timeout;
    char history_file[CONFIG_MAX_HISTORY_FILE_LENGTH];
} config;

int ConfigInit(char *file);

int ConfigPrint();

char *ConfigGetHistoryFile();

uint32_t ConfigGetExecutionTimeout();

#endif //PATRIKSHELL_CONFIG_H
