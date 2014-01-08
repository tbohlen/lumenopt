#include "imageMaker.hpp"
#include "Image.h"
#include <string.h>
#include "hit.h"

using namespace std;

ImageMaker::ImageMaker(SceneParser *baseScene) : sun(NULL), baseScene(baseScene), completeScene(NULL) {

}

ImageMaker::~ImageMaker() {
    if(sun != NULL) {
        delete sun;
    }
    if(baseScene != NULL) {
        delete baseScene;
    }
    if(completeScene != NULL) {
        delete completeScene;
    }
}

void ImageMaker::makeImageOfScene(const Vector3f &sunPos, const ObjPtr building, int resolution, char *fileName) {
    Light *sun = this->makeSun(sunPos);
    SceneParser *scene = this->readyScene(sun, building);
    this->makeImage(scene, resolution, fileName);
}

Light* ImageMaker::makeSun(const Vector3f &sunPos) {
    if(this->sun != NULL) {
        delete this->sun;
    }
    this->sun = new DirectionalLight(sunPos, Vector3f(1, 1, 0.8));
    return this->sun;
}

SceneParser* ImageMaker::readyScene(Light *sun, const ObjPtr building) {
    if(completeScene != NULL) {
        delete completeScene;
    }
    completeScene = new SceneParser(*this->baseScene);
    completeScene->addLight(sun);
    completeScene->addObject(building);
    return completeScene;
}

void ImageMaker::makeImage(SceneParser *const scene, int resolution, char *fileName) {

    Group *group = scene->getGroup();
    Camera *camera = scene->getCamera();
    Image image(resolution, resolution);
    Vector3f pixelColor;
    float x;
    float y;
    int i;
    int j;

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
    image.SaveImage(fileName);
}

Vector3f ImageMaker::getPixelColor(bool intersection, Hit *hit, Ray ray, SceneParser *const scene) {
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
        return scene->getBackgroundColor();
    }
}
