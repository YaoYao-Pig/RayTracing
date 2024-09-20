#include"Ray.h"
using namespace yyz;

Ray::Ray(const Vector3 &_origin, const Vector3 &_direction) : origin(_origin), direction(_direction) {}

Vector3 Ray::getOrigin() const
{
    return origin;
}

Vector3 Ray::getDirection() const
{
    return direction;
}

Vector3 Ray::pointAtParameter(float t) const
{
    return origin + direction * t;
}