#include "ringue.h"

#include <math.h>

GLuint Ringue::LoadTextureRAW( const char * filename )
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


void Ringue::DefineTamanhoLadoTotal()
{
    GLfloat x1 = gMesh.vertsPos[pontoBase1].x;
    GLfloat y1 = gMesh.vertsPos[pontoBase1].y;

    GLfloat x2 = gMesh.vertsPos[pontoBase2].x;
    GLfloat y2 = gMesh.vertsPos[pontoBase2].y;

    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    ladoTotal = (int)distanciaPontos;

}

void Ringue::DefineProfundidade()
{
    GLfloat z1 = gMesh.vertsPos[pontoHaste2].z;

    GLfloat z2 = gMesh.vertsPos[pontoBase1].z;

    profundidade = (int)z1 - z2;
}


void Ringue::DefineTamanhoLado()
{
    GLfloat x1 = gMesh.vertsPos[pontoBaseInterno1].x;
    GLfloat y1 = gMesh.vertsPos[pontoBaseInterno1].y;

    GLfloat x2 = gMesh.vertsPos[pontoBaseInterno2].x;
    GLfloat y2 = gMesh.vertsPos[pontoBaseInterno2].y;

    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    lado = (int)distanciaPontos;

}

void Ringue::DefineAltura()
{
    GLfloat p1 = gMesh.vertsPos[pontoBase1].z;
    GLfloat p2 = gMesh.vertsPos[pontoBaseInterno1].z;

    altura = p2 - p1;
}

void Ringue::CalculaAlturaComBaseNoLutador(GLfloat alturaLutador)
{
    gProporcaoAltura = (alturaLutador * 2)/profundidade;
    //  cout << gProporcaoAltura << endl;
    //   cout << gProporcao << endl;

}
void DisplayPlane (GLuint textura)
{
    float tile_x = 0.125;
    int tiles = 500;
    float height = 1;
    float width = 1;
    float u_max = height*tile_x;
    float v_max = width*tile_x;

    GLfloat materialEmission[] = { 0.10, 0.10, 0.10, 1};
    GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 100.0 };
    glColor3f(1,1,1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT  );//X
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );//Y
    glBindTexture (GL_TEXTURE_2D, textura);

    // double textureS = 1; // Bigger than 1, repeat
    // glBegin (GL_QUADS);
    //     glNormal3f(0,1,0);
    //     glTexCoord2f (0, 0);
    //     glVertex3f (-1, 0, -1);
    //     glNormal3f(0,1,0);
    //     glTexCoord2f (0, textureS);
    //     glVertex3f (-1, 0, +1);
    //     glNormal3f(0,1,0);
    //     glTexCoord2f (textureS, textureS);
    //     glVertex3f (+1, 0, +1);
    //     glNormal3f(0,1,0);
    //     glTexCoord2f (textureS, 0);
    //     glVertex3f (+1, 0, -1);
    // glEnd();


    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    for (int x=0; x < tiles; ++x)
    {    

        for (int y=0; y < tiles; ++y)
        {
            float x0 = (float)x/(float)tiles;
            float x1 = (float)(x+1)/(float)tiles;
            float y0 = (float)y/(float)tiles;
            float y1 = (float)(y+1)/(float)tiles;

            glTexCoord2f(u_max*x0, v_max*y0);  glVertex3f( width*y0, height*x0, 0);
            glTexCoord2f(u_max*x1, v_max*y0);  glVertex3f(width*y1, height*x0, 0);
            glTexCoord2f(u_max*x1, v_max*y1);  glVertex3f(width*y1, height*x1, 0);
            glTexCoord2f(u_max*x0, v_max*y1);  glVertex3f(width*y0, height*x1, 0);
        }
    }
    glEnd();

}

void Ringue::DesenhaRingue()
{
    GLfloat ladoChao = ladoTotal * gProporcao;
    glPushMatrix();
         glTranslatef(-ladoChao/2, -ladoChao/2, 0);

        glScalef(ladoChao, ladoChao,1);
        glTranslatef(0,0,0);
        // glRotatef(90,1,0,0);
        //       glTranslatef(10,0,0);

    DisplayPlane(texture);
 glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, (-altura));
        glScalef(gProporcao, gProporcao, gProporcao);
        gMesh.draw();
    glPopMatrix();

}

void Ringue::CarregaTexturas()
{
    gMesh.loadTextura(LoadTextureRAW("modelos/ringue.bmp")); 
            texture = LoadTextureRAW("modelos/floor.bmp");

}

GLfloat Ringue::GetXMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].x * gProporcao;
}

GLfloat Ringue::GetYMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].y * gProporcao;
}

GLfloat Ringue::GetZMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].z * gProporcao;
}