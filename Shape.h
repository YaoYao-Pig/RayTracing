#ifndef SHAPE_H
#define SHAPE_H
#include"Vector3.h"
#include"Ray.h"
#include"Hitable.h"
namespace yyz{
    

    class Shape{};

    class Sphere :public Shape,public Hitable{
        public:
            
            Sphere(yyz::Vector3 c,float r):center(c),radius(r){}

            bool hit(const yyz::Ray& r,float t_min,float t_max,hitRecord& rec) const;

            inline yyz::Vector3 getCenter() const {return center;}
            inline float getRadius() const {return radius;}
        private:
            yyz::Vector3 center;
            float radius;
    };


};

#endif