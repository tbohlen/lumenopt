#include "imageMaker.hpp"
#include "Image.h"
#include <string.h>
#include "hit.h"
#include "Ray.h"
#include "Group.h"
#include "SceneParser.h"
#include "Light.h"
#include "Camera.h"

using namespace std;

ImageMaker::ImageMaker(SceneParser *baseScene) : baseScene(baseScene), completeScene(NULL) {

}

ImageMaker::~ImageMaker() {
    if(completeScene != NULL) {
        delete completeScene;
    }
}

void ImageMaker::makeImageOfScene(Vector3f &sunPos, const ObjPtr building, int resolution, const char *filename) {
    sunPos.negate();
    LightPtr sun = this->makeSun(sunPos);
    SceneParser *scene = this->readyScene(sun, building);
    this->makeImage(scene, resolution, filename);
}

LightPtr ImageMaker::makeSun(const Vector3f &sunPos) {
    return LightPtr( new DirectionalLight(sunPos, Vector3f(1., 1., 1.)) );
}

SceneParser* ImageMaker::readyScene(LightPtr sun, const ObjPtr building) {
    if(this->completeScene != NULL) {
        delete this->completeScene;
    }
    this->completeScene = new SceneParser(*this->baseScene);
    this->completeScene->addLight(sun);
    this->completeScene->addObject(building);
    return completeScene;
}

void ImageMaker::makeImage(SceneParser *const scene, int resolution, const char *filename) {

    GroupPtr group = scene->getGroup();
    Camera *camera = scene->getCamera();
    Image image(resolution, resolution);
    Vector3f pixelColor;
    float x;
    float y;
    int i;
    int j;

    if (group) {
        // iterate over the pixels in the scene, saving each to the image.
        for (i = 0; i < resolution; i++) {

            x = (float)i/resolution;

            for (j = 0; j < resolution; j++) {
                y = (float)j/resolution;
                Ray ray = camera->generateRay(Vector2f(x, y));
                Hit* hit = new Hit();
                bool intersection = group->intersect(ray, *hit, camera->getTMin());

                pixelColor = this->getPixelColor(intersection, hit, ray, scene);

                image.SetPixel(i, j, pixelColor);
                delete hit;
            }
        }

        // save the image
        image.SaveImage(filename);
    }
}

Vector3f ImageMaker::getPixelColor(bool intersection, Hit *hit, Ray ray, SceneParser *const scene) {
    if (intersection) {
        int i;
        Material* mat = hit->getMaterial();
        Vector3f p = ray.pointAtParameter(hit->getT());
        Vector3f shading;

        // ambient light
        Vector3f ambientLight = scene->getAmbientLight();
        shading = ambientLight * mat->getDiffuseColor(hit);

        for(i = 0; i < scene->getNumLights(); i++) {
            Vector3f dir;
            Vector3f col;
            float distToLight;
            LightPtr light = scene->getLight(i);
            light->getIllumination(p, dir, col, distToLight);
            Vector3f addition = mat->Shade(ray, *hit, dir, col);
            shading += addition;
        }

        return shading;
    }
    else {
        return scene->getBackgroundColor();
    }
}
