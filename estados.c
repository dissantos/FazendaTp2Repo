#include "estados.h"

void mover(OBJETO *obj){
    obj->posicao.x += obj->velocidade.x;
    obj->posicao.z += obj->velocidade.z;
    if(obj->posicao.x >= 60|| obj->posicao.x <= -60)
        obj->velocidade.x *= -1;
    if(obj->posicao.z >= 60 || obj->posicao.z <= -60)
        obj->velocidade.z *= -1;
        
    

}
