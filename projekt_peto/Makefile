CC = gcc

INC = .
FLAGS = -Wall -std=gnu99
STATIC = -std=gnu99
OUTPUT = -o
RM = rm -f


# targety

all: userman

userman: userman.o person.o basic.o
	$(CC) userman.o person.o basic.o $(OUTPUT) userman $(STATIC)

userman.o: userman.c person.h basic.h
	$(CC) $(FLAGS) -I$(INC) -c userman.c

person.o: person.c person.h
	$(CC) $(FLAGS) -I$(INC) -c person.c

basic.o: basic.c basic.h
	$(CC) $(FLAGS) -I$(INC) -c basic.c

clean:
	-@$(RM) userman.o person.o basic.o userman

run:
	@echo "Spustam program"; \
	./userman
