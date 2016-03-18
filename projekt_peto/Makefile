CC = gcc

INC = .
FLAGS = -Wall -std=gnu99
STATIC = -std=gnu99
OUTPUT = -o
RM = rm -f


# targety

all: project

project: userman.o
	$(CC) userman.o $(OUTPUT) project $(STATIC)

userman.o: userman.c
	$(CC) $(FLAGS) -I$(INC) -c userman.c

clean:
	-@$(RM) userman.o project

run:
	@echo "Spustam program"; \
	./project
