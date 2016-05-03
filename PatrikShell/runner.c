#include "runner.h"

void _RunnerParseInput(char *userInputStr, char **cmdWithArgs) {
    unsigned int i;
    unsigned int arg = 0;
    unsigned int string_start = 0;
    unsigned int cur_string_len = 0;
    unsigned int last_was_space = 1;

    for (i = 0; i <= strlen(userInputStr); i++) {
        if ((userInputStr[i] == ' ') || (userInputStr[i] == '\0')) {
            if (!last_was_space) {
                cmdWithArgs[arg] = strndup(&userInputStr[string_start], cur_string_len);
                if (cmdWithArgs[arg] == NULL) {
                    syslog(LOG_ERR, "Failed malloc _RunnerParseInput:cmdWithArgs!\n");
                }

                arg += 1;
                cur_string_len = 0;
                string_start = i + 1;
            } else { /* multiple spaces in a row */
                string_start += 1;
            }
            last_was_space = 1;
        } else {
            last_was_space = 0;
            cur_string_len += 1;
        }
    }
}

void _RunnerKill(pid_t pidToKill, int *status) {
    kill(pidToKill, SIGTERM);

    bool died = false;
    int loop = 0;
    for (; !died && loop < 5; loop++) {
        sleep(1);
        if (waitpid(pidToKill, status, WNOHANG) == pidToKill) {
            died = true;
        }
    }

    if (!died) {
        kill(pidToKill, SIGKILL);
        *status = 1;
    }

}

int RunnerRun(char *formattedInput, uint32_t timeout) {
    syslog(LOG_INFO, "Started %s", formattedInput);
    int i;
    size_t cmdargv_len;

    char **cmdargv = NULL;

    cmdargv_len = sizeof(char *) * MAX_CMD_ARGS;
    if ((cmdargv = (char **) malloc(cmdargv_len)) == NULL) {
        syslog(LOG_ERR, "Failed malloc RunnerRun:cmdargv\n");
    } else {
        memset(cmdargv, '\0', sizeof(char *) * MAX_CMD_ARGS);
    }

    // rozparsovanie stringu na parametre
    _RunnerParseInput(formattedInput, cmdargv);

    pid_t c_pid, pid;
    int status = EXIT_FAILURE;
    time_t start = time(NULL);

    c_pid = fork();

    if (c_pid == 0) {
        /* CHILD */

        // execute command
        execvp(cmdargv[0], cmdargv);

        //only get here if exec failed
        syslog(LOG_ERR, "Failed RunnerRun:execvp");
        kill(getpid(), SIGKILL);
        return EXIT_FAILURE;
    } else if (c_pid > 0) {
        /* PARENT */

        time_t waittime = 0;
        do {
            pid = waitpid(c_pid, &status, WNOHANG);
            if (pid == 0) {
                time_t now = time(NULL);
                waittime = now - start;
                if (waittime > timeout) {
                    _RunnerKill(c_pid, &status);
                    break;
                }
            }
        } while (pid == 0 && waittime <= timeout);

        if (WIFSIGNALED(status)) {
            syslog(LOG_ALERT, "Child %d was terminated with a status of: %d \n", c_pid, WTERMSIG(status));
            printf("Child %d was terminated with a status of: %d \n", c_pid, WTERMSIG(status));
        }

        printf("Child was running %d seconds\n", (int) waittime);
    } else {
        syslog(LOG_ERR, "Failed RunnerRun:fork");
        return ERROR_RUNNER_FORK_FAILED;
    }

    // Free list of command strings
    if (cmdargv) {
        for (i = 0; i < MAX_CMD_ARGS; i++) {
            free(cmdargv[i]);
        }
    }
    free(cmdargv);

    return status;
}