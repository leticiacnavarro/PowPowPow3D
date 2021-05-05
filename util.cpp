#include "util.h"

//Funcao auxiliar para normalizar um vetor a/|a|
void normalize(float a[3])
{
    double norm = sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

//Funcao auxiliar para fazer o produto vetorial entre dois vetores a x b = out
void cross(float a[3], float b[3], float out[3])
{
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}

void Util::ProcessaCamera(int toggle, Lutador &lutador)
{
    if (toggle == 0){
        CameraPrimeiraPessoa(lutador);
    }
    else if(toggle == 1){
        CameraPulso(lutador);
    }
    else if(toggle == 2){
        CameraSuperior(lutador);
    }
}

GLint Util::GetCamAngle(){
    return camAngle;
}

void Util::CameraPrimeiraPessoa(Lutador &lutador){

    int ponto = pontoOlho; 

    GLfloat pontoFoco[3];

    lutador.DirecaoPrimeiraPessoa(20, pontoFoco);

    gluLookAt(lutador.GetXFromMesh(ponto), lutador.GetYFromMesh(ponto), lutador.GetZFromMesh(ponto),
                pontoFoco[0], pontoFoco[1], lutador.GetZFromMesh(ponto), 
                0,0,1);
}

void Util::CameraPulso(Lutador &lutador)
{
    int ponto = pontoBraco; 
    int ponto2 = pontoMao2; 
    
    GLfloat mao1[3] = {lutador.GetXFromRealMesh(ponto), lutador.GetYFromRealMesh(ponto), lutador.GetZFromRealMesh(ponto)};
    GLfloat mao2[3] = {lutador.GetXFromRealMesh(ponto2), lutador.GetYFromRealMesh(ponto2), lutador.GetZFromRealMesh(ponto2)};

    GLfloat normal[3] = {lutador.GetXMeshNormal(pontoMaoDireita), lutador.GetYMeshNormal(pontoMaoDireita), lutador.GetZMeshNormal(pontoMaoDireita)};
    

    normalize(mao1);
    normalize(mao2);
    GLfloat up[3];

    cross(mao1, mao2, up);

    GLfloat pontoFoco[3];
    GLfloat pontoOrigem[3];

    lutador.DirecaoPrimeiraPessoa(40, pontoFoco);
    lutador.DirecaoPrimeiraPessoa(-5, pontoOrigem);

    gluLookAt(lutador.GetXFromRealMesh(ponto), lutador.GetYFromRealMesh(ponto), lutador.GetZFromRealMesh(pontoMaoDireita),
                pontoFoco[0], pontoFoco[1], lutador.GetZFromRealMesh(pontoMaoDireita), 
                0, 0, 1);


}
void Util::CameraSuperior(Lutador &lutador){

    GLfloat s = abs(camYXAngle*M_PI/180);
    GLfloat t = abs(camYZAngle*M_PI/180);

    gluLookAt(  lutador.GetXFromMesh(pontoBarriga) - zoom * cos(s) * sin(t),
                lutador.GetYFromMesh(pontoBarriga) - zoom * sin(s) * sin(t),
                lutador.GetZFromMesh(pontoBarriga) + zoom * cos(t),
                lutador.GetXFromMesh(pontoBarriga), lutador.GetYFromMesh(pontoBarriga), lutador.GetZFromMesh(pontoBarriga),
                0, 0, 1);

}

void Util::Iluminacao(Lutador &lutador, Lutador &bot, bool modoNoturno, Ringue &ringue, bool apaga){
    if(modoNoturno)
    {
      
        glDisable (GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);    
        glDisable(GL_LIGHT2);    
        glDisable(GL_LIGHT3);  

        glPushMatrix();
            
            glTranslatef(lutador.GetXFromRealMesh(pontoMeioCabeca), lutador.GetYFromRealMesh(pontoMeioCabeca), lutador.altura + (lutador.altura * 0.5));
            GLfloat pontoFoco[3];

            lutador.DirecaoPrimeiraPessoa(20, pontoFoco);

            GLfloat light1_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
            GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
            GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
            GLfloat light1_position[] = {0,0,0, 1};
            GLfloat spot_direction[] = { 0,0,-1, 1};

            glLightfv(GL_LIGHT4, GL_AMBIENT, light1_ambient);
            glLightfv(GL_LIGHT4, GL_DIFFUSE, light1_diffuse);
            glLightfv(GL_LIGHT4, GL_SPECULAR, light1_specular);
            glLightfv(GL_LIGHT4, GL_POSITION, light1_position);
            glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 20.0);
            glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 2);
            
            glDisable(GL_LIGHTING);
                glPointSize(15);
                glColor3f(1.0,1.0,0.0);
                glBegin(GL_POINTS);
                    glVertex3f(light1_position[0],light1_position[1],light1_position[2]);
                glEnd();

        glPopMatrix();
        glPushMatrix();

        bot.DirecaoPrimeiraPessoa(20, pontoFoco);
            glTranslatef(bot.GetXFromRealMesh(pontoMeioCabeca), bot.GetYFromRealMesh(pontoMeioCabeca), bot.altura + (bot.altura * 0.5));
            //glTranslatef(0, 0, 0);

        glLightfv(GL_LIGHT5, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT5, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT5, GL_SPECULAR, light1_specular);
        glLightfv(GL_LIGHT5, GL_POSITION, light1_position);

        glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 15.0);
        glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 2.0);
        
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light1_position[0],light1_position[1],light1_position[2]);
            glEnd();  
        glPopMatrix();
            glEnable(GL_LIGHT4);
            glEnable(GL_LIGHT5);  
       
        glEnable(GL_LIGHTING);

    }
    else{
        glDisable (GL_LIGHT4);
        glDisable (GL_LIGHT5);

        glDisable (GL_LIGHTING);
        GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat alturaLuz = lutador.altura * 1.5;
        GLfloat light_position[] = {ringue.GetXMeshPuro(pontoCanto1), ringue.GetYMeshPuro(pontoCanto1), alturaLuz, 1};
        glLightfv(GL_LIGHT0,GL_POSITION,light_position);
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light_position[0],light_position[1],light_position[2]);
            glEnd();  

        GLfloat light_position2[] = {ringue.GetXMeshPuro(pontoCanto2), ringue.GetYMeshPuro(pontoCanto2), alturaLuz, 1};
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT1,GL_POSITION,light_position2);
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light_position2[0],light_position2[1],light_position2[2]);
            glEnd();  

        GLfloat light_position3[] = {ringue.GetXMeshPuro(pontoCanto3), ringue.GetYMeshPuro(pontoCanto3), alturaLuz, 1};
        glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT2,GL_POSITION,light_position3);
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light_position3[0],light_position3[1],light_position3[2]);
            glEnd();  
        GLfloat light_position4[] = {ringue.GetXMeshPuro(pontoCanto4), ringue.GetYMeshPuro(pontoCanto4), alturaLuz, 1};

     //   GLfloat light_position4[] = {0, 0, 10, 1};
        glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT3,GL_POSITION,light_position4);
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light_position4[0],light_position4[1],light_position4[2]);
            glEnd();  
                        
            glEnable(GL_LIGHT0);    
            glEnable(GL_LIGHT1);    
            glEnable(GL_LIGHT2);    
            glEnable(GL_LIGHT3);   
 

        glEnable(GL_LIGHTING);

    }
}

void Util::DrawAxes(double size)
{
    GLfloat color_r[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat color_g[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat color_b[] = { 0.0, 0.0, 1.0, 1.0 };

    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

    //x axis red
    glPushMatrix();
        glColor3fv(color_r);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();

    //y axis green
    glPushMatrix();
        glColor3fv(color_g);
        glRotatef(90,0,0,1);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();

    //z axis blue
    glPushMatrix();
        glColor3fv(color_b);
        glRotatef(-90,0,1,0);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix(); 
        glPopAttrib();
   
}

