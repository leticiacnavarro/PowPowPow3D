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
      //  cout << modoNoturno << endl;

    if(modoNoturno){
         GLfloat light_position[] = { lutador.GetX(), lutador.GetY(), 50.0, 1.0 };
         glLightfv(  GL_LIGHT0, GL_SPOT_DIRECTION, light_position);
        // GLfloat light_position2[] = { bot.GetX(), bot.GetY(), 50.0, 1.0 };
        // glLightfv(  GL_LIGHT1, GL_SPOT_DIRECTION, light_position2);
        
    }
    else{
            //Define e desenha a fonte de luz
        GLfloat light_position[] = {10, 10, 80, 1};
        glLightfv(GL_LIGHT0,GL_POSITION,light_position);
        glDisable(GL_LIGHTING);
            glPointSize(15);
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
                glVertex3f(light_position[0],light_position[1],light_position[2]);
            glEnd();    
        glEnable(GL_LIGHTING);
        // GLfloat light_position[] = {0, 0, 200.0, 1.0 };
        // glLightfv(  GL_LIGHT0, GL_POSITION, light_position);
    }
    // GLfloat light_position[] = {0, 0, 200.0, 1.0 };
    // glLightfv(  GL_LIGHT0, GL_POSITION, light_position);
    
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