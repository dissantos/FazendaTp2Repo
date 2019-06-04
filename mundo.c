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

