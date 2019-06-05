#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H
#include "coordenadas.h"
#include "glm.h"

OBJETO *galinha;
OBJETO cerca[4];
OBJETO estabulo;
OBJETO *porco;
OBJETO *arvore;
OBJETO triforce;

int qtdDeGalinhas;
int qtdDeArvores;
int qtdDePorco;
int qtdDeArvores;

GLMmodel* modelEstabulo;
GLMmodel* modelCerca;

int luzEstaLigada;
int linhasRelevo;
int anguloDeRotacao;
double respiracao;
double incrementoRespiracao;
GLfloat incrementoDeLuz;
double pontos[100][100];
int idTexturaGrama;
int idTexturaTerra;
int fogAtivo;

#endif
