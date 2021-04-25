#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "menu.h"

void Menu::RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b)
{
    //Push to recover original attributes
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        //Draw text in the x, y, z position
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
    //Draw text considering a 2D space (disable all 3d features)
    glMatrixMode (GL_PROJECTION);
    //Push to recover original PROJECTION MATRIX
    glPushMatrix();
        glLoadIdentity ();
     glOrtho(-(gX/2),     // X coordinate of left edge             
             (gX/2),     // X coordinate of right edge            
             -(gY/2),     // Y coordinate of bottom edge             
             (gY/2),     // Y coordinate of top edge             
             -100,     // Z coordinate of the “near” plane            
             100);    // Z coordinate of the “far” plane        RasterChars(x, y, 0, text, r, g, b);    
         RasterChars(x, y, 0, text, r, g, b);   

    glPopMatrix();
    glMatrixMode (GL_MODELVIEW);
}
void Menu::DesenhaTexto(GLfloat x, GLfloat y, char *tmpStr, bool center)
{
    
    glPushMatrix();
        int len, i;
        GLfloat color_r[] = { 1.0, 0.0, 0.0, 1.0 };
        GLfloat color_g[] = { 0.0, 1.0, 0.0, 1.0 };




        glColor3fv(color_r);

        glRasterPos2f(x, y); //glWindowPos
        len = (int) strlen(tmpStr);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(fonte, tmpStr[i]);
        }

    glPopMatrix();
}



void Menu::DesenhaPlacar(GLint pontosLutador, GLint pontosBot)
{
        static char str[1000];
        char *temp;
        sprintf(str, "%d / %d", pontosLutador, pontosBot);
        temp = str;
        GLfloat x = -gX/2 + 10;
        GLfloat y = -gY/2 + 10;
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

        GLfloat x = 0;
        GLfloat y = 0;

        int tamanho = glutBitmapLength(fonte, reinterpret_cast<const unsigned char*>(temp)); 
        x = x - (tamanho/2);

        PrintText(x, y, temp, 0, 0, 0);

}

void Menu::DesenhaMenu(){
    
}

