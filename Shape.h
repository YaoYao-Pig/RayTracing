#ifndef SHAPE_H
#define SHAPE_H
#include"Header.h"
#include"Vector3.h"
#include"Ray.h"
#include"Hitable.h"
#include"Material.h"
#include<memory>
namespace yyz{
    

    class Shape{};

    class Sphere :public Shape,public Hitable{
        public:
            
            Sphere(yyz::Vector3 c,float r,Material* m)
                    :center(c),radius(r),material(m){}

            bool hit(const yyz::Ray& r,float t_min,float t_max,OUT hitRecord& rec) const;

            inline yyz::Vector3 getCenter() const {return center;}
            inline float getRadius() const {return radius;}
        private:
            yyz::Vector3 center;
            float radius;
            Material* material;
    };


};

#endif