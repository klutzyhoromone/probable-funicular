RAYLIB ?= ../external/raylib/src/

GLAD ?= ../external/
all:
	gcc main.c -DPLATFORM_DESKTOP -g -I. -I $(RAYLIB)  -L $(RAYLIB) -I $(GLAD) -L $(GLAD)  \
	    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
clean:
	rm a.out
