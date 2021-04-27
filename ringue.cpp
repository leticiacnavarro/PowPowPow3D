#include "ringue.h"
#include <math.h>

void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    int pts = 50;
    glColor3f (R, G, B);

    for(unsigned int i = 0; i <= pts; ++i ){

        float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
        float x = radius * sin(angle);
        float y = radius * cos(angle);
        
        glPointSize(3);

        glBegin(GL_POLYGON);
            glVertex3f(x, y, 0.0f);
    }
    glEnd();
}
void Ringue::DesenhaRingue()
{
    glPushMatrix();
        glTranslatef(0, 0, -profundidade);
        gMesh.draw();
    glPopMatrix();

}

