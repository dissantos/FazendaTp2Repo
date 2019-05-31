#include "desenha.h"
#include "estados.h"
#include "variaveisGlobais.h"
#include "mundo.h"
GLfloat angle, fAspect;
int keys[255];
int galinhaAtual = 0;
int modoCamera = 1;
double horaDoDia = -500;
float luzVerde = 0;
// Função callback chamada para fazer o desenho
void Desenha(void)
{
	
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);

	desenhaCena();

	// Executa os comandos OpenGL
	glutSwapBuffers();
 }

// Inicializa parâmetros de rendering
void Inicializa (void)
{ GLfloat luzAmbiente[4]={0.8,0.8,0.8,1.0}; 
	GLfloat luzDifusa[4]={1,luzVerde,0,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1, 1, 1, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={horaDoDia, 80.0, 200, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;
	//limpa tela
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glShadeModel(GL_SMOOTH);


	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
  
  //controle de ligar ou desligar a luz
  luzEstaLigada = 1;
  
  angle=45;
	qtdDeGalinhas = 10	;
	galinha = malloc(sizeof(OBJETO)*qtdDeGalinhas);
	for(int i = 0; i < qtdDeGalinhas; i++){
		galinha[i].posicao.x = rand()%71;
		galinha[i].velocidade.x = 1;
		if(rand()%2 == 0)
			galinha[i].velocidade.x = -1;
		if(rand()%2 == 0)
			galinha[i].posicao.x *= -1;
		galinha[i].posicao.y = -190;
		galinha[i].velocidade.y = 2;
		galinha[i].posicao.z = rand()%71;
		galinha[i].velocidade.z = 1;
		if(rand()%2 == 0)
			galinha[i].velocidade.z = -1;
		if(rand()%2 == 0)
			galinha[i].posicao.z *= -1;
		
		galinha[i].model = glmReadOBJ("humanoid_quad.obj");
	}
	
	for (int i = 0; i < 4; i++){
		if(i == 0){
			cerca[i].posicao.x = 70;
			cerca[i].posicao.z = 53;
		}
		if(i == 1){
			cerca[i].posicao.x = -50;
			cerca[i].posicao.z = 65;
		}
		if(i == 2){
			cerca[i].posicao.x = -70;
			cerca[i].posicao.z = 53;
		}
		if(i == 3){
			cerca[i].posicao.x = -50;
			cerca[i].posicao.z = -70;
		}
		cerca[i].posicao.y = -190;
		cerca[i].model = glmReadOBJ("13078_Wooden_Post_and_Rail_Fence_v1_l3.obj");
	}
	estabulo.posicao.x = 105;
	estabulo.posicao.y = -190;
	estabulo.posicao.z = 0;
	estabulo.model = glmReadOBJ("Stable.obj");

	
	idTexturaGrama = SOIL_load_OGL_texture(
        "grama.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
	
	idTexturaTerra = SOIL_load_OGL_texture(
        "terra.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
	
	
	
	gerarRelevo();
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	if(modoCamera == 1){
    	gluLookAt(0,80,1, 0,0,0, 0,1,0);
	}
	else{
		gluLookAt(galinha[galinhaAtual].posicao.x - 5,10,galinha[galinhaAtual].posicao.z -5,0,0,0,0,1,0);	
	}
	
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}
void atualiza(){
	if(keys[27] == 1)
		exit(0);
	if(keys['1'] == 1){
		modoCamera = 1;
		PosicionaObservador();
	}
	if(keys['2'] == 1){
		modoCamera = 2;
		PosicionaObservador();
	}
	if(keys['L'] == 1 || keys['l'] == 1){
		if(luzEstaLigada == 1){
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			luzEstaLigada = 0;
		}
		else{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			luzEstaLigada = 1;
		}
	}
	//atualiza a luz como o passar do dia
	GLfloat posicaoLuz[4]={200, 80.0, 400, 1.0};
	GLfloat luzDifusa[4]={1,luzVerde,0,1.0};	   // "cor" 
	GLfloat incrementoDeLuz = 0.002;
	horaDoDia += 2 ;
	luzVerde += incrementoDeLuz;
	if(horaDoDia == 500)
		horaDoDia = -500;
	if(luzVerde <= 0 || luzVerde >= 1)
		incrementoDeLuz *= -1;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
	for(int i = 0; i < qtdDeGalinhas; i++){
		mover(&galinha[i]);
	}
	glutPostRedisplay();
	glutTimerFunc(33,atualiza,0);
}

void teclaPressionada(unsigned char key, int x, int y){
	keys[key] = 1;
}

void teclaLiberada(unsigned char key, int x, int y){
	keys[key] = 0;
	// se personagem solta a tecla mudar vetor teclas para 0
}

// Programa Principal
int main(int argc, char** argv){
	glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  	glutInitWindowSize(800, 800);
  	glutInitWindowPosition(100, 100);
	glutCreateWindow("Fazenda");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(teclaPressionada);
    glutKeyboardUpFunc(teclaLiberada);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutTimerFunc(0,atualiza,0);
	Inicializa();

	glutMainLoop();
}
