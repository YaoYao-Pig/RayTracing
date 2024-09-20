#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"
#include "Vector3.h"

class Camera{
public:
    Camera(const yyz::Vector3 _origin,yyz::Vector3 _horizontal,yyz::Vector3 _vertical,yyz::Vector3 _llc):
        origin(_origin),horizontal(_horizontal),vertical(_vertical),lowerLeftCorner(_llc){

        }
                    //      x       y
    yyz::Ray getRay(double u,double v){
        return yyz::Ray(origin,(lowerLeftCorner+u*horizontal+v*vertical)-origin);
    }
private:
    yyz::Vector3 origin;

    yyz::Vector3 direction;

    yyz::Vector3 lowerLeftCorner;
    yyz::Vector3 horizontal;
    yyz::Vector3 vertical;




};



#endif