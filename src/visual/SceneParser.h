#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

#include <cassert>
#include <vecmath.h>

#include "SceneParser.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Object3D.h"
#include "Mesh.hpp"
#include "Group.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Transform.h"
#include "types.h"

/*
class Camera;
class Light;
class Material;
class Object3D;
class Group;
class Sphere;
class Plane;
class Triangle;
class Transform;
*/
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

    vector<LightPtr> getLights() const {
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
        return this->materials.size();
    }

    vector < boost::shared_ptr < Material > > getMaterials() const {
        return this->materials;
    }

    boost::shared_ptr<Material> getMaterial( int i ) const
    {
        assert( i >= 0 && i < materials.size() );
        return materials[i];
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
    boost::shared_ptr<Material> parseMaterial();

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
    std::vector< boost::shared_ptr< Material > > materials;
    boost::shared_ptr<Material> current_material;
    GroupPtr group;
};

#endif // SCENE_PARSER_H
