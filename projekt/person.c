#include "person.h"

person *users = NULL;
int cnt_usr = 0;
int uni_fd = -1;

void addPerson() {
    person pp;

    char id[5];

    printf("Zadaj UID:");
    fgets(id, 5 - 1, stdin);
    pp.uid = atoi(id);

    printf("Zadaj GID:");
    fgets(id, 5 - 1, stdin);
    pp.gid = atoi(id);

    printf("Zadaj meno:");
    memset(pp.name, 0, NAME_LENGTH);
    fgets(pp.name, NAME_LENGTH - 1, stdin);

    printf("Zadaj login:");
    memset(pp.login, 0, LOGIN_LENGTH);
    fgets(pp.login, LOGIN_LENGTH - 1, stdin);

    printf("Zadaj heslo:");
    memset(pp.password, 0, PASSWD_LENGTH);
    fgets(pp.password, PASSWD_LENGTH - 1, stdin);

    printf("Zadaj domovský adresár:");
    memset(pp.home, 0, HOME_LENGHT);
    fgets(pp.home, HOME_LENGHT - 1, stdin);

    printf("Zadaj shell:");
    memset(pp.shell, 0, SHELL_LENGTH);
    fgets(pp.shell, SHELL_LENGTH - 1, stdin);

    FILE *fp = fopen(SHELL_FILE, "a");
    if (fp == NULL) werror("Chyba otvorenia súboru", -1);
    //fwrite(&pp, sizeof(person), 1, fp);
    fwrite(&pp.uid, sizeof(int), 1, fp);
    fwrite(&pp.gid, sizeof(int), 1, fp);
    fwrite(rtrim(pp.name), sizeof(char), NAME_LENGTH, fp);
    fwrite(rtrim(pp.login), sizeof(char), LOGIN_LENGTH, fp);
    fwrite(rtrim(pp.password), sizeof(char), PASSWD_LENGTH, fp);
    fwrite(rtrim(pp.home), sizeof(char), HOME_LENGHT, fp);
    fwrite(rtrim(pp.shell), sizeof(char), SHELL_LENGTH, fp);
    fclose(fp);

    vypis("Užívateľ bol pridaný!");
}

person parsePerson(const char *buffer) {
    person tmp;

    memcpy(&(tmp.uid), buffer, sizeof(int));
    buffer += sizeof(int);

    memcpy(&(tmp.gid), buffer, sizeof(int));
    buffer += sizeof(int);

    memcpy(&(tmp.name), buffer, NAME_LENGTH);
    buffer += NAME_LENGTH;

    memcpy(&(tmp.login), buffer, LOGIN_LENGTH);
    buffer += LOGIN_LENGTH;

    memcpy(&(tmp.password), buffer, PASSWD_LENGTH);
    buffer += PASSWD_LENGTH;

    memcpy(&(tmp.home), buffer, HOME_LENGHT);
    buffer += HOME_LENGHT;

    memcpy(&(tmp.shell), buffer, SHELL_LENGTH);
    //buffer += SHELL_LENGTH;

    return tmp;
}

void writePerson(person pp) {
    printf("-------------------------------\n");
    printf("| Osoba UID/GID: %d/%d\n", pp.uid, pp.gid);
    printf("| Meno:          %s\n", pp.name);
    printf("| Login:         %s\n", pp.login);
    printf("| Password:      %s\n", pp.password);
    printf("| Home:          %s\n", pp.home);
    printf("| Shell:         %s\n", pp.shell);
}

void displayPersons(void) {

    openDB();
    for (int i = 0; i < cnt_usr; i++) {
        writePerson(users[i]);
    }
    printf("-------------------------------\n");
}

void openDB() {
    uni_fd = open(SHELL_FILE, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (uni_fd < 0) {
        werror("Nepodarilo sa otvorit subor!", -1);
    }

    struct stat fileinfo;
    fstat(uni_fd, &fileinfo);
    int cusr = (int) fileinfo.st_size / (int) sizeof(person);

    if (fileinfo.st_size) { // ked nieje prazdny subor
        users = (person *) mmap(NULL, sizeof(person) * cusr, PROT_READ | PROT_WRITE, MAP_SHARED, uni_fd, 0);
        if (errno != 0) {
            close(uni_fd);
            werror("Nepodarilo sa namapovat!", -2);
        }
        cnt_usr = cusr;
        return;
    }
    close(uni_fd);
}

void updateDB() {
    msync((void *) users, sizeof(person) * cnt_usr, MS_SYNC);
}

void closeDB() {
    updateDB();
    munmap((void *) users, sizeof(person) * cnt_usr);
    close(uni_fd);
}