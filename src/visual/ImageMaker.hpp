#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include "Vector3f.h"
#include "Light.h"
#include "Camera.h"
#include "SceneParser.h"
#include "types.h"

/*
 * Class ImageMaker
 *
 * Constructs and saves images of scenes that include a building model, a sun
 * model, and a complete scene defined by the user. The ImageMaker is
 * constructed with this user-defined base scene. For each image it must be
 * provided a sun position, a building to model, and a resolution. The resulting
 * image is then saved to disk.
 */

class ImageMaker {
    public:
        /*
         * Constructor: ImageMaker
         *
         * Constructs a new ImageMaker object using baseScene as its background
         * scene.
         *
         * Arguments:
         * baseScene - the background scene for all images create by this
         * ImageMaker
         */
        ImageMaker(SceneParser *baseScene);

        ~ImageMaker();

        /*
         * Method: makeImageOfScene
         *
         * Constructs the image of the baseScene with the sun at the given
         * position and the given building inserted into the scene. The image is
         * saved to disk.
         *
         * Arguments:
         * sunPos - position of the sun in the sky
         * building - group of Object3Ds defining the building. Must be an
         * ObjPtr to comply with Group implementation.
         * resolution - the size of the image to produce
         * fileName - where to save the image
         */
        void makeImageOfScene(const Vector3f &sunPos, const ObjPtr building, int resolution, char *fileName);
    private:

        /*
         * Method getPixelColor
         *
         * Calculates the color scene at the hit found for the given ray
         * projected from a camera. If an intersection was found a shader is
         * used. Otherwise, the background color is returned.
         *
         * Arguments:
         * intersection - whether or not the ray hit something
         * hit - the hit object representing what the ray intersected
         * ray - the ray in question
         * scene - the scene the ray is being cast through
         *
         * Returns a Vector3f color resulting from the shading (or the
         * background color, if no intersection.
         */
        Vector3f getPixelColor(bool intersection, Hit *hit, Ray ray, SceneParser *const scene);

        /*
         * Method: readyScene
         *
         * Modifies the baseScene of this object to create a scene including the
         * sun and building provided.
         *
         * Arguments:
         * sun - the directional light representing the sun
         * building - an group of Object3Ds representing the building
         *
         * Returns the conglomerate scene.
         */
        SceneParser* readyScene(Light *sun, ObjPtr building);

        /*
         * Method: makeSun
         *
         * Creates a new directional light at the position provided. Represents
         * the sun in the model.
         *
         * The memory for this directional light is stored in-object and handled
         * by the object.
         *
         * Arguments: 
         * sunPos - the position from which the sun should be shining
         *
         * Returns the sun representation.
         */
        Light* makeSun(const Vector3f &sunPos);

        /*
         * Method: makeImage
         *
         * Saves an image of the scene to the given file at the given
         * resolution.
         *
         * Arguments:
         * scene
         * resolution - a square, resolution x resolution image is produced
         * fileName
         */
        void makeImage(SceneParser *const scene, int resolution, char* fileName);

        Light *sun;
        SceneParser *baseScene;
        SceneParser *completeScene;
};

#endif
