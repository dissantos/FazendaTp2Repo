#include "desenha.h"
#include "coordenadas.h"


void desenhaGalinhas(){
	glColor3f(0,0,1);
	for(int i = 0; i < qtdDeGalinhas; i++){
		glPushMatrix();
			glTranslatef(galinha[i].posicao.x,galinha[i].posicao.y,galinha[i].posicao.z);
			if(galinha[i].velocidade.x == 1 && galinha[i].velocidade.z == 1)
				glRotatef(45,0,1,0);
			if(galinha[i].velocidade.x == -1 && galinha[i].velocidade.z == 1)
				glRotatef(135,0,1,0);
			if(galinha[i].velocidade.x == -1 && galinha[i].velocidade.z == -1)
				glRotatef(225,0,1,0);
			if(galinha[i].velocidade.x == 1 && galinha[i].velocidade.z == -1)
				glRotatef(315,0,1,0);
			glRotatef(-90,1,0,0);
			glmDraw(modelTeste, GLM_TEXTURE);
		glPopMatrix();
	}
}

void desenhaSolo(){
	glPushMatrix();
		glTranslatef(0,-200,0);
			glColor3f(0,1,0);
			glBegin(GL_TRIANGLE_FAN);
				glVertex3f(-300,0,-300);
				glVertex3f(300,0,-300);
				glVertex3f(300,0,300);
				glVertex3f(-300,0,300);
			glEnd();
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
				glVertex3f(-70,0,-70);
				glVertex3f(70,0,-70);
				glVertex3f(70,0,70);
				glVertex3f(-70,0,70);
			glEnd();
	glPopMatrix();
}

void desenhaCena(){
	desenhaSolo();
	desenhaGalinhas();
}
