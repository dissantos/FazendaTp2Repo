#include "mundo.h"
#include <stdlib.h>

float calcularAltura(float numeroInicial,int numeroMinimoFinal,int numeroMaximoFinal){  
	float numeroFinal;
	numeroFinal = numeroMinimoFinal + (numeroMaximoFinal - numeroMinimoFinal)*numeroInicial;
	return numeroFinal;
}

void gerarRelevo(){
	int numArvoresGeradas = 0;
	for(int x=0;x<100;x++){ //estou calculando a altura de cada ponto
		for(int z=0;z<100;z++){
				pontos[x][z] = calcularAltura(perlin2d(x,z,0.3,9),-10,10);
		}
	}
}

void gerarPosicoesDosAnimais(OBJETO *obj){
		obj->posicao.x = rand()%61;
		obj->velocidade.x = 1;
		if(rand()%2 == 0)
			obj->velocidade.x = -1;
		if(rand()%2 == 0)
			obj->posicao.x *= -1;
		obj->posicao.y = -190;
		obj->velocidade.y = 2;
		obj->posicao.z = rand()%61;
		obj->velocidade.z = 1;
		if(rand()%2 == 0)
			obj->velocidade.z = -1;
		if(rand()%2 == 0)
			obj->posicao.z *= -1;
		obj->estado = 1;
}
