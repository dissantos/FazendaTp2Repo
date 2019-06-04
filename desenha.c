#include "desenha.h"
#include "coordenadas.h"


void desenhaTriforce(){
	glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(triforce.posicao.x,triforce.posicao.y, triforce.posicao.z);
		glRotatef(90,1,0,1);
		glScaled(10,10,10);
			glmDraw(triforce.model,GL_NONE);
	glPopMatrix();
}

void desenhaGalinhas(){
	glColor3f(0,0,1);
	for(int i = 0; i < qtdDeGalinhas; i++){
		glPushMatrix();
			glTranslatef(galinha[i].posicao.x,galinha[i].posicao.y,galinha[i].posicao.z);
			if(galinha[i].velocidade.x == 1 && galinha[i].velocidade.z == 1){
				glRotatef(45,0,1,0);
				glRotatef(180,0,1,0);
			}
			if(galinha[i].velocidade.x == -1 && galinha[i].velocidade.z == 1){
				glRotatef(135,0,1,0);

			}
			if(galinha[i].velocidade.x == -1 && galinha[i].velocidade.z == -1){
				glRotatef(225,0,1,0);
				glRotatef(180,0,1,0);
			}
			if(galinha[i].velocidade.x == 1 && galinha[i].velocidade.z == -1){
				glRotatef(315,0,1,0);
			}
			glmDraw(galinha[i].model, GLM_COLOR);
		glPopMatrix();
	}
}

void desenhaSolo(){
	GLfloat especularidade[] = {1.0,1.0,1.0,1.0};
	GLfloat brilho[] = {20.0};
	GLfloat corBranca[] = {1.0,1.0,1.0,1.0};
	GLfloat corVerde[] = {1,0.5,0,1.0};
	glDisable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMaterialfv(GL_FRONT, GL_SHININESS,brilho);
  	glMaterialfv(GL_FRONT, GL_AMBIENT, corVerde);
   	glMaterialfv(GL_FRONT, GL_DIFFUSE, corBranca);
	
	if(linhasRelevo){
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	glPushMatrix();
		glTranslatef(0,-200,0);
			glColor3f(0,1,0);
			for(int x = 0; x < 100; x++){
				for(int z = 0; z < 100; z++){
					glPushMatrix();
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, idTexturaGrama);
						glTranslatef(-200,0,200);
						glBegin(GL_TRIANGLE_STRIP);
						glTexCoord2f(0,0);
						glVertex3f(x*5,pontos[x][z],(-z)*5);
						glTexCoord2f(0,1);
						glVertex3f((x+1)*5,pontos[x+1][z],(-z)*5);
						glTexCoord2f(1,1);
						glVertex3f(x*5,pontos[x][z+1],(-z-1)*5);
						glTexCoord2f(0,0);
						glEnd();
						glDisable(GL_TEXTURE_2D);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, idTexturaGrama);
						glBegin(GL_TRIANGLE_STRIP);
						glTexCoord2f(1,0);
						glVertex3f((x+1)*5,pontos[x+1][z],(-z)*5);
						glTexCoord2f(1,1);
						glVertex3f((x+1)*5,pontos[x+1][z+1],(-z-1)*5);
						glTexCoord2f(0,1);
						glVertex3f(x*5,pontos[x][z+1],(-z-1)*5);
						glEnd();
						glDisable(GL_TEXTURE);		
					glPopMatrix();
				}
			}

			glColor3f(1,1,0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, idTexturaTerra);
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(0,0);
				glVertex3f(-70,5,-70);
				glTexCoord2f(0,1);
				glVertex3f(70,5,-70);
				glTexCoord2f(1,1);
				glVertex3f(70,5,70);
				glTexCoord2f(1,0);
				glVertex3f(-70,5,70);
			glEnd();
			glDisable(GL_TEXTURE);
		
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
}

void desenharArvore(){
	for(int i = 0; i < qtdDeArvores; i++){
		glPushMatrix();
			glTranslatef(arvore[i].posicao.x,arvore[i].posicao.y, arvore[i].posicao.z);
			glScalef(5.f,5.f,5.f);
				glmDraw(arvore[i].model,GLM_COLOR);
			
		glPopMatrix();
	}
}

void desenhaEstabulo(){
	glDisable(GL_COLOR_MATERIAL);
	glPushMatrix();
		glTranslatef(estabulo.posicao.x,estabulo.posicao.y,estabulo.posicao.z);
		glRotated(-90,0,1,0);
		glColor3f(1,0,0);
		glScaled(0.1,0.1,0.1);
		glmDraw(estabulo.model,GLM_TEXTURE);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	
}

void desenhaCerca(){
	
	glPushMatrix();
		glTranslatef(cerca[0].posicao.x,cerca[0].posicao.y,cerca[0].posicao.z);
		glRotated(-90,1,0,0);
		glRotated(90,0,0,1);
		glScaled(0.6,0.3,0.2);
		glmDraw(cerca[0].model,GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(cerca[1].posicao.x,cerca[1].posicao.y,cerca[1].posicao.z);
		glRotated(-90,1,0,0);
		glScaled(0.6,0.3,0.2);
		glmDraw(cerca[1].model,GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(cerca[2].posicao.x,cerca[2].posicao.y,cerca[2].posicao.z);
		glRotated(-90,1,0,0);
		glRotated(90,0,0,1);
		glScaled(0.6,0.3,0.2);
		glmDraw(cerca[2].model,GLM_TEXTURE);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(cerca[3].posicao.x,cerca[3].posicao.y,cerca[3].posicao.z);
		glRotated(-90,1,0,0);
		glScaled(0.6,0.3,0.2);
		glmDraw(cerca[3].model,GLM_TEXTURE);
	glPopMatrix();
	

}

void desenhaCena(){
	desenhaSolo();
	desenharArvore();
	desenhaEstabulo();
	desenhaCerca();
	desenhaGalinhas();


}
