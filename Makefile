# Project: FleshChasmerOne

CPP = g++
SRC = $(wildcard ./*.c)
OBJS = $(subst ./,build/,$(SRC))
OBJ = $(OBJS:.c=.o)


LIBS = -lSDL_mixer -lSDLmain -lSDL
INCS =  -I"/usr/include/SDL" -I"./" 
BIN  = FleshChasmer
FLAGS = $(INCS) -DPC -fpermissive -fexpensive-optimizations -O3 -Wall -g
RM = rm -f
MKDIR = mkdir -p

.PHONY: clean

all: all-before FleshChasmer

all-before:
	$(MKDIR) "build"

clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) -o $@ $^ $(LIBS)

build/%.o : ./%.c
	$(CPP) -c $< -o $@ $(FLAGS)

