#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <math.h>

#include "ringue.h"
#include "lutador.h"
#include "iniciacao.h"
#include "menu.h"
#include "util.h"

#define INC_KEY 1
#define INC_KEYIDLE 0.2

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
GLint distanciaSocoTotal = 200;
GLint braco = 1;
GLboolean parouDeSocarBot = true;

// Tipo Jogo

bool modoTreino;

//Util
int toggleCam = 0;
bool toggleLight = false;
bool toggleApagaTudo;
int buttonDown = 0;

//Texture
GLuint texturePlane;
GLuint textureBotWins;
GLuint texturePlayerWins;

GLuint LoadTextureRAW( const char * filename )
{

    GLuint texture;
    
    Image* image = loadBMP(filename);

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                             0,                            //0 for now
                             GL_RGB,                       //Format OpenGL uses for image
                             image->width, image->height,  //Width and height
                             0,                            //The border of the image
                             GL_RGB, //GL_RGB, because pixels are stored in RGB format
                             GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
                             image->pixels);               //The actual pixel data
    delete image;

    return texture;
}

void changeCamera(int angle, int zNear, int zFar)
{
    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    gluPerspective (angle, Width / Height, zNear, zFar);

    glMatrixMode (GL_MODELVIEW);
        glutPostRedisplay();
}

void orthogonalStart() 
{
    glMatrixMode(GL_PROJECTION);
    // if(!toggleLight){
        glDisable(GL_LIGHTING);
    // }
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-500/2, 500/2, -500/2, 500/2);
    glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd()
{
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void background(GLuint texture)
{

    orthogonalStart();

    // texture width/height
    const int iw = 500;
    const int ih = 500;

    glPushMatrix();
    glBindTexture( GL_TEXTURE_2D, texture); 

    glTranslatef( -iw/2, -ih/2, 0 );
    glBegin(GL_QUADS);
        glTexCoord2i(0,0); glVertex2i(0, 0);
        glTexCoord2i(1,0); glVertex2i(iw, 0);
        glTexCoord2i(1,1); glVertex2i(iw, ih);
        glTexCoord2i(0,1); glVertex2i(0, ih);
    glEnd();
    glPopMatrix();

    orthogonalEnd();
}

void renderScene(void)
{
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glClearColor(0.692,	0.852,	0.988, 1.0f); // Black, no opacity(alpha).
  //  glClearColor(0,0,0, 1.0f); // Black, no opacity(alpha).

    glClear (   GL_COLOR_BUFFER_BIT | 
                GL_DEPTH_BUFFER_BIT);

    
    if(pontoLutador < 10 && pontoBot < 10)
    {    
        background(texturePlane);
        menu.DesenhaMiniMapa(lutador.GetX(), lutador.GetY(), bot.GetX(), bot.GetY());

        menu.DesenhaPlacar(pontoLutador, pontoBot);

        util.ProcessaCamera(toggleCam, lutador);
   //     util.DrawAxes(50);
        ringue.Desenha();
        util.Iluminacao(lutador, bot, toggleLight, ringue, toggleApagaTudo);
        bot.Desenha(toggleLight);

        lutador.Desenha(toggleLight);
       
    }
    else if(pontoLutador >= pontoBot)
    {
        background(texturePlayerWins);

     //   background();
      //  menu.DesenhaFinalJogo(true);
    }
    else if(pontoBot > pontoLutador)
    {
        background(textureBotWins);

       // background();
     //   menu.DesenhaFinalJogo(false);
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
            changeCamera(util.GetCamAngle(), 15, 1000);
            break;
        case '2':
            toggleCam = 1;
            changeCamera(50, 15, 1000);
            break;
        case '3':
            toggleCam = 2;
            changeCamera(util.GetCamAngle(), 5, 1000);
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
        case 'l':
        case 'L':
            toggleApagaTudo = !toggleApagaTudo;
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
  //  glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    ringue.CarregaTexturas();
    lutador.CarregaTexturas();
    bot.CarregaTexturas();  
    texturePlane = LoadTextureRAW( "modelos/ceu.bmp" );
    textureBotWins = LoadTextureRAW( "modelos/bot_wins.bmp" );
    texturePlayerWins = LoadTextureRAW( "modelos/player_wins.bmp" );

    ringue.CalculaAlturaComBaseNoLutador(lutador.altura);
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
        bool acertou = bot.Soca(distanciaSocoTotal, distanciaSoco, braco, lutador);
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
           //   cout << "socando" << endl;
            bool acertou = lutador.Soca(WidthHalf, distanciaPercorrida, 1, bot);
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
            bool acertou = lutador.Soca(WidthHalf, distanciaPercorrida, 2, bot);
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
        
        util.camYXAngle += x - util.lastX;
        util.camYZAngle -= y - util.lastY;

        util.lastX = x;
        util.lastY = y;

        GLfloat s = abs(util.camYXAngle*M_PI/180);
        GLfloat t = abs(util.camYZAngle*M_PI/180);
        // cout << "s: " << (util.camYXAngle) << " t: " << (util.camYZAngle) << endl;

    }
        glutPostRedisplay();

}

void Inicializa(char *caminhoArquivo)
{
    if(!iniciacao.ProcessaArquivo(caminhoArquivo))
    {
        exit(0);
    }

    
    iniciacao.IniciaArena(Width, Height, WidthHalf, HeightHalf, ringue);
    iniciacao.IniciaLutadores(lutador, bot, ringue);
    iniciacao.TipoJogo(modoTreino);

    menu.Iniciacao(Width, Height); 

    // ringue.Iniciacao(Width, Height, 3);  
     
}


void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    changeCamera(util.GetCamAngle(), 15, 1000);
}


int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    Inicializa(argv[1]);

    // Create the window.
    glutInitWindowSize(500, 500);
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
