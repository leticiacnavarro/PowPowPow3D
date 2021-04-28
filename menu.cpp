#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include "menu.h"

void Menu::DesenhaMiniArena(GLfloat side, double r, double g, double b)
{
    float halfWidth = side/2;

    // glBegin(GL_QUADS);
    //     glVertex2f(-halfWidth, 0);
    //     glVertex2f(halfWidth, 0);
    //     glVertex2f(halfWidth, height);
    //     glVertex2f(-halfWidth, height);
    // glEnd();
    //     glPopAttrib();
    glClear(GL_DEPTH_BUFFER_BIT);

    glColor3f (r, g, b);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-halfWidth, -halfWidth);
        glVertex2f(halfWidth, -halfWidth);
        glVertex2f(halfWidth, halfWidth);
        glVertex2f(-halfWidth, halfWidth);
    glEnd();

    //Lutador
    glPushMatrix();
        glTranslatef(gXLutador, gYLutador, 0);
            glColor3f (0, 1, 0);
        int pts = 50;

        for(unsigned int i = 0; i <= pts; ++i ){

            float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
            float x = 0.01 * sin(angle);
            float y = 0.01 * cos(angle);
            
            glPointSize(3);

            glBegin(GL_POLYGON);
                glVertex3f(x, y, 0.0f);
        }
        glEnd();
    glPopMatrix();

    //Bot
    glPushMatrix();
        glTranslatef(gXBot, gYBot, 0);
            glColor3f (1, 0, 0);

        for(unsigned int i = 0; i <= pts; ++i ){

            float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
            float x = 0.01 * sin(angle);
            float y = 0.01 * cos(angle);
            
            glPointSize(3);

            glBegin(GL_POLYGON);
                glVertex3f(x, y, 0.0f);
        }
        glEnd();
    glPopMatrix();
    glEnd();

}


void Menu::RasterRectangle(GLfloat x, GLfloat y, GLfloat z, double r, double g, double b)
{
    
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glColor3f(r,g,b);
        glTranslatef(0.9, 0.1, 0);
        DesenhaMiniArena(0.25, 1, 0, 1);
        // glTranslatef(0.01, 0.01, 0);
        // DesenhaCirc(0.01, 1, 1, 0);
    glPopAttrib();

}

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
void Menu::PrintDrawing(GLfloat x, GLfloat y, double r, double g, double b)
{
    glMatrixMode (GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity ();
        glOrtho (0, 1, 0, 1, -1, 1);
        RasterRectangle(x, y, 0, r, g, b);    

    glPopMatrix();
    glMatrixMode (GL_MODELVIEW);
}

void Menu::CalculaPosicao(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    //cout << "gXLutador: " << x1 << "gYLutador: " << gYLutador << endl;

    gXLutador = (x1 * 0.25)/(ladoRingue)/2;
    gYLutador = (y1 * 0.25)/(ladoRingue) /2;
    gXBot = (x2 * 0.25)/(ladoRingue)/2;
    gYBot = (y2 * 0.25)/(ladoRingue)/2;

}

void Menu::DesenhaMiniMapa(GLfloat xLutador, GLfloat yLutador, GLfloat xBot, GLfloat yBot)
{
    CalculaPosicao(xLutador, yLutador, xBot, yBot);
    PrintDrawing(1, 1, 1, 1, 0);
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
        PrintText(x, y, temp, 0, 1, 0);

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

