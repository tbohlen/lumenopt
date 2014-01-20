#include <cstdio>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>

#include "SceneParser.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

#include "Object3D.h"
#include "Group.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Transform.h"

#define DegreesToRadians(x) ((M_PI * x) / 180.0f)

SceneParser::SceneParser(const char* filename) {

    // initialize some reasonable default values
    camera = NULL;
    background_color = Vector3f(0.5,0.5,0.5);
    ambient_light = Vector3f(0,0,0);

    // parse the file
    assert(filename != NULL);
    const char *ext = &filename[strlen(filename)-4];

    if(strcmp(ext,".txt")!=0){
		printf("wrong file name extension\n");
		exit(0);
	}
    file = fopen(filename,"r");

	if (file == NULL){
		printf("cannot open scene file\n");
		exit(0);
	}
    cout << "Parsing file..." << endl;
    parseFile();
    fclose(file);
    cout << "File closed... " << endl;
    file = NULL;

    // if no lights are specified, set ambient light to white
    // (do solid color ray casting)
    if (lights.size() == 0) {
        printf ("WARNING:    No lights specified\n");
        //ambient_light = Vector3f(1,1,1);
    }
}

SceneParser::SceneParser(const SceneParser& sceneParser) {
    group = sceneParser.getGroup();
    camera = sceneParser.getCamera()->clone();
    background_color = sceneParser.getBackgroundColor();
    ambient_light = sceneParser.getAmbientLight();

    lights = sceneParser.getLights();
    materials = sceneParser.getMaterials();
}

SceneParser::~SceneParser() {
    if (camera != NULL)
        delete camera;
}

// ====================================================================
// ====================================================================

void SceneParser::addLight(const LightPtr light) {
    this->lights.push_back(light);
};

void SceneParser::addObject(const ObjPtr object) {
    if (group) {
        this->group->appendObject(object);
    }
};

void SceneParser::parseFile() {
    //
    // at the top level, the scene can have a camera, 
    // background color and a group of objects
    // (we add lights and other things in future assignments)
    //
    char token[MAX_PARSER_TOKEN_LENGTH];
    while (getToken(token)) {
        cout << "Next Loop" << endl;
        if (!strcmp(token, "PerspectiveCamera")) {
            cout << "Parsing camera" << endl;
            parsePerspectiveCamera();
        } else if (!strcmp(token, "Background")) {
            cout << "Parsing background" << endl;
            parseBackground();
        } else if (!strcmp(token, "Lights")) {
            cout << "Parsing lights" << endl;
            parseLights();
        } else if (!strcmp(token, "Materials")) {
            cout << "Parsing materials" << endl;
            parseMaterials();
        } else if (!strcmp(token, "Group")) {
            cout << "Parsing group" << endl;
            group = parseGroup();
        } else {
            printf ("Unknown token in parseFile: '%s'\n", token);
            exit(0);
        }
    }
    cout << "done" << endl;
}

// ====================================================================
// ====================================================================

void SceneParser::parsePerspectiveCamera() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    // read in the camera parameters
    getToken(token); assert (!strcmp(token, "{"));
    getToken(token); assert (!strcmp(token, "center"));
    Vector3f center = readVector3f();
    getToken(token); assert (!strcmp(token, "direction"));
    Vector3f direction = readVector3f();
    getToken(token); assert (!strcmp(token, "up"));
    Vector3f up = readVector3f();
    getToken(token); assert (!strcmp(token, "angle"));
    float angle_degrees = readFloat();
    float angle_radians = DegreesToRadians(angle_degrees);
    getToken(token); assert (!strcmp(token, "}"));
    camera = new PerspectiveCamera(center,direction,up,angle_radians);
}

void SceneParser::parseBackground() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    // read in the background color
    getToken(token); assert (!strcmp(token, "{"));
    while (1) {
        getToken(token);
        if (!strcmp(token, "}")) {
            break;
        } else if (!strcmp(token, "color")) {
            background_color = readVector3f();
        } else if (!strcmp(token, "ambientLight")) {
            ambient_light = readVector3f();
        } else {
            printf ("Unknown token in parseBackground: '%s'\n", token);
            assert(0);
        }
    }
}

// ====================================================================
// ====================================================================

void SceneParser::parseLights() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));
    // read in the number of objects
    getToken(token); assert (!strcmp(token, "numLights"));
    int num_lights = readInt();
    lights.resize(num_lights);
    // read in the objects
    int count = 0;
    while (num_lights > count) {
        getToken(token);
        if (!strcmp(token, "DirectionalLight")) {
            lights[count] = parseDirectionalLight();
        } else if(strcmp(token, "PointLight")==0)
		{
			lights[count] = parsePointLight();
		}
		else {
            printf ("Unknown token in parseLight: '%s'\n", token);
            exit(0);
        }
        count++;
    }
    getToken(token); assert (!strcmp(token, "}"));
}


LightPtr SceneParser::parseDirectionalLight() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));
    getToken(token); assert (!strcmp(token, "direction"));
    Vector3f direction = readVector3f();
    getToken(token); assert (!strcmp(token, "color"));
    Vector3f color = readVector3f();
    getToken(token); assert (!strcmp(token, "}"));
    return LightPtr( new DirectionalLight(direction,color) );
}
LightPtr SceneParser::parsePointLight() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));
    getToken(token); assert (!strcmp(token, "position"));
    Vector3f position = readVector3f();
    getToken(token); assert (!strcmp(token, "color"));
    Vector3f color = readVector3f();
    getToken(token); assert (!strcmp(token, "}"));
    return LightPtr( new PointLight(position,color) );
}
// ====================================================================
// ====================================================================

void SceneParser::parseMaterials() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));
    // read in the number of objects
    getToken(token); assert (!strcmp(token, "numMaterials"));
    int num_materials = readInt();
    materials.resize(num_materials);
    // read in the objects
    int count = 0;
    while (num_materials > count) {
        getToken(token);
        if (!strcmp(token, "Material") || !strcmp(token, "PhongMaterial")) {
            materials[count] = parseMaterial();
        } else {
            printf ("Unknown token in parseMaterial: '%s'\n", token);
            exit(0);
        }
        count++;
    }
    getToken(token); assert (!strcmp(token, "}"));
}


boost::shared_ptr<Material> SceneParser::parseMaterial() {
    char token[MAX_PARSER_TOKEN_LENGTH];
	char filename[MAX_PARSER_TOKEN_LENGTH];
	filename[0] = 0;
    Vector3f diffuseColor(1,1,1);
    Vector3f specularColor(0,0,0);
	float shininess = 0;
    getToken(token); assert (!strcmp(token, "{"));
    while (1) {
        getToken(token);
        if (strcmp(token, "diffuseColor")==0) {
            diffuseColor = readVector3f();
        }
		else if (strcmp(token, "specularColor")==0) {
            specularColor = readVector3f();
        }
		else if (strcmp(token, "shininess")==0) {
            shininess = readFloat();
        }
		else if (strcmp(token, "texture")==0) {
            getToken(filename);
        }
		else {
            assert (!strcmp(token, "}"));
            break;
        }
    }
    cout << "Making material" << endl;
    boost::shared_ptr<Material> answer( new Material(diffuseColor, specularColor, shininess) );
    cout << "Made material" << endl;
	if(filename[0] !=0){
		answer->loadTexture(filename);
	}
    cout << "returning" << endl;
    return answer;
}

// ====================================================================
// ====================================================================

ObjPtr SceneParser::parseObject(char token[MAX_PARSER_TOKEN_LENGTH]) {
    ObjPtr answer;
    if (!strcmp(token, "Group")) {
        answer = parseGroup();
    } else if (!strcmp(token, "Sphere")) {
        answer = parseSphere();
    } else if (!strcmp(token, "Plane")) {
        answer = parsePlane();
    } else if (!strcmp(token, "Triangle")) {
        answer = parseTriangle();
    } else if (!strcmp(token, "TriangleMesh")) {
        answer = parseTriangleMesh();
    } else if (!strcmp(token, "Transform")) {
        answer = parseTransform();
    } else {
        printf ("Unknown token in parseObject: '%s'\n", token);
        exit(0);
    }
    return answer;
}

// ====================================================================
// ====================================================================

GroupPtr SceneParser::parseGroup() {
    //
    // each group starts with an integer that specifies
    // the number of objects in the group
    //
    // the material index sets the material of all objects which follow,
    // until the next material index (scoping for the materials is very
    // simple, and essentially ignores any tree hierarchy)
    //
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));

    // read in the number of objects
    getToken(token); assert (!strcmp(token, "numObjects"));
    int num_objects = readInt();

    GroupPtr answer( new Group(num_objects) );

    // read in the objects
    int count = 0;
    while (num_objects > count) {
        getToken(token);
        if (!strcmp(token, "MaterialIndex")) {
            // change the current material
            int index = readInt();
            assert (index >= 0 && index <= getNumMaterials());
            current_material = getMaterial(index);
        } else {
            // NOTE: Modified this to convert to a shared_ptr to work with new
            // group implementation
            ObjPtr object =  parseObject(token);
            assert (object != NULL);
            answer->addObject(count, object);

            count++;
        }
    }
    getToken(token); assert (!strcmp(token, "}"));

    // return the group
    return answer;
}

// ====================================================================
// ====================================================================

ObjPtr SceneParser::parseSphere() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));
    getToken(token); assert (!strcmp(token, "center"));
    Vector3f center = readVector3f();
    getToken(token); assert (!strcmp(token, "radius"));
    float radius = readFloat();
    getToken(token); assert (!strcmp(token, "}"));
    assert (current_material);
    return ObjPtr( new Sphere(center,radius,current_material) );
}


ObjPtr SceneParser::parsePlane() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));
    getToken(token); assert (!strcmp(token, "normal"));
    Vector3f normal = readVector3f();
    getToken(token); assert (!strcmp(token, "offset"));
    float offset = readFloat();
    getToken(token); assert (!strcmp(token, "}"));
    assert (current_material);
    return ObjPtr( new Plane(normal,offset,current_material) );
}


ObjPtr SceneParser::parseTriangle() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    getToken(token); assert (!strcmp(token, "{"));
    getToken(token);
    assert (!strcmp(token, "vertex0"));
    Vector3f v0 = readVector3f();
    getToken(token);
    assert (!strcmp(token, "vertex1"));
    Vector3f v1 = readVector3f();
    getToken(token);
    assert (!strcmp(token, "vertex2"));
    Vector3f v2 = readVector3f();
    getToken(token); assert (!strcmp(token, "}"));
    assert (current_material);
    return ObjPtr( new Triangle(v0,v1,v2,current_material) );
}

ObjPtr SceneParser::parseTriangleMesh() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    char filename[MAX_PARSER_TOKEN_LENGTH];
    // get the filename
    getToken(token); assert (!strcmp(token, "{"));
    getToken(token); assert (!strcmp(token, "obj_file"));
    getToken(filename);
    getToken(token); assert (!strcmp(token, "}"));
    const char *ext = &filename[strlen(filename)-4];
    assert(!strcmp(ext,".obj"));
    return ObjPtr( new Mesh(filename,current_material) );
}


ObjPtr SceneParser::parseTransform() {
    char token[MAX_PARSER_TOKEN_LENGTH];
    Matrix4f matrix = Matrix4f::identity();
    ObjPtr object;
    getToken(token); assert (!strcmp(token, "{"));
    // read in transformations: 
    // apply to the LEFT side of the current matrix (so the first
    // transform in the list is the last applied to the object)
    getToken(token);

    while (1) {
        if (!strcmp(token,"Scale")) {
            Vector3f s = readVector3f();
            matrix = matrix * Matrix4f::scaling( s[0], s[1], s[2] );
        } else if (!strcmp(token,"UniformScale")) {
            float s = readFloat();
            matrix = matrix * Matrix4f::uniformScaling( s );
        } else if (!strcmp(token,"Translate")) {
            matrix = matrix * Matrix4f::translation( readVector3f() );
        } else if (!strcmp(token,"XRotate")) {
            matrix = matrix * Matrix4f::rotateX(DegreesToRadians(readFloat()));
        } else if (!strcmp(token,"YRotate")) {
            matrix = matrix * Matrix4f::rotateY(DegreesToRadians(readFloat()));
        } else if (!strcmp(token,"ZRotate")) {
            matrix = matrix * Matrix4f::rotateZ(DegreesToRadians(readFloat()));
        } else if (!strcmp(token,"Rotate")) {
            getToken(token); assert (!strcmp(token, "{"));
            Vector3f axis = readVector3f();
            float degrees = readFloat();
            float radians = DegreesToRadians(degrees);
            matrix = matrix * Matrix4f::rotation(axis,radians);
            getToken(token); assert (!strcmp(token, "}"));
        } else if (!strcmp(token,"Matrix4f")) {
            Matrix4f matrix2 = Matrix4f::identity();
            getToken(token); assert (!strcmp(token, "{"));
            for (int j = 0; j < 4; j++) {
	            for (int i = 0; i < 4; i++) {
                    float v = readFloat();
	                matrix2( i, j ) = v;
                }
            }
            getToken(token); assert (!strcmp(token, "}"));
            matrix = matrix2 * matrix;
        } else {
            // otherwise this must be an object,
            // and there are no more transformations
            object = parseObject(token);
            break;
        }
        getToken(token);
    }

    assert(object != NULL);
    getToken(token); assert (!strcmp(token, "}"));
    return ObjPtr( new Transform(matrix, object) );
}

// ====================================================================
// ====================================================================

int SceneParser::getToken(char token[MAX_PARSER_TOKEN_LENGTH]) {
    // for simplicity, tokens must be separated by whitespace
    assert (file != NULL);
    int success = fscanf(file,"%s ",token);
    if (success == EOF) {
        token[0] = '\0';
        return 0;
    }
    return 1;
}


Vector3f SceneParser::readVector3f() {
    float x,y,z;
    int count = fscanf(file,"%f %f %f",&x,&y,&z);
    if (count != 3) {
        printf ("Error trying to read 3 floats to make a Vector3f\n");
        assert (0);
    }
    return Vector3f(x,y,z);
}


Vector2f SceneParser::readVec2f() {
    float u,v;
    int count = fscanf(file,"%f %f",&u,&v);
    if (count != 2) {
        printf ("Error trying to read 2 floats to make a Vec2f\n");
        assert (0);
    }
    return Vector2f(u,v);
}


float SceneParser::readFloat() {
    float answer;
    int count = fscanf(file,"%f",&answer);
    if (count != 1) {
        printf ("Error trying to read 1 float\n");
        assert (0);
    }
    return answer;
}


int SceneParser::readInt() {
    int answer;
    int count = fscanf(file,"%d",&answer);
    if (count != 1) {
        printf ("Error trying to read 1 int\n");
        assert (0);
    }
    return answer;
}
