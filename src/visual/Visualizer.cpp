#include "visual/Visualizer.hpp"
#include <assert.h>
#include "vecmath/vecmath.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

Visualizer::Visualizer(vector<vector<vector<bool> > > building, float xSize, float ySize, float zSize) : building(building), xSize(xSize), ySize(ySize), zSize(zSize) {
}

void Visualizer::draw() {

    int i;
    int j;
    int k;

    // draw each particle
    glPushMatrix();

    glShadeModel(GL_SMOOTH);
    GLfloat floorColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glBegin(GL_TRIANGLES);

    for (i = 0; i < this->building.size(); i++) {
        for (j = 0; j < this->building[0].size(); j++) {
            for (k = 0; k < this->building[0][0].size(); k++) {
                if (this->building[i][j][k]) {
                    // then build the triangle
                    float left = i * this->xSize;
                    float right = (i + 1) * this->xSize;
                    float height = j * this->ySize;
                    float back = k * this->zSize;
                    float front = (k + 1) * this->zSize;

                    Vector3f leftFront(left, height, front);
                    Vector3f leftBack(left, height, back);
                    Vector3f rightFront(right, height, front);
                    Vector3f rightBack(right, height, back);

                    // first triangle
                    glNormal3f(0., 1., 0.);
                    glVertex3f(leftBack[0], leftBack[1],leftBack[2]);

                    glNormal3f(0., 1., 0.);
                    glVertex3f(leftFront[0], leftFront[1],leftFront[2]);

                    glNormal3f(0., 1., 0.);
                    glVertex3f(rightFront[0], rightFront[1],rightFront[2]);

                    // second triangle
                    glNormal3f(0., 1., 0.);
                    glVertex3f(leftBack[0], leftBack[1],leftBack[2]);

                    glNormal3f(0., 1., 0.);
                    glVertex3f(rightFront[0], rightFront[1],rightFront[2]);

                    glNormal3f(0., 1., 0.);
                    glVertex3f(rightBack[0], rightBack[1],rightBack[2]);

                }
            }
        }
    }

    glEnd();

    glPopAttrib();

    glPopMatrix();
}
