#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>

#include "config.h"
#include "runner.h"
#include "history.h"

#define CONFIG_FILE "/home/boss/Plocha/systemko/PatrikShell/patrikshell.conf"

void _PatrikShellParseCommand(char *oldInputStr, char *newInputStr) {
    int i = 0;
    for (; oldInputStr[i] != '\n' &&
           oldInputStr[i] != '|' &&
           oldInputStr[i] != ';' &&
           oldInputStr[i] != '\0'; i++)
        newInputStr[i] = oldInputStr[i];
    newInputStr[i] = '\0';
}

char *_PatrikShellConcat(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main() {
    openlog(NULL, LOG_PID, LOG_USER);

    char *formattedInput = NULL;
    char *userInput = NULL;

    if ((userInput = malloc(sizeof(char) * MAX_CMD_LEN)) == NULL) {
        fprintf(stderr, "Failed malloc\n");
        return EXIT_FAILURE;
    }

    printf("Vitajte v programe PatrikShell\n");

    // inicializacie
    int rsp;
    rsp = ConfigInit(CONFIG_FILE);
    if (rsp < 0) {
        return rsp;
    }

    char *historyFile = ConfigGetHistoryFile();
    if (ConfigGetHistoryFileRelative() == 1) {
        char historyFileCwd[MAX_CMD_LEN] = "";
        getcwd(historyFileCwd, sizeof(historyFileCwd));
        size_t len = strlen(historyFileCwd);
        if (historyFileCwd[len - 1] != '/') {
            historyFileCwd[len] = '/';
            historyFileCwd[len + 1] = '\0';
        }
        historyFile = _PatrikShellConcat(historyFileCwd, historyFile);
    }
    rsp = HistoryInit(historyFile);
    if (rsp < 0) {
        return rsp;
    }

    // beh programu
    while (true) {
        printf("Váš príkaz > ");

        // nacitanie vstupu
        if (fgets(userInput, MAX_CMD_LEN, stdin) == NULL) {
            printf("Pressed [Ctrl+D]\n");
            return EXIT_SUCCESS;
        }

        // parsovanie vstupu
        if ((formattedInput = malloc(sizeof(userInput) * 10)) == NULL)
            printf("Failed malloc.\n");
        _PatrikShellParseCommand(userInput, formattedInput);

        // vyvolanie prikazu z historie
        if ((strncmp("!", formattedInput, 1) == 0)) {
            // extrahovanie cisla
            uint32_t val;
            char ch;
            sscanf(formattedInput, "%c%d\n", &ch, &val);
            // ziskanie z historie
            rsp = HistoryGet(val, formattedInput);
            if (rsp != EXIT_SUCCESS) {
                printf("Prikaz nebol najdeny\n");
                continue;
            }
        } else {
            HistoryWrite(formattedInput);
        }

        // Kontrola na buildin prikazy
        if ((strncmp("exit", formattedInput, 4) == 0)) {
            printf("\nPráca s programom PatrikShell je ukončená\n");
            free(formattedInput);
            HistoryClose();
            closelog();
            return EXIT_SUCCESS;

        } else if ((strncmp("config", formattedInput, 6) == 0)) {
            rsp = ConfigPrint();

        } else if ((strncmp("history", formattedInput, 7) == 0)) {
            rsp = HistoryPrint();

        } else if ((strncmp("setenv", formattedInput, 6) == 0)) {
            char program[MAX_CMD_LEN] = "";
            char env[MAX_CMD_LEN] = "";
            char value[MAX_CMD_LEN] = "";
            sscanf(formattedInput, "%s %s %s\n", program, env, value);
            printf("nastavenie premennej prostredia þ%sþ\n", env);
            rsp = setenv(env, value, 1);

        } else if ((strncmp("getenv", formattedInput, 6) == 0)) {
            char program[MAX_CMD_LEN] = "";
            char env[MAX_CMD_LEN] = "";
            sscanf(formattedInput, "%s %s\n", program, env);
            char *value = getenv(env);
            printf("citanie premennej prostredia\n");
            printf("%s = %s\n", env, value);

        } else if ((strncmp("chndir", formattedInput, 6) == 0)) {
            char program[MAX_CMD_LEN] = "";
            char dir[MAX_CMD_LEN] = "";
            sscanf(formattedInput, "%s %s\n", program, dir);
            printf("Change working dir to %s\n", dir);
            rsp = chdir(_PatrikShellConcat(dir, "\0"));

        } else if ((strncmp("getdir", formattedInput, 6) == 0)) {
            char cwd[MAX_CMD_LEN] = "";
            char *wd = getcwd(cwd, sizeof(cwd));
            if (wd != NULL)
                printf("Current working dir: %s\n", cwd);
            else
                perror("getcwd() error");

        } else if ((strncmp("help", formattedInput, 4) == 0)) {
            printf("Dostupne prikazy: config, history, setenv, getenv, chndir, getdir, help\n");
            printf("Vyvolanie prikazu z historie !XYZ\n");

        } else if ((strcmp("", formattedInput) == 0)) {
            free(formattedInput);
            continue;

        } else {
            // spustenie prikazu cez runner s timeoutom
            rsp = RunnerRun(formattedInput, ConfigGetExecutionTimeout());
        }
        if (rsp != EXIT_SUCCESS) {
            syslog(LOG_ERR, "Process ended with error code %d errno %d [%s]\n", rsp, errno, formattedInput);
            printf("Process ended with error code %d\n", rsp);
        }

        // vypraznit pamäť
        free(formattedInput);
    }

    HistoryClose();
    closelog();

    return EXIT_FAILURE;
}