#ifndef __PERSON_H__
#define __PERSON_H__

typedef enum s {MALE, FEMALE} gender;
typedef enum e {ELEMENTARY,HIGH,UNIVERSITY} education;

typedef struct p {
	char *name;
	char *surname;
	unsigned short age;
	gender sex;
	unsigned short weight;
	unsigned short height;
	education edu;
} person;

person *addPerson(void);

#endif /* __PERSON_H__ */
