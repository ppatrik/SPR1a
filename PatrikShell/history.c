#include "history.h"

// region Private

HistoryItem *_HistoryCommands = NULL;
int _HistoryCommandsCnt = 0;
int _HistoryFd = -1;
char _HistoryFile[CONFIG_MAX_HISTORY_FILE_LENGTH];

int _HistoryOpenDB() {
    struct stat finfo;
    _HistoryFd = open(_HistoryFile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (_HistoryFd < 0) {
        syslog(LOG_ERR, "Subor %s nie je mozne otvorit!", _HistoryFile);
        return ERROR_HISTORY_OPEN_DB;
    }
    fstat(_HistoryFd, &finfo);
    if (finfo.st_size > 0) {
        int u_cnt = (int) finfo.st_size / sizeof(HistoryItem);
        _HistoryCommands = (HistoryItem *) mmap(NULL, sizeof(HistoryItem) * u_cnt, PROT_READ | PROT_WRITE, MAP_SHARED,
                                                _HistoryFd, (off_t) 0);
        if (errno != 0) {
            syslog(LOG_ERR, "Historiu nie je mozne mapovat!");
            close(_HistoryFd);
            _HistoryFd = -1;
            return ERROR_HISTORY_MAP_DB;
        }
        _HistoryCommandsCnt = u_cnt;
        return _HistoryCommandsCnt;
    } else {
        close(_HistoryFd);
        _HistoryFd = -1;
    }
    return EXIT_SUCCESS;
}

void _HistoryUpdateDB() {
    msync(_HistoryCommands, sizeof(HistoryItem) * _HistoryCommandsCnt, MS_SYNC);
    syslog(LOG_DEBUG, "History update db");
}

void _HistoryCloseDB() {
    _HistoryUpdateDB();
    munmap(_HistoryCommands, sizeof(HistoryItem) * _HistoryCommandsCnt);
    close(_HistoryFd);
}

// endregion

// region Public

int HistoryInit(char *file) {
    strcpy(_HistoryFile, file);
    _HistoryOpenDB();
    return EXIT_SUCCESS;
}

int HistoryClose() {
    _HistoryCloseDB();
    return EXIT_SUCCESS;
}

int HistoryPrint() {
    if (_HistoryCommandsCnt == 0) {
        _HistoryOpenDB();
    }
    printf("Výpis histórie príkazov:\n");
    printf("------------------------\n");
    int i = 0;
    for (; i < _HistoryCommandsCnt; i++) {
        printf("[%03d] %s\n", (i + 1), _HistoryCommands[i].command);
    }
    printf("------------------------\n");
    return EXIT_SUCCESS;
}

int HistoryGet(uint32_t history_item_id, char *prikaz) {
    if (_HistoryCommandsCnt == 0) {
        _HistoryOpenDB();
    }

    if ((history_item_id) && (history_item_id <= _HistoryCommandsCnt)) {
        strcpy(prikaz, _HistoryCommands[history_item_id - 1].command);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

void HistoryWrite(char *cmd) {
    if (_HistoryCommandsCnt) {
        _HistoryCloseDB();
    }
    char buf[sizeof(HistoryItem)];
    memset(buf, 0, sizeof(HistoryItem));

    FILE *fs = fopen(_HistoryFile, "a");
    if (fs == NULL) {
        syslog(LOG_ERR, "Nemozem otvorit subor %s.", _HistoryFile);
    }
    fwrite(&buf, sizeof(HistoryItem), 1, fs);
    fclose(fs);
    _HistoryOpenDB();
    strcpy(_HistoryCommands[_HistoryCommandsCnt - 1].command, cmd);
    _HistoryUpdateDB();
}

// endregion