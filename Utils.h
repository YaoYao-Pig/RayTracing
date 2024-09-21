#ifndef UTILS_H
#define UTILS_H
#include "Vector3.h"
#include"Header.h"
namespace yyz
{
    Vector3 randomInUnitSphere();
    inline float getRandom0to1(){
        return rand()%(RANDOM_N+1)/(float(RANDOM_N+1));
    }
}

#endif