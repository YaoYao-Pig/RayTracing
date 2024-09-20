#ifndef HitableLIST_H
#define HitableLIST_H
#include "Hitable.h"
namespace yyz{
    //自带了一个Z-buffer，针对每个ray的hit，会去在所有的Hitable对象当中找到最小的t值，以及它的碰撞点信息，并且返回
    class HitableList:public Hitable{
        public:
            HitableList(){}
            HitableList(std::vector<Hitable *>p):allHitable(p),size(allHitable.size()){}
            virtual bool hit(const yyz::Ray &r, float t_min, float t_max, hitRecord &rec) const override;

            std::vector<Hitable*> allHitable;
            int size;
        
    };
}

#endif