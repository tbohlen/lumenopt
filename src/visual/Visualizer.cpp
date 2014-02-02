#include "visual/Visualizer.hpp"
#include <assert.h>
#include "vecmath/vecmath.h"
#include "model/building.hpp"
#include "model/sun.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

Visualizer::Visualizer(Building *building, Sun *sun) : building(building), sun(sun) {
    this->sunIndex = 0;
    this->xSize = building->getXSize();
    this->ySize = building->getYSize();
    this->zSize = building->getZSize();
}

void Visualizer::draw() {

    int i;
    int j;
    int k;

    coord sunDir = sun->getDirectionForIndex(this->sunIndex);

    // draw each particle
    glPushMatrix();

    glShadeModel(GL_SMOOTH);
    GLfloat floorColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shadowColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glBegin(GL_TRIANGLES);

    for (i = 0; i < this->building->getDimension(); i++) {
        for (j = 0; j < this->building->getSecondDimension(i); j++) {
            for (k = 0; k < this->building->getThirdDimension(i, j); k++) {
                if (this->building->floorExists(i, j, k)) {
                    // set the material
                    indices ind;
                    ind.x = i;
                    ind.y = j;
                    ind.z = k;

                    bool shaded = this->building->inShade(ind, sunDir);
                    if (shaded) {
                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, shadowColor);
                    }
                    else {
                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorColor);
                    }

                    glPushAttrib(GL_ALL_ATTRIB_BITS);

                    // then build the triangle
                    float left = i * this->xSize;
                    float right = (i + 1) * this->xSize;
                    float back = j * this->ySize;
                    float front = (j + 1) * this->ySize;
                    float height = k * this->zSize;

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

                    // pop the material
                    glPopAttrib();
                }
            }
        }
    }
    glEnd();

    glPopMatrix();
}

void Visualizer::nextSunPosition() {
    this->sunIndex = (this->sunIndex + 1) % sun->getNumberOfSamples();
    cout << "Switching sun position to " << this->sunIndex << endl;
}
