OBJS = main.cpp src/SabrinaEngine/graphics.cpp src/SabrinaEngine/sprites.cpp src/SabrinaEngine/sound.cpp src/SabrinaEngine/input.cpp src/SabrinaEngine/framerate.cpp src/SabrinaEngine/collision.cpp src/SabrinaEngine/entity.cpp src/SabrinaEngine/sabrinaEngine.cpp

CC = g++

COMPILER_FLAGS = -Wall -g

LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_mixer

INCLUDE = -I/src/sabrinaEngine

OBJ_NAME = SABRINA_ENGINE

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
