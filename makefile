#Spellchecker Makefile
CC = g++
CFLAGS = -g -Wall

all:spellchecker

spellchecker:main.o SpellChecker.o
	$(CC) $(CFLAGS) -o spellchecker main.o SpellChecker.o

main.o:main.cpp SpellChecker.h
	$(CC) $(CFLAGS) -c main.cpp

SpellChecker.o:SpellChecker.cpp SpellChecker.h
	$(CC) $(CFLAGS) -c SpellChecker.cpp

clean:
	rm -f spellchecker *.o *.~ *.gch

