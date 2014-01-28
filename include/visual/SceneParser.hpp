#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

#include "types.hpp"
#include <vector>
#include "vecmath/vecmath.h"
#include "Material.hpp"

class Camera;
class Object3D;
class Group;
class Sphere;
class Plane;
class Triangle;
class Transform;
class Light;

#define MAX_PARSER_TOKEN_LENGTH 100

class SceneParser
{
public:

    SceneParser( const char* filename );
    SceneParser( const SceneParser& sceneParser );
    ~SceneParser();

    Camera* getCamera() const
    {
        return camera;
    }

    Vector3f getBackgroundColor() const
    {
        return background_color;
    }

    Vector3f getAmbientLight() const
    {
        return ambient_light;
    }

    std::vector<LightPtr> getLights() const {
        return this->lights;
    }

    int getNumLights() const
    {
        return this->lights.size();
    }

    LightPtr getLight( int i ) const
    {
        assert( i >= 0 && i < lights.size() );
        return lights[i];
    }

    int getNumMaterials() const
    {
        return this->num_materials;
    }

    Material* getMaterial( int i ) const
    {
        assert( i >= 0 && i < this->num_materials );
        return &materials[i];
    }

    GroupPtr getGroup() const
    {
        return group;
    }

    void addLight(const LightPtr light);

    void addObject(const ObjPtr object);

private:

    SceneParser()
    {
        assert( false );
    }

    void parseFile();
    void parsePerspectiveCamera();
    void parseBackground();
    void parseLights();
    LightPtr parseDirectionalLight();
	LightPtr parsePointLight();
    void parseMaterials();
    Material* parseMaterial();

    ObjPtr parseObject( char token[ MAX_PARSER_TOKEN_LENGTH ] );
    GroupPtr parseGroup();
    ObjPtr parseSphere();
    ObjPtr parsePlane();
    ObjPtr parseTriangle();
    ObjPtr parseTriangleMesh();
    ObjPtr parseTransform();

    int getToken( char token[ MAX_PARSER_TOKEN_LENGTH ] );
    Vector3f readVector3f();
    Vector2f readVec2f();
    float readFloat();
    int readInt();

    FILE* file;
    Camera* camera;
    Vector3f background_color;
    Vector3f ambient_light;
    std::vector<LightPtr> lights;
    Material* materials;
    int num_materials;
    Material* current_material;
    GroupPtr group;
};

#endif // SCENE_PARSER_H
