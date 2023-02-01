COMPILER = gcc
FLAGS = -Wall --std=c99
OUTPUT = Enigma
OBJS = PlugBoard.o Rotor.o Enigma.o

all : main.c $(OBJS)
	$(COMPILER) $(FLAGS) $^ -o $(OUTPUT).exe

Enigma.o : Enigma.h Enigma.c
	$(COMPILER) $(FLAGS) $^ -c

PlugBoard.o : PlugBoard.h PlugBoard.c
	$(COMPILER) $(FLAGS) $^ -c

Rotor.o : Rotor.h Rotor.c
	$(COMPILER) $(FLAGS) $^ -c

clean :
	rm -rf Enigma.exe *.o *.gch
