#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>

#include "config.h"
#include "runner.h"
#include "history.h"

#define CONFIG_FILE "patrikshell.conf"

void _PatrikShellParseCommand(char *oldInputStr, char *newInputStr) {
    int i = 0;
    for (; oldInputStr[i] != '\n' &&
           oldInputStr[i] != '|' &&
           oldInputStr[i] != ';' &&
           oldInputStr[i] != '\0'; i++)
        newInputStr[i] = oldInputStr[i];
    newInputStr[i] = '\0';
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

    rsp = HistoryInit(ConfigGetHistoryFile());
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
        if ((strcmp("exit", formattedInput) == 0)) {
            printf("\nPráca s programom PatrikShell je ukončená\n");
            free(formattedInput);
            HistoryClose();
            closelog();
            return EXIT_SUCCESS;
        } else if ((strcmp("config", formattedInput) == 0)) {
            rsp = ConfigPrint();
        } else if ((strcmp("history", formattedInput) == 0)) {
            rsp = HistoryPrint();
        } else if ((strcmp("", formattedInput) == 0)) {
            free(formattedInput);
            continue;
        } else {
            // spustenie prikazu cez runner s timeoutom
            rsp = RunnerRun(formattedInput, ConfigGetExecutionTimeout());
        }
        if (rsp != EXIT_SUCCESS) {
            printf("Process ended with error code %d\n", rsp);
        }

        // vypraznit pamäť
        free(formattedInput);
    }

    HistoryClose();
    closelog();

    return EXIT_FAILURE;
}