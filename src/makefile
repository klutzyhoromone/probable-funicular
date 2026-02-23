RAYLIB ?= ../external/raylib/src/

RAYGUI ?= ../external/

all:
	gcc main.c -g -I. -I $(RAYLIB)  -L $(RAYLIB) -I $(RAYGUI) -L $(RAYGUI)  \
	    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
