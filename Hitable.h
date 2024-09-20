#ifndef HITABLE_H
#define HITABLE_H
#include"vector3.h"
#include"Ray.h"
#include<vector>
namespace yyz
{
    struct hitRecord
    {
        float t;
        // 碰撞点
        yyz::Vector3 p;
        // 碰撞点法线
        yyz::Vector3 normal;
    };
    class Hitable
    {
        public:
            virtual bool hit(const yyz::Ray &r, float t_min, float t_max, hitRecord &rec) const = 0;
            
    };

    
}

#endif // HITABLE_H