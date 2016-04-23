#ifndef PATRIKSHELL_RUNNER_H
#define PATRIKSHELL_RUNNER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <syslog.h>

#include "errors.h"

#define MAX_CMD_LEN 1000
#define MAX_CMD_ARGS 100

int RunnerRun(char *command, uint32_t timeout);

#endif //PATRIKSHELL_RUNNER_H
