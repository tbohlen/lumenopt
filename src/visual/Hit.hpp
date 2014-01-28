#ifndef HIT_H
#define HIT_H

#include "vecmath/vecmath.h"
#include <iostream>

class Material;
class Ray;

class Hit
{
public:

    // constructors
    Hit();

    Hit( float _t, Material* m, const Vector3f& n );

    Hit( const Hit& h );

    // destructor
    ~Hit();

    float getT() const;

    Material* getMaterial() const;

    const Vector3f& getNormal() const;

    void set( float _t, Material* m, const Vector3f& n );

	void setTexCoord(const Vector2f &coord);


	bool hasTex;
	Vector2f texCoord;
private:
	float t;
    Material* material;
    Vector3f normal;

};

inline std::ostream& operator << ( std::ostream &os, const Hit& h ) {
    os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
    return os;
}

#endif // HIT_H
