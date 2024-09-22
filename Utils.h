#ifndef UTILS_H
#define UTILS_H
#include "Vector3.h"
#include"Header.h"
#include<random>
namespace yyz
{
    Vector3 randomInUnitSphere();
    Vector3 randomInUnitDisk();
    inline float getRandom0to1(){
        return rand()%(RANDOM_N+1)/(float(RANDOM_N+1));
    }

    inline float getRandom(float start,float end){
        return getRandom0to1()*(end-start)+start;
    }
}

#endif