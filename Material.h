#ifndef MATERIAL_H
#define MATERIAL_H

#include"Ray.h"
#include"Hitable.h"
namespace yyz{
    class Material{
        public:
            /*
                Ray ray:入射的射线
                hitRecord& 碰撞点信息
                attenuation：碰撞后rgb的衰减值
                scatterd：碰撞后的散射方向
            */
            
            virtual bool scatter(const Ray& ray,const hitRecord& record,OUT Vector3& attenuation,OUT Ray& scattered)const =0;
    };

    class Lambertian:public Material{
        public:
            Lambertian(const Vector3& a):albedo(a){}


            virtual bool scatter(const Ray& ray,const hitRecord& record,OUT Vector3& attenuation,OUT Ray& scattered)const override;

        private:
            yyz::Vector3 albedo;
    };

    class Metal:public Material{
        public:
            Metal(const Vector3&a,float f):albedo(a),fuzz(f<1?f:1){}

            virtual bool scatter(const Ray& ray,const hitRecord& record,OUT Vector3& attenuation,OUT Ray& scattered)const override;



        private:
            Vector3 albedo;
            //扰动半径，镜面反射会在这个半径内抖动，达到镜面的模糊效果
            float fuzz;
        
    };

    class Glass:public Material{
        public:
            Glass(float ri):ref_idx(ri){}

            virtual bool scatter(const Ray& r_in,const hitRecord& record,OUT Vector3& attenuation,OUT Ray& scattered)const override;


        private:
            float ref_idx;
    };
}





#endif