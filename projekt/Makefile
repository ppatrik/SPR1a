CC = gcc

INC = .
FLAGS = -Wall
STATIC =
OUTPUT = -o
RM = rm -f


# targety

all: project

project: project.o person.o basic.o
	$(CC) project.o person.o basic.o $(OUTPUT) project $(STATIC)

project.o: project.c person.h basic.h
	$(CC) $(FLAGS) -I$(INC) -c project.c

person.o: person.c person.h
	$(CC) $(FLAGS) -I$(INC) -c person.c

basic.o: basic.c basic.h
	$(CC) $(FLAGS) -I$(INC) -c basic.c

clean:
	-@$(RM) project.o person.o basic.o project

run:
	@echo "Spustam program"; \
	./project
