CC=gcc
OPCOES_COMPILADOR=-I. -lSOIL -lglut -lGLU -lGLEW -lGL -lm -Wall `sdl-config --cflags --libs` -lSDL_mixer -w
TODOS_ARQUIVOS_PONTOH = coordenadas.h glm.h glmint.h image_DXT.h image_helper.h variaveisGlobais.h 
TODOS_ARQUIVOS_OBJ = main.o desenha.o estados.o variaveisGlobais.o glm.o glm_util.o glmimg.o image_DXT.o image_helper.o mundo.o perlin.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o main $^ $(OPCOES_COMPILADOR)

run: all
	./main

clean:
	rm *.o main
