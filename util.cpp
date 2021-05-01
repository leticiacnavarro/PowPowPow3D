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

    zNear = 50;
    zFar = 100;

    int ponto = pontoOlho; 

    GLfloat pontoFoco[3];

    lutador.DirecaoPrimeiraPessoa(20, pontoFoco);

    gluLookAt(lutador.GetXFromMesh(ponto), lutador.GetYFromMesh(ponto), lutador.GetZFromMesh(ponto),
                pontoFoco[0], pontoFoco[1], lutador.GetZFromMesh(ponto), 
                0,0,1);
}

void Util::CameraPulso(Lutador &lutador)
{
    zNear = 500;
    zFar = 1000;

    int ponto = pontoBraco; 
    int ponto2 = pontoMaoDireita; 
    
    GLfloat braco[3] = {lutador.GetXFromRealMesh(ponto), lutador.GetYFromRealMesh(ponto), lutador.GetZFromRealMesh(ponto)};
    GLfloat mao[3] = {lutador.GetXFromRealMesh(ponto2), lutador.GetYFromRealMesh(ponto2), lutador.GetZFromRealMesh(ponto2)};

    normalize(braco);
    normalize(mao);
    GLfloat up[3];

    cross(mao, braco, up);
    cout << "up: " << up[0] << "-" << up[1] << "-" << up[2] << endl;
    GLfloat pontoFoco[3];
    GLfloat pontoOrigem[3];

    lutador.DirecaoPrimeiraPessoa(20, pontoFoco);
    lutador.DirecaoPrimeiraPessoa(-5, pontoOrigem);

    gluLookAt(lutador.GetXFromRealMesh(ponto), lutador.GetYFromRealMesh(ponto), lutador.GetZFromRealMesh(ponto),
                pontoFoco[0], pontoFoco[1], lutador.GetZFromRealMesh(ponto), 
                up[2],up[0],up[1]);


}
void Util::CameraSuperior(Lutador &lutador){


    zNear = 0;
    zFar = 100;

    GLfloat s = abs(camYXAngle*M_PI/180);
    GLfloat t = abs(camYZAngle*M_PI/180);

    gluLookAt(  lutador.GetXFromMesh(pontoBarriga) - zoom * cos(s) * sin(t),
                lutador.GetYFromMesh(pontoBarriga) - zoom * sin(s) * sin(t),
                lutador.GetZFromMesh(pontoBarriga) + zoom * cos(t),
                lutador.GetXFromMesh(pontoBarriga), lutador.GetYFromMesh(pontoBarriga), lutador.GetZFromMesh(pontoBarriga),
                0, 0, 1);

}

void Util::Iluminacao(Lutador &lutador, Lutador &bot, bool modoNoturno){
    if(modoNoturno)
    {
      
        glDisable (GL_LIGHTING);
        glDisable (GL_LIGHT0);

        GLfloat pontoFoco[3];

        lutador.DirecaoPrimeiraPessoa(20, pontoFoco);

        GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_specular[] = { 0.0, 1.0, 1.0, 1.0 };
        GLfloat light1_position[] = {lutador.GetXFromRealMesh(pontoMeioCabeca), lutador.GetYFromRealMesh(pontoMeioCabeca), lutador.GetZFromRealMesh(pontoMeioCabeca) + 10, 1};
        GLfloat spot_direction[4] = { lutador.GetXFromRealMesh(pontoMeioCabeca), lutador.GetYFromRealMesh(pontoMeioCabeca), lutador.GetZFromRealMesh(pontoMeioCabeca), 1.0f };

        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);

        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50);
        
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light1_position[0],light1_position[1],light1_position[2]);
            glEnd();  
            
        glEnable(GL_LIGHT1);       
        glEnable(GL_LIGHTING);

        bot.DirecaoPrimeiraPessoa(20, pontoFoco);

        GLfloat light2_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light2_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light2_position[] = {bot.GetXFromRealMesh(pontoMeioCabeca), bot.GetYFromRealMesh(pontoMeioCabeca), bot.GetZFromRealMesh(pontoMeioCabeca) + 20, 1};
        GLfloat spot_direction2[4] = {bot.GetXFromRealMesh(pontoMeioCabeca), bot.GetYFromRealMesh(pontoMeioCabeca), bot.GetZFromRealMesh(pontoMeioCabeca), 0.0f };

        glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0);

        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 100.0);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50);
        
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light2_position[0],light2_position[1],light2_position[2]);
            glEnd();  
            
        glEnable(GL_LIGHT2);       
        glEnable(GL_LIGHTING);

    }
    else{
        glDisable (GL_LIGHT1);
        glDisable (GL_LIGHT2);

        glDisable (GL_LIGHTING);

        GLfloat light_position[] = {0, 0, 100, 1};
        glLightfv(GL_LIGHT0,GL_POSITION,light_position);
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light_position[0],light_position[1],light_position[2]);
            glEnd();  
            
        glEnable(GL_LIGHT0);       
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