CC=gcc

CFLAGS=-Wall -Wextra -Werror -O0 -g -std=c11 -pthread
LDFLAGS=-lm

all: grade

aluno: tm.c aluno.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o aluno tm.c aluno.c

test: tm.c test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o test tm.c test.c 

grade: test
	./test

teste_aluno: aluno
	./aluno

clean:
	rm -rf *.o test aluno
