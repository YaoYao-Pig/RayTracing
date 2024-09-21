#ifndef RAY_H
#define RAY_H
#include "Vector3.h"

namespace yyz
{
    class Ray{
        public:
            Ray()=default;
            Ray(const Vector3& _origin, const Vector3& _direction);
            Vector3 getOrigin() const;
            Vector3 getDirection() const;
            Vector3 pointAtParameter(float t) const;
        private:
            Vector3 origin;
            Vector3 direction;
    };

};// namespace yyz




#endif