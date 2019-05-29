#include "desenha.h"
#include "estados.h"
GLfloat angle, fAspect;
int keys[255];
int galinhaAtual = 0;
int modoCamera = 1;

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha o teapot com a cor corrente (wire-frame)
	desenhaCena();

	// Executa os comandos OpenGL
	glutSwapBuffers();
 }

// Inicializa parâmetros de rendering
void Inicializa (void)
{ 
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
		galinha[i].velocidade.y = 0;
		galinha[i].posicao.z = rand()%71;
		galinha[i].velocidade.z = 1;
		if(rand()%2 == 0)
			galinha[i].velocidade.z = -1;
		if(rand()%2 == 0)
			galinha[i].posicao.z *= -1;
	}
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
	printf("%d\n",modoCamera);
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
