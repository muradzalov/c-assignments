CC = gcc
CFLAGS = -Wall -g

all: spell_checker

spell_checker: spell_checker.c hashset_pa4.c
	$(CC) $(CFLAGS) -o spell_checker spell_checker.c hashset_pa4.c -lm

clean:
	rm -f spell_checker
