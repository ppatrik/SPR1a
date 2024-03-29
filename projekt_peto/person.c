//
// Created by boss on 18.3.2016.
//

#include "person.h"

person *users = NULL;
int user_cnt = 0;
int db_fd = -1;

int getUserCnt() {
    return user_cnt;
}

void addPerson() {
    if (user_cnt) closeDB();
    char buf[sizeof(person)];
    memset(buf, 0, sizeof(person));

    FILE *fs = fopen(DB_FILE, "a");
    if (fs == NULL) werror("Nemozem otvorit subor.\n\n", -1);
    fwrite(&buf, sizeof(person), 1, fs);
    fclose(fs);
    openDB();

    char txt[MAX_ID_LEN];
    printf("Zadaj ID:    ");
    fgets(txt, MAX_ID_LEN, stdin);
    users[user_cnt - 1].id = (uint32_t) atoi(txt);
    printf("Zadaj meno:  ");
    fgets(users[user_cnt - 1].name, NAME_LENGTH, stdin);
    strim(users[user_cnt - 1].name);
    printf("Zadaj login: ");
    fgets(users[user_cnt - 1].login, LOGIN_LENGTH, stdin);
    strim(users[user_cnt - 1].login);
    printf("Zadaj heslo: ");
    fgets(users[user_cnt - 1].password, PASSWORD_LENGTH, stdin);
    strim(users[user_cnt - 1].password);
    printf("Zadaj shell: ");
    fgets(users[user_cnt - 1].shell, SHELL_LENGTH, stdin);
    strim(users[user_cnt - 1].shell);
    printf("Zadaj home:  ");
    fgets(users[user_cnt - 1].home, HOME_LENGTH, stdin);
    strim(users[user_cnt - 1].home);
    printf("Pouzivatel pridany. Velkost struktury: %lu. \n\n", (long) sizeof(person));
    updateDB();
}

int openDB(void) {
    struct stat finfo;
    db_fd = open(DB_FILE, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (db_fd < 0) {
        perror("Subor nie je mozne otvorit!");
        return 0;
    }
    fstat(db_fd, &finfo);
    if (finfo.st_size > 0) {
        int u_cnt = (int) finfo.st_size / sizeof(person);
        users = (person *) mmap(NULL, sizeof(person) * u_cnt, PROT_READ | PROT_WRITE, MAP_SHARED, db_fd, (off_t) 0);
        if (errno != 0) {
            perror("Nie je mozne mapovat!");
            close(db_fd);
            db_fd = -1;
            return 0;
        }
        user_cnt = u_cnt;
        return user_cnt;
    } else {
        close(db_fd);
        db_fd = -1;
    }
    return 0;
}

void closeDB() {
    updateDB();
    munmap(users, sizeof(person) * user_cnt);
    close(db_fd);
}

void updateDB() {
    msync(users, sizeof(person) * user_cnt, MS_SYNC);
}

void displayPerson() {
    if (user_cnt == 0) openDB();
    char volba[5];
    printf("Zobrazenie pouzivatela: ");
    fgets(volba, 5, stdin);
    int por = atoi(volba);
    if ((por) && (por <= user_cnt)) {
        printf("---------------------------------------\n");
        printf("ID:\t%d\nMeno:\t%s\nLogin:\t%s\nHeslo:\t%s\nShell:\t%s\nDomov:\t%s\n\n",
               users[por - 1].id, users[por - 1].name, users[por - 1].login, users[por - 1].password,
               users[por - 1].shell, users[por - 1].home);
    } else {
        printf("Osoba neexistuje!\n\n");
    }
}

void listPersons() {
    printf("Vypis osob v DB:\n");
    printf("---------------------------------------\n");
    if (user_cnt == 0) openDB();
    for (int i = 0; i < user_cnt; i++) {
        printf("Pouzivatel c. %d: %d:%s:%s:%s:%s:%s \n", (i + 1), users[i].id, users[i].name, users[i].login,
               users[i].password, users[i].shell, users[i].home);
    }
    printf("\n");
}

void editPerson() {
    if (user_cnt == 0) openDB();
    char volba[MAX_INPUT];
    printf("Uprava pouzivatela: ");
    fgets(volba, MAX_INPUT, stdin);
    int por = atoi(volba);
    if ((por) && (por <= user_cnt)) {
        char tmp[MAX_STR_LEN];
        printf("Zadaj meno: [%s] ", users[por - 1].name);
        fgets(tmp, NAME_LENGTH, stdin);
        strim(tmp);
        if (strlen(tmp)) strncpy(users[por - 1].name, tmp, NAME_LENGTH);
        printf("Zadaj login: [%s] ", users[por - 1].login);
        fgets(tmp, LOGIN_LENGTH, stdin);
        strim(tmp);
        if (strlen(tmp)) strncpy(users[por - 1].login, tmp, LOGIN_LENGTH);
        printf("Zadaj heslo: [%s] ", users[por - 1].password);
        fgets(tmp, PASSWORD_LENGTH, stdin);
        strim(tmp);
        if (strlen(tmp)) strncpy(users[por - 1].password, tmp, PASSWORD_LENGTH);
        printf("Zadaj shell: [%s] ", users[por - 1].shell);
        fgets(tmp, SHELL_LENGTH, stdin);
        strim(tmp);
        if (strlen(tmp)) strncpy(users[por - 1].shell, tmp, SHELL_LENGTH);
        printf("Zadaj home: [%s] ", users[por - 1].home);
        fgets(tmp, HOME_LENGTH, stdin);
        strim(tmp);
        if (strlen(tmp)) strncpy(users[por - 1].home, tmp, HOME_LENGTH);
        updateDB();
        printf("Pouzivatel upraveny.\n\n");
    } else {
        printf("Osoba neexistuje!\n\n");
    }
}

void removePerson() {
    if (user_cnt == 0) openDB();
    char volba[MAX_INPUT];
    printf("Odstranenie pouzivatela: ");
    fgets(volba, MAX_INPUT, stdin);
    int por = atoi(volba);
    if ((por) && (por <= user_cnt)) {
        if (por == user_cnt) {
            closeDB();
            truncate(DB_FILE, sizeof(person) * (por - 1));
        } else {
            memcpy(&users[por - 1], &users[user_cnt - 1], sizeof(person));
            closeDB();
            truncate(DB_FILE, sizeof(person) * (user_cnt - 1));
        }
        printf("Pouzivatel odstraneny.\n\n");
        openDB();
    } else {
        printf("Osoba neexistuje!\n\n");
    }
}
