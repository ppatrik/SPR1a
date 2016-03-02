#include "person.h"

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
    fwrite(&pp, sizeof(person), 1, fp);
    /*fwrite(&pp.uid, sizeof(int), 1, fp);
    fwrite(&pp.gid, sizeof(int), 1, fp);
    fwrite(rtrim(pp.name), sizeof(char), NAME_LENGTH, fp);
    fwrite(rtrim(pp.login), sizeof(char), LOGIN_LENGTH, fp);
    fwrite(rtrim(pp.password), sizeof(char), PASSWD_LENGTH, fp);
    fwrite(rtrim(pp.login), sizeof(char), LOGIN_LENGTH, fp);
    fwrite(rtrim(pp.home), sizeof(char), HOME_LENGHT, fp);
    fwrite(rtrim(pp.shell), sizeof(char), SHELL_LENGTH, fp);*/
    fclose(fp);

    vypis("Užívateľ bol pridaný!");
}
