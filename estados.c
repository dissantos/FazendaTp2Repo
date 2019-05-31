#include "estados.h"

void mover(OBJETO *obj){
    obj->posicao.x += obj->velocidade.x;
    obj->posicao.z += obj->velocidade.z;
    obj->posicao.y += obj->velocidade.y;
    if(obj->posicao.x >= 58|| obj->posicao.x <= -58)
        obj->velocidade.x *= -1;
    if(obj->posicao.z >= 58 || obj->posicao.z <= -58)
        obj->velocidade.z *= -1;
		if(obj->posicao.y >= -185 || obj->posicao.y <=  -190)
			obj->velocidade.y *= -1;

}
