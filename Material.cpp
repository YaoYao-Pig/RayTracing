#include"Material.h"
#include"Utils.h"
#include<iostream>
using namespace yyz;

//输入都是unitVector
Vector3 reflect(const Vector3& v,const Vector3& n){
    return v-2*(v.dot(n))*n;
}
bool refract(const Vector3& v,const Vector3& n, float ni_over_nt,Vector3& refracted){
    Vector3 nv=v.normalize();
    float dt=nv.dot(n);
    //判别式
    float discriminant=1.0-pow(ni_over_nt,2)*(1.0-pow(dt,2));
    if(discriminant>0){
        refracted=ni_over_nt*(nv-n*dt)-n*sqrt(discriminant);
        return true;
    }
    else{
        return false;
    }
}

//菲涅尔项的石里克近似
float schlick(float cosine,float ref_idx){
    float r0=(1.0-ref_idx)/(1.0+ref_idx);
    r0=pow(r0,2);
    return r0+(1.0-r0)*pow((1.0-cosine),5);
}

bool Lambertian::scatter(const Ray& ray,const hitRecord& record,OUT Vector3& attenuation,OUT Ray& scattered)const{
    Vector3 target = record.p+record.normal+randomInUnitSphere();
    scattered=Ray(record.p,target-record.p);

    attenuation=albedo;
    return true;

}


bool Metal::scatter(const Ray& ray,const hitRecord& record,OUT Vector3& attenuation,OUT Ray& scattered)const{
    Vector3 reflectRay=reflect(ray.getDirection().normalize(),record.normal) + fuzz*randomInUnitSphere();
    scattered=Ray(record.p,reflectRay);

    attenuation=albedo;
    return (scattered.getDirection().dot(record.normal)>0.0); //反射光线与法线夹角小于90度
}

bool Glass::scatter(const Ray& r_in,const hitRecord& record,OUT Vector3& attenuation,OUT Ray& scattered)const{
    //折射+反射
    Vector3 outward_normal;
    float ni_over_nt;
    Vector3 reflected=reflect(r_in.getDirection(),record.normal);

    attenuation=Vector3(1.0,1.0,1.0);
    
    float reflect_prob;
    float cosine;

    if(r_in.getDirection().dot(record.normal) > 0){
        outward_normal=-record.normal;
        ni_over_nt=ref_idx;
        cosine=ref_idx*r_in.getDirection().dot(record.normal)/r_in.getDirection().length();
    }
    else{
        outward_normal=record.normal;
        ni_over_nt=1.0/ref_idx;

        cosine=-r_in.getDirection().dot(record.normal)/r_in.getDirection().length();
    }



    
    Vector3 refracted;
    if(refract(r_in.getDirection(),outward_normal,ni_over_nt,refracted)){
        reflect_prob=schlick(cosine,ref_idx);
    }
    else{
        reflect_prob=1.0;
    }

    //std::cout<<"ff"<<ff<<std::endl;
    if(getRandom0to1()<reflect_prob){
        scattered=Ray(record.p,reflected);
    }
    else{
        scattered=Ray(record.p,refracted);
    }

    return true;

}