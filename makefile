#Makefile Génerique Flappy
SFML_DIR	= SFML-2.5.1
LIBDIR	= $(SFML_DIR)/lib
CFLAGS	= $(SFML_DIR)/include
LIBS	= -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
OBJS	= main.o fonction.o
OUT	= flappy
CC	 = g++
FLAGS	 = -O3 -c -I$(CFLAGS) -std=c++17 -Wall
HEADER	=	*.hpp *.h
DOLLAR	= \$$
all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -L$(LIBDIR) $(LIBS)

main.o: main.cpp $(HEADER)
	$(CC) $(FLAGS) main.cpp

fonction.o: fonction.cpp $(HEADER)
	$(CC) $(FLAGS) fonction.cpp

nolib: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -L$(LIBDIR) $(LIBS)
	rm -f flappyNoLib.sh
	@echo "#!/bin/bash" >> flappyNoLib.sh
	@echo "EXE=flappy" >> flappyNoLib.sh
	@echo "SFML_DIR=SFML-2.5.1" >> flappyNoLib.sh
	@echo "LIBDIR=$(DOLLAR)SFML_DIR/lib" >> flappyNoLib.sh
	@echo "if [[ $(DOLLAR)LD_LIBRARY_PATH = $(DOLLAR)LIBDIR ]]" >> flappyNoLib.sh
	@echo "then" >> flappyNoLib.sh
	@echo "	./$(DOLLAR)EXE" >> flappyNoLib.sh
	@echo "else" >> flappyNoLib.sh
	@echo 	"export LD_LIBRARY_PATH=$(DOLLAR)LIBDIR && ./$(DOLLAR)EXE $1" >> flappyNoLib.sh
	@echo "fi" >> flappyNoLib.sh
	chmod +x flappyNoLib.sh

clean:
	rm -f flappyNoLib.sh
	rm $(OBJS) $(OUT)
