#include"HitableList.h"
using namespace yyz;



bool HitableList::hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const {
    hitRecord tmpRec;
    bool hit_anything =false;
    double closest_so_far = t_max;
    for(int i=0;i<size;++i){
        if(allHitable[i]->hit(r,t_min,closest_so_far,tmpRec)){
            hit_anything = true;
            closest_so_far=tmpRec.t;
            rec=tmpRec;
        }
    }
    return hit_anything;
}