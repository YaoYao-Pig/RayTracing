#ifndef RAY_H
#define RAY_H
#include "Vector3.h"

namespace yyz
{
    class Ray{
        public:
            Ray(const Vector3& _origin, const Vector3& _direction);
            Vector3 getOrigin() const;
            Vector3 getDirection() const;
            Vector3 pointAtParameter(float t) const;
        private:
            Vector3 origin;
            Vector3 direction;
    };

    Ray::Ray(const Vector3& _origin, const Vector3& _direction) : 
        origin(_origin), direction(_direction){}


    Vector3 Ray::getOrigin() const{
        return origin;
    }

    Vector3 Ray::getDirection() const{
        return direction;
    }

    Vector3 Ray::pointAtParameter(float t) const{
        return origin +  direction*t;
    }

};// namespace yyz




#endif