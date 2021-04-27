#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <math.h>

#include "lutador.h"
#include "iniciacao.h"
#include "menu.h"
#include "util.h"
#include "ringue.h"

#define INC_KEY 1
#define INC_KEYIDLE 0.1

//Key status
int keyStatus[256];

Menu menu;
Iniciacao iniciacao;
Util util;

Lutador lutador;
Lutador bot;

Ringue ringue;

// Window dimensions
GLint Width;
GLint Height;

GLint WidthHalf;
GLint HeightHalf;

GLint pontoCentral;

//Pontuacao
GLint pontoLutador;
GLint pontoBot;


//Lutador Socando pow pow pow
GLboolean parouDeSocarLutador = true;
GLboolean botaoCerto;


// Bot socando pow pow pow
GLint distanciaSoco = 0;
GLint distanciaSocoTotal = 25;
GLint braco = 1;
GLboolean parouDeSocarBot = true;

// Tipo Jogo

bool modoTreino;

//Util
int toggleCam = 0;
bool toggleLight = false;
int buttonDown = 0;

void renderScene(void)
{
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glClearColor(0.692,	0.852,	0.988, 1.0f); // Black, no opacity(alpha).
    glClear (   GL_COLOR_BUFFER_BIT | 
                GL_DEPTH_BUFFER_BIT);

    
    if(pontoLutador < 10 && pontoBot < 10)
    {    
        menu.DesenhaPlacar(pontoLutador, pontoBot);
        util.ProcessaCamera(toggleCam, lutador);
   //     util.DrawAxes(50);
        ringue.Desenha();
        util.Iluminacao(lutador, bot, toggleLight);
        bot.Desenha();

        lutador.Desenha();
       
    }
    else if(pontoLutador >= pontoBot)
    {
        menu.DesenhaFinalJogo(true);
    }
    else if(pontoBot > pontoLutador)
    {
        menu.DesenhaFinalJogo(false);
    }

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '+':
            util.zoom++;
            break;
        case '-':
            util.zoom--;
            break;
        case '1':
            toggleCam = 0;
            break;
        case '2':
            toggleCam = 1;
            break;
        case '3':
            toggleCam = 2;
            break;
        case 'n':
        case 'N':
            toggleLight = !toggleLight; //Using keyStatus trick
            break; 
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'w':
        case 'W':
             keyStatus[(int)('w')] = 1; //Using keyStatus trick
             break;
        case 's':
        case 'S':
             keyStatus[(int)('s')] = 1; //Using keyStatus trick
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void init(void)
{
    ResetKeyStatus();
    glEnable(GL_TEXTURE_2D);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
      
}

void movimentaBot(double inc)
{
    if(distanciaSoco <= 0)
    {
        distanciaSoco = 0;
        parouDeSocarBot = true;

        if(braco == 1){
            braco = 2;
        }
        else if(braco == 2){
            braco = 1;
        }
    }

    if(inc < 1){
        inc = 1;
    }
    if(bot.VerificaSePode(inc, Width, Height, lutador.GetX(), lutador.GetY())){
        bot.Anda(inc);
    }
    else
    {
        //distanciaSoco += inc;
        bool acertou = bot.Soca(distanciaSocoTotal, distanciaSoco, braco, lutador.GetX(), lutador.GetY());
        if(acertou)
        {
            if(parouDeSocarBot)
            {
                pontoBot++;
                parouDeSocarBot = false;
            }
            distanciaSoco -= inc;
        }
        else
        {
            if(parouDeSocarBot)
            {
                distanciaSoco += inc;
            }
            else
            {
                distanciaSoco -= inc;
            }
        }
    }
    bot.GiraSozinho(inc, lutador.GetX(), lutador.GetY());

}

bool VerificaSeEstaAndando()
{
    if(keyStatus[(int)('w')])
    {
        return false;
    }
    if(keyStatus[(int)('s')])
    {
        return false;
    }  
    if(keyStatus[(int)('a')])
    {            
        return false;
    }
    if(keyStatus[(int)('d')])
    {
        return false;
    }

    return true;
} 

void idle(void)
{
    if(pontoLutador < 10 && pontoBot < 10)
    {    
        static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
        GLdouble currentTime, timeDiference;
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        timeDiference = currentTime - previousTime;
        previousTime = currentTime;

        double inc = INC_KEY * timeDiference * INC_KEYIDLE;

    //    for(int i = 0; i < 90000000; i++);

        if(!modoTreino)
        {
           movimentaBot(inc);
        }

        //Treat keyPress
        if(keyStatus[(int)('w')])
        {
            if(lutador.VerificaSePode(inc, Width, Height, bot.GetX(), bot.GetY()))
            {
                        lutador.ParaDeSocar();

                lutador.Anda(inc);

            }
        }
        if(keyStatus[(int)('s')])
        {
            if(lutador.VerificaSePode(-inc, Width, Height, bot.GetX(), bot.GetY()))
            {
                        lutador.ParaDeSocar();

                lutador.Anda(-inc);

            }
        }  
        if(keyStatus[(int)('a')])
        {    
                    lutador.ParaDeSocar();
        
            lutador.Gira(inc);
        }
        if(keyStatus[(int)('d')])
        {
                    lutador.ParaDeSocar();

            lutador.Gira(-inc);
        }
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{


    if(state == 0)
    {
        pontoCentral = x;
        if(button == 0)
        {
            botaoCerto = true;
        }
    }
    else
    {
        botaoCerto = false;

        pontoCentral = 0;
        lutador.ParaDeSocar();
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        util.lastX = x;
        util.lastY = y;
        buttonDown = 1;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        buttonDown = 0;
    }
}

void mouseArrasta(int x, int y)
{
    if(botaoCerto)
    {
        if(VerificaSeEstaAndando())
        {
        GLfloat distanciaPercorrida = abs(x - pontoCentral);

        if(distanciaPercorrida > WidthHalf)
        {
            distanciaPercorrida = WidthHalf;
        }
        
        if(x > pontoCentral){

            bool acertou = lutador.Soca(WidthHalf, distanciaPercorrida, 1, bot.GetX(), bot.GetY());
            if(acertou)
            {
                if(parouDeSocarLutador)
                {
                    pontoLutador++;
                    parouDeSocarLutador = false;
                }
            }
            else{
                parouDeSocarLutador = true;
            }
        }
        else if(x < pontoCentral)
        {
            bool acertou = lutador.Soca(WidthHalf, distanciaPercorrida, 2, bot.GetX(), bot.GetY());
            if(acertou)
            {
                if(parouDeSocarLutador)
                {
                    pontoLutador++;
                    parouDeSocarLutador = false;
                }
            }
            else{
                parouDeSocarLutador = true;
            }
    
        }
        }
        
    }
    else
    {
        if (!buttonDown)
            return;
        
        util.camYXAngle -= x - util.lastX;
        util.camYZAngle += y - util.lastY;

        util.lastX = x;
        util.lastY = y;
    }
        glutPostRedisplay();

}

void Inicializa(char *caminhoArquivo)
{
    if(!iniciacao.ProcessaArquivo(caminhoArquivo))
    {
        exit(0);
    }

    
    iniciacao.IniciaArena(Width, Height, WidthHalf, HeightHalf);
    iniciacao.IniciaLutadores(lutador, bot);
    iniciacao.TipoJogo(modoTreino);

    menu.Iniciacao(Width, Height); 

    ringue.Iniciacao(Width, Height, 3);  
     
}

void changeCamera(int angle, int w, int h)
{
    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    gluPerspective (angle, Width / Height, 1, 1000);

    glMatrixMode (GL_MODELVIEW);
        glutPostRedisplay();

}

void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);

    changeCamera(util.GetCamAngle(), w, h);
}


int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    Inicializa(argv[1]);

    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Pow Pow Pow");
 
    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutReshapeFunc (reshape);
    glutKeyboardUpFunc(keyup);
    glutMotionFunc(mouseArrasta);
    glutMouseFunc(mouse);
   
    init();
 
    glutMainLoop();
 
    return 0;
}
