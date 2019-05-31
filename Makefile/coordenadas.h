#ifndef COORDENADAS_H_INCLUDED
#define COORDENADAS_H_INCLUDED
#include <glm.h>
typedef struct{
	double x;
	double y;
	double z;
}COORD;

typedef struct{
	COORD posicao;
	COORD velocidade;
	GLMmodel *model;
	int estado;
	
}OBJETO;


#endif
