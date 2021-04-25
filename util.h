#ifndef UTIL_H
#define	UTIL_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>

#include "lutador.h"

using namespace std;

class Util
{
    GLfloat gX;
    GLfloat gY;


private:
    void CameraPrimeiraPessoa(Lutador &lutador);
    void CameraPulso(Lutador &lutador);
    void CameraSuperior(Lutador &lutador);
public:
    Util(){}

    GLint lastX = 0;
    GLint lastY = 0;

    GLint zoom = 150;
    GLint camAngle = 60;

    GLfloat camYXAngle = 0;
    GLfloat camYZAngle = 0;

    void ProcessaCamera(int toggle, Lutador &lutador);
    GLint GetCamAngle();
    void Camera();
    void Iluminacao(Lutador &lutador, Lutador &bot, bool modoNoturno);
    void DrawAxes(double size);

};

#endif	/* UTIL_H */
