.PHONY: all clean
FLAGS=-Wall -Wextra -std=c23 -g
INCLUDE=-I C:\raylib\w64devkit\include
RAYLIB=-L C:\raylib\w64devkit\lib
LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm -lm
all: double_pendulum

double_pendulum: double_pendulum.c
	gcc $(FLAGS) double_pendulum.c -o double_pendulum $(INCLUDE) $(RAYLIB) $(LIBS)

clean:
	del double_pendulum.exe