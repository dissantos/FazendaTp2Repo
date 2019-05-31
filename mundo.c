#include "mundo.h"

float calcularAltura(float numeroInicial, int numeroMinimoInicial,int numeroMaximoInicial,int numeroMinimoFinal,int numeroMaximoFinal){  
	float numeroFinal;
	numeroFinal = ((numeroInicial-numeroMinimoInicial)*(numeroMaximoFinal - numeroMinimoFinal)/(numeroMaximoInicial-numeroMinimoInicial)) + numeroMinimoFinal;
	return numeroFinal;
}

void gerarRelevo(){
	int x,z;
	for(x=0;x<100;x++){ //estou calculando a altura de cada ponto
		for(z=0;z<100;z++){
				pontos[x][z] = calcularAltura(perlin2d(x,z,0.3,9),0,1,-10,10);
		}
	}
}
