#include"Shape.h"


using namespace yyz;

bool Sphere::hit(const yyz::Ray& r,float t_min,float t_max,hitRecord& rec) const{

    Vector3 oc=r.getOrigin()-center;

    float a=r.getDirection().dot(r.getDirection());

    float b=2.0*(oc.dot(r.getDirection()));

    float c=oc.dot(oc)-radius*radius;

    float delta=b*b-4*a*c;
    if(delta>0.0f){
        float temp=(-b-sqrt(delta))/(2.0*a);
        if(temp<t_max&&temp>t_min){
            rec.t=temp;
            rec.p=r.pointAtParameter(rec.t);
            rec.normal=(rec.p-center).normalize();
            rec.mat_ptr=material;
            return true;
        }
    }
    return false;
}
