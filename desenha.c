#include "desenha.h"
#include "coordenadas.h"


void desenhaTriforce(){
	glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(triforce.posicao.x,triforce.posicao.y, triforce.posicao.z);
		glRotatef(anguloDeRotacao,1,0,1);
		glScaled(5,5,5);
			glmDraw(triforce.model,GL_NONE);
	glPopMatrix();
}

void desenhaGalinhas(){
	glColor3f(1,1,1);
	for(int i = 0; i < qtdDeGalinhas; i++){
		glPushMatrix();
			glTranslatef(galinha[i].posicao.x,galinha[i].posicao.y,galinha[i].posicao.z);
			glScaled(1+respiracao,1+respiracao,1+respiracao);
			if(galinha[i].velocidade.x == 1 && galinha[i].velocidade.z == 1){
				glRotatef(43,0,1,0);
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

void desenharPorco(){
	for(int i = 0; i < qtdDePorco; i++){
		glPushMatrix();
			glTranslatef(porco[i].posicao.x,porco[i].posicao.y,porco[i].posicao.z);
			glScaled(0.75+respiracao,0.75+respiracao,0.75+respiracao	);	
			if(porco[i].velocidade.x == 1 && porco[i].velocidade.z == 1){
				glRotatef(45,0,1,0);
				glRotatef(180,0,1,0);
			}
			if(porco[i].velocidade.x == -1 && porco[i].velocidade.z == 1){
				glRotatef(135,0,1,0);

			}
			if(porco[i].velocidade.x == -1 && porco[i].velocidade.z == -1){
				glRotatef(225,0,1,0);
				glRotatef(180,0,1,0);
			}
			if(porco[i].velocidade.x == 1 && porco[i].velocidade.z == -1){
				glRotatef(315,0,1,0);
			}
			glmDraw(porco[i].model, GLM_COLOR);
		glPopMatrix();
	}
}

void desenharPorcoPai(){

	for(int i = 0; i < qtdDePorcoPai; i++){
		glPushMatrix();
			glTranslatef(porcoPai[i].posicao.x,porcoPai[i].posicao.y,porcoPai[i].posicao.z);
			glScaled(1.75+respiracao,1.75+respiracao,1.75+respiracao	);	
			if(porcoPai[i].velocidade.x == 1 && porcoPai[i].velocidade.z == 1){
				glRotatef(45,0,1,0);
				glRotatef(180,0,1,0);
			}
			if(porcoPai[i].velocidade.x == -1 && porcoPai[i].velocidade.z == 1){
				glRotatef(135,0,1,0);

			}
			if(porcoPai[i].velocidade.x == -1 && porcoPai[i].velocidade.z == -1){
				glRotatef(215,0,1,0);
				glRotatef(180,0,1,0);
			}
			if(porcoPai[i].velocidade.x == 1 && porcoPai[i].velocidade.z == -1){
				glRotatef(335,0,1,0);
			}
			glmDraw(porcoPai[i].model, GLM_COLOR);
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

//http://nehe.gamedev.net/tutorial/cool_looking_fog/19001/
//faz o fogfog
void desenhaFog(){
	GLuint filter;                      // Which Filter To Use
	GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // os tres tipos de Fog
	GLuint fogfilter= 1;                    // Fog a ser utilizado
	GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};      // cor do Fog
	glClearColor(0.5f,0.5f,0.5f,1.0f);          
 
	glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);            // coloca cor do Fog
	glFogf(GL_FOG_DENSITY, 0.008f);              // Densidade do fog
	glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
	glFogf(GL_FOG_START, 9.0f);             // Fog Start Depth
	glFogf(GL_FOG_END, 10.0f);               // Fog End Depth
	glEnable(GL_FOG);                   // Habilita GL_FOG
	fogAtivo = 1;
}

void desenhaCena(){
	desenhaTriforce();
	desenhaSolo();
	desenharArvore();
	desenhaEstabulo();
	desenhaCerca();
	desenhaGalinhas();
	desenharPorco();
	desenharPorcoPai();

}
