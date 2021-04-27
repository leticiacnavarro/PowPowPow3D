#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "menu.h"

void Menu::RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b)
{
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glColor3f(r,g,b);
        glRasterPos3f(x, y, z);
        const char* tmpStr;
        tmpStr = text;
        while( *tmpStr ){
            glutBitmapCharacter(fonte, *tmpStr);
            tmpStr++;
        }
    glPopAttrib();
}

void Menu::PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b)
{
    glMatrixMode (GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity ();
        glOrtho (0, 1, 0, 1, -1, 1);
        RasterChars(x, y, 0, text, r, g, b);    
    glPopMatrix();
    glMatrixMode (GL_MODELVIEW);
}

void Menu::DesenhaPlacar(GLint pontosLutador, GLint pontosBot)
{
        static char str[1000];
        char *temp;
        sprintf(str, "%d / %d", pontosLutador, pontosBot);
        temp = str;
        GLfloat x = 0.01;
        GLfloat y = 0.01;
        PrintText(x, y, temp, 0, 0, 0);

}

void Menu::DesenhaFinalJogo(bool ganhou)
{
        static char str[1000];
        char *temp;
        if(ganhou)
        {
           sprintf(str, "JOGADOR GANHOU!!");
        }
        else
        {
           sprintf(str, "BOT GANHOU!!");
        }
        temp = str;

        GLfloat x = 0.5;
        GLfloat y = 0.5;

    //    int tamanho = glutBitmapLength(fonte, reinterpret_cast<const unsigned char*>(temp)); 
    //    x = x - (tamanho/2);

        PrintText(x, y, temp, 0, 0, 0);

}

void Menu::DesenhaMenu(){
    
}

