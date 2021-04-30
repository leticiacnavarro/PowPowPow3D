#include "util.h"

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

    zNear = -20;
    zFar = 1000;

    GLfloat pontoFocoTras[3];
    GLfloat pontoFocoFrente[3];

    lutador.DirecaoPrimeiraPessoa(-150, pontoFocoTras);
    lutador.DirecaoPrimeiraPessoa(20, pontoFocoFrente);

    gluLookAt(lutador.GetXFromMesh(pontoOlho), lutador.GetYFromMesh(pontoOlho), lutador.GetZFromMesh(pontoOlho),
                pontoFocoFrente[0], pontoFocoFrente[1], lutador.GetZFromMesh(pontoOlho), 
                0,0,1);
}

void Util::CameraPulso(Lutador &lutador)
{
    zNear = 0;
    zFar = 1000;

    int ponto = pontoBraco; 

    GLfloat pontoFoco[3];

    lutador.DirecaoPrimeiraPessoa(20, pontoFoco);

    gluLookAt(lutador.GetXFromMesh(ponto), lutador.GetYFromMesh(ponto), lutador.GetZFromMesh(ponto),
                pontoFoco[0], pontoFoco[1], lutador.GetZFromMesh(ponto), 
                0,0,1);


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
        glDisable (GL_LIGHT1);
        glDisable (GL_LIGHTING);

        GLfloat light_position[] = {10, 10, 50, 1};
        glLightfv(GL_LIGHT0,GL_POSITION,light_position);
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light_position[0],light_position[1],light_position[2]);
            glEnd();  
            
    //    glEnable(GL_LIGHT0);       
        glEnable(GL_LIGHTING);

    }
    else{
       
        glDisable (GL_LIGHTING);
        glDisable (GL_LIGHT0);

        GLfloat pontoFoco[3];

    lutador.DirecaoPrimeiraPessoa(20, pontoFoco);

        GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_position[] = {lutador.GetXFromRealMesh(pontoOlho), lutador.GetYFromRealMesh(pontoOlho), lutador.GetZFromRealMesh(pontoOlho) + 20, 1};
        GLfloat spot_direction[4] = { lutador.GetXFromRealMesh(pontoOlho), lutador.GetYFromRealMesh(pontoOlho), lutador.GetZFromRealMesh(pontoOlho), 0.0f };

        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);

        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 100.0);
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

        // GLfloat target[3] = { 0.0f, 0.0f, 0.0f };
        // GLfloat color[3] = { 1.0f, 1.0f, 1.0f };
        // GLfloat cutoff(5.0f);
        // GLfloat exponent(15.0f);
        // GLfloat direction[3];
        // GLfloat position[4] = { lutador.GetX(), lutador.GetY(), lutador.GetZ(), 0.0f };

        // direction[0] = target[0] - lutador.GetX();
        // direction[1] = target[1] - lutador.GetY();
        // direction[2] = target[2] - lutador.GetZ();  

        // glEnable(GL_LIGHT1);

        // glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
        // glLightfv(GL_LIGHT1, GL_SPECULAR, color);
        // glLightfv(GL_LIGHT1, GL_POSITION, position);

        // glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
        // glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
        // glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);
        // glEnable(GL_LIGHTING);

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