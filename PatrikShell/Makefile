CC = gcc

INC = .
FLAGS = -Wall -std=gnu99 -Wformat-security
STATIC = -std=gnu99
OUTPUT = -o
RM = rm -f


# targety

all: patrikshell

patrikshell: patrikshell.o config.o history.o runner.o
	$(CC) patrikshell.o config.o history.o runner.o $(OUTPUT) patrikshell $(STATIC)

patrikshell.o: patrikshell.c config.h history.h runner.h
	$(CC) $(FLAGS) -I$(INC) -c patrikshell.c

config.o: config.c config.h
	$(CC) $(FLAGS) -I$(INC) -c config.c

history.o: history.c history.h
	$(CC) $(FLAGS) -I$(INC) -c history.c

runner.o: runner.c runner.h
	$(CC) $(FLAGS) -I$(INC) -c runner.c

clean:
	-@$(RM) patrikshell.o config.o history.o runner.o patrikshell

run:
	@echo "Spustam program"; \
	./patrikshell