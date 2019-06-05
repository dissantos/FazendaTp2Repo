#include "desenha.h"
#include "estados.h"
#include "variaveisGlobais.h"
#include "mundo.h"
GLfloat angle, fAspect;
int keys[255];
int galinhaAtual = 0;
int modoCamera = 1;
float luzVerde = 0;
int delay = 0;


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
		gluLookAt(galinha[galinhaAtual].posicao.x-30*galinha[galinhaAtual].velocidade.x,-150,galinha[galinhaAtual].posicao.z-30*galinha[galinhaAtual].velocidade.z,
							galinha[galinhaAtual].posicao.x,-190,galinha[galinhaAtual].posicao.z, 
							0,1,0);	
	}
	
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);
	PosicionaObservador();
	desenhaCena();

	// Executa os comandos OpenGL
	glutSwapBuffers();
 }

// Inicializa parâmetros de rendering
void Inicializa (void)
{ GLfloat luzAmbiente[4]={0.8,0.8,0.8,1.0}; 
	GLfloat luzDifusa[4]={1,luzVerde,0,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1, 1, 1, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0, 80.0, 400, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;
	//limpa tela
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glShadeModel(GL_FLAT);


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
  incrementoDeLuz = 0.02;
  //controle do relevo
  linhasRelevo = 0;
  //controleFOG --------------------------------------------
  fogAtivo=0;
 
  respiracao = 0;
  //incremento de respiracao dos animais
	incrementoRespiracao = 0.01;
  
  angle=45;
	qtdDeGalinhas = 10	;
	galinha = malloc(sizeof(OBJETO)*qtdDeGalinhas);
	for(int i = 0; i < qtdDeGalinhas; i++){
		
		gerarPosicoesDosAnimais(&galinha[i]);
		galinha[i].model = glmReadOBJ("GALINACEA.obj");
		
	}
	
	qtdDePorco = 4;
	porco = malloc(sizeof(OBJETO)*qtdDePorco);
	for(int i = 0; i < qtdDePorco;i++){
		gerarPosicoesDosAnimais(&porco[i]);
		porco[i].model = glmReadOBJ("pigpronto.obj");
	}
	
	triforce.posicao.x = 200;
	triforce.posicao.z = -250;
	triforce.posicao.y = -190;
	triforce.model = glmReadOBJ("triforce.obj");
	anguloDeRotacao = 0;
	
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
		cerca[i].posicao.y = -200;
		cerca[i].model = glmReadOBJ("13078_Wooden_Post_and_Rail_Fence_v1_l3.obj");
	}
	
	estabulo.posicao.x = 105;
	estabulo.posicao.y = -190;
	estabulo.posicao.z = 0;
	estabulo.model = glmReadOBJ("Stable.obj");

	qtdDeArvores = 30;
	arvore = malloc(sizeof(OBJETO)*qtdDeArvores);
	for(int i = 0; i < qtdDeArvores; i++){
		arvore[i].model = glmReadOBJ("arvere1.obj");
	}
	
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
	for(int i = 0; i < qtdDeArvores; i++){
		int x,z;
		while(1){
			x = rand()%100+80;
			z = rand()%100+80;
			int teste = 1;
			if(rand()%2 == 0)
				x *= -1;
			if(rand()%2 == 0)
				z *= -1;
			
			for(int j = 0; j < i; j++){
				if(arvore[j].posicao.x == x && arvore[j].posicao.z == z){
					teste = 0;
					break;
				}
			}
			if(teste == 1)
				break;
		}
		
		arvore[i].posicao.y = -190;
		arvore[i].posicao.x = x;
		arvore[i].posicao.z = z;
		printf("x: %d - z: %d\n",x,z);
		
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
}
void atualiza(){
	if ((keys['N'] == 1 || keys['n'] == 1) && modoCamera == 2){
		if(fogAtivo == 0){
			desenhaFog();
		}
		else {
			glDisable(GL_FOG);
			fogAtivo = 0;
		}
	}
	
	if(keys[27] == 1)
		exit(0);
	if(keys['1'] == 1){
		modoCamera = 1;
	}
	if(keys['2'] == 1){
		modoCamera = 2;
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
	if(keys['R'] == 1 || keys['r'] == 1){
		linhasRelevo = 1 - linhasRelevo;
	}
	if(keys['C'] == 1 || keys['c']){
		galinhaAtual++;
		if(galinhaAtual == qtdDeGalinhas)
			galinhaAtual = 0;
	}

	//atualiza a luz como o passar do dia

	GLfloat luzDifusa[4]={1,luzVerde,0,1.0};	   // "cor" 
	
	luzVerde += incrementoDeLuz;
	if(luzVerde <= 0 || luzVerde >= 1)
		incrementoDeLuz *= -1;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	
	respiracao += incrementoRespiracao;
	if(respiracao <= 0 || respiracao >= 0.1)
		incrementoRespiracao*=-1;

	delay++;
	if(delay%40 == 0){
		int posicaoAuxiliar = rand()%qtdDeGalinhas;
		maquinaDeEstado(&galinha[posicaoAuxiliar],1 - galinha[posicaoAuxiliar].estado);
	}
	
	
	
	for(int i = 0; i < qtdDeGalinhas; i++){
		if(galinha[i].estado == 1)
			mover(&galinha[i]);
	}
	
	for(int i = 0; i < qtdDePorco; i++){
			mover(&porco[i]);
	}
	
	anguloDeRotacao+=5;
	glutPostRedisplay();
	glutTimerFunc(25,atualiza,0);
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
	//system("clear");
	printf("Instrucoes:\nR - Mostrar Relevo\nL - Ligar/Desligar a luz\nBotao Esquerdo/Direito do mouse - Zoom\n1 - Entrar no modo camera em cima\n2 - Entrar no modo terceira pessoa\n C - Mudar a camera terceira pessoa para outra galinha\n");

	glutMainLoop();
}
