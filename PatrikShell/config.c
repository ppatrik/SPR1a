#include "config.h"

// region Private

uint32_t _ConfigReadInteger(char *config_line) {
    char prm_name[MAX_CONFIG_VARIABLE_LEN];
    uint32_t val;
    sscanf(config_line, "%s %d\n", prm_name, &val);
    return val;
}

void _ConfigReadString(char *config_line, char *val) {
    char prm_name[MAX_CONFIG_VARIABLE_LEN];
    sscanf(config_line, "%s %s\n", prm_name, val);
}

// endregion

// region Public

int ConfigInit(char *file) {
    FILE *fp;
    char buf[CONFIG_LINE_BUFFER_SIZE];

    if ((fp = fopen(file, "r")) == NULL) {
        syslog(LOG_ERR, "Nepodarilo sa otvorit konfiguračný súbor %s", file);
        return ERROR_CONFIG_FILE_CANT_READ;
    }
    while (!feof(fp)) {
        fgets(buf, CONFIG_LINE_BUFFER_SIZE, fp);
        if (buf[0] == '#' || strlen(buf) < 4) {
            continue;
        }
        if (strstr(buf, "EXECUTION_TIMEOUT ")) {
            config.execution_timeout = _ConfigReadInteger(buf);
        }
        if (strstr(buf, "HISTORY_FILE ")) {
            _ConfigReadString(buf, config.history_file);
        }
    }
    fclose(fp);
    if (config.execution_timeout > 0 && strlen(config.history_file) > 0) {
        return EXIT_SUCCESS;
    } else {
        syslog(LOG_ERR, "Konfiguračný súbor neobsahuje povinné parametre %s", file);
        return ERROR_CONFIG_FILE_MISSING_PARAMS;
    }
}

int ConfigPrint() {
    printf("Readed config file:\n");
    printf("EXECUTION_TIMEOUT = %d\n", ConfigGetExecutionTimeout());
    printf("HISTORY_FILE = %s\n", ConfigGetHistoryFile());
    return EXIT_SUCCESS;
}

char *ConfigGetHistoryFile() {
    return config.history_file;
}

uint32_t ConfigGetExecutionTimeout() {
    return config.execution_timeout;
}

// endregion