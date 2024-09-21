#include"Utils.h"
#include "Vector3.h"
#include "Header.h"


yyz::Vector3 yyz::randomInUnitSphere()
{
    yyz::Vector3 p;
        do
        {
            float r[3];
            for (int i = 0; i < 3; ++i)
            {

                r[i] = getRandom0to1();
            }
            p = 2.0 * yyz::Vector3(r[0], r[1], r[2]) - yyz::Vector3(1, 1, 1);
        } while (p.dot(p) >= 1.0);
        return p;
}