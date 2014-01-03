#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

char* inputFileName = NULL;
char* outputFileName = NULL;
int outputSize[2] = {0, 0};
char* renderMode = "shade";
SceneParser* scene;

float minDepth = 0.0;
float maxDepth = 25.0;

bool renderNormal = false;
char* normalOutputFile = NULL;

// parser
void readArguments(int argc, char* argv[]) {
    int argNum;

    for( argNum = 1; argNum < argc; argNum++ )
    {
        char* arg = argv[argNum];

        if (strcmp(arg, "-input") == 0) {
            // save the input file name
            argNum++;
            inputFileName = argv[argNum];
            cout << "Input File Name: " << inputFileName << endl;
        }
        else if (strcmp(arg, "-output") == 0) {
            // save the output file name
            argNum++;
            outputFileName = argv[argNum];
            cout << "Output File Name: " << outputFileName << endl;
        }
        else if (strcmp(arg, "-size") == 0) {
            // save the size of the image to be generated
            argNum++;
            char* width = argv[argNum];
            outputSize[0] = atoi(width);
            cout << "Output Width: " << outputSize[0] << endl;

            argNum++;
            char* height = argv[argNum];
            outputSize[1] = atoi(height);
            cout << "Output Height: " << outputSize[1] << endl;
        }
        else if(strcmp(arg, "-intersect") == 0) {
            // change the rendering type to intersect
            renderMode = "intersect";
        }
        else if (strcmp(arg, "-depth") == 0) {
            // change the rendering type to depth
            renderMode = "depth";
            argNum++;
            minDepth = atoi(argv[argNum]);
            argNum++;
            maxDepth = atoi(argv[argNum]);
        }
        else if (strcmp(arg, "-shade") == 0) {
            // change the rendering type to shading
            renderMode = "shade";
        }
        else if (strcmp(arg, "-normal") == 0) {
            renderNormal = true;
            argNum++;
            normalOutputFile = argv[argNum];
            cout << "Rendering Normals To File: " << normalOutputFile << endl;
        }
    }
    cout << "Render Mode: " << renderMode << endl;
}

void printVector(Vector3f vec) {
    cout << vec[0] << ", " << vec[1] << ", " << vec[2] << endl;
}

Vector3f drawIntersect(bool intersection, Hit *hit, Vector3f bg) {
    if (intersection) {
        return Vector3f(1.0f, 1.0f, 1.0f);
    }
    else {
        return Vector3f(0.0f, 0.0f, 0.0f);
    }
}

Vector3f drawDepth(bool intersection, Hit *hit, Vector3f bg) {
    float t = hit->getT();
    if (t > maxDepth) {
        return Vector3f(0.0f, 0.0f, 0.0f);
    }
    else if (t < minDepth) {
        return Vector3f(1.0, 1.0, 1.0);
    }
    else {
        float gray = 1.0 - (t-minDepth)/(maxDepth-minDepth);
        return Vector3f(gray, gray, gray);
    }
}

Vector3f drawNormal(bool intersection, Hit *hit, Vector3f bg) {
    if (intersection) {
        Vector3f n = hit->getNormal();
        return Vector3f(abs(n[0]), abs(n[1]), abs(n[2]));
    }
    else {
        return bg;
    }
}

Vector3f drawShade(bool intersection, Hit *hit, Ray ray, Vector3f bg) {
    if (intersection) {
        int i;
        Material *mat = hit->getMaterial();
        Vector3f p = ray.pointAtParameter(hit->getT());
        Vector3f shading;

        // ambient light
        Vector3f ambientLight = scene->getAmbientLight();
        shading = ambientLight * mat->getDiffuseColor(hit);

        for(i = 0; i < scene->getNumLights(); i++) {
            Vector3f dir;
            Vector3f col;
            float distToLight;
            Light* light = scene->getLight(i);
            light->getIllumination(p, dir, col, distToLight);
            Vector3f addition = mat->Shade(ray, *hit, dir, col);
            shading += addition;
        }

        return shading;
    }
    else {
        return bg;
    }
}

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
    int i;
    int j;
    Group* group;
    Camera* camera;

    // read in all user-supplied arguments
    readArguments(argc, argv);

    // parse the scene
    scene = new SceneParser(inputFileName);
    group = scene->getGroup();
    camera = scene->getCamera();
    Image image(outputSize[0], outputSize[1]);
    Image normalImage(outputSize[0], outputSize[1]);

    // iterate over the pixels in the scene, saving each to the image.
    for (i = 0; i < outputSize[0]; i++) {
        for (j = 0; j < outputSize[1]; j++) {
            float x = (float)i/outputSize[0];
            float y = (float)j/outputSize[1];
            Ray ray = camera->generateRay(Vector2f(x, y));
            Hit* hit;
            hit = new Hit();
            Vector3f pixelColor;
            Vector3f bg = scene->getBackgroundColor();
            bool intersection = group->intersect(ray, *hit, camera->getTMin());
            if (strcmp(renderMode, "intersect") == 0) {
                pixelColor = drawIntersect(intersection, hit, bg);
            }
            else if (strcmp(renderMode, "depth") == 0) {
                pixelColor = drawDepth(intersection, hit, bg);
            }
            else if (strcmp(renderMode, "shade") == 0) {
                pixelColor = drawShade(intersection, hit, ray, bg);
            }

            if (renderNormal) {
                normalImage.SetPixel(i, j, drawNormal(intersection, hit, bg));
            }
            image.SetPixel(i, j, pixelColor);
            delete hit;
        }
    }

    // save the image
    image.SaveImage(outputFileName);

    if (renderNormal) {
        normalImage.SaveImage(normalOutputFile);
    }

    // cleanup
    delete scene;

    return 0;
}

