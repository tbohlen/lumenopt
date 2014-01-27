#include "Light.hpp"

////////////////////////////////////////////////////////////////////////////////
// DirectionalLight Class Implementation
////////////////////////////////////////////////////////////////////////////////

DirectionalLight::DirectionalLight( const Vector3f& d, const Vector3f& c )
{
    direction = d.normalized();
    color = c;
}

DirectionalLight::~DirectionalLight()
{

}
///@param p unsed in this function
///@param distanceToLight not well defined because it's not a point light
void DirectionalLight::getIllumination( const Vector3f& p, Vector3f& dir, Vector3f& col, float& distanceToLight ) const
{
    // the direction to the light is the opposite of the
    // direction of the directional light source
    dir = -direction;
    col = color;
}

////////////////////////////////////////////////////////////////////////////////
// PointLight Class Implementation
////////////////////////////////////////////////////////////////////////////////

PointLight::PointLight( const Vector3f& p, const Vector3f& c )
{
    position = p;
    color = c;
}

PointLight::~PointLight()
{

}

void PointLight::getIllumination( const Vector3f& p, Vector3f& dir, Vector3f& col, float& distanceToLight ) const
{
    // the direction to the light is the opposite of the
    // direction of the directional light source
    dir = (position-p);
    dir = dir/dir.abs();
    col = color;
}
