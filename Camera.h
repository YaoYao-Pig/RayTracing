#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"
#include "Vector3.h"
#include"Header.h"
#include<math.h>
#include"Utils.h"
namespace yyz{
    class Camera{
    public:
        Camera(float _fov, float _aspect,Position3 _origin,Position3 _lookAt,Vector3 _up,
            float aperture,float focus_dist) 
            : fov(_fov), aspect(_aspect),origin(_origin),z_near(-1){

            //正交基
            lookDirection=-(_lookAt-origin).normalize();
            right=_up.cross(lookDirection).normalize();
            up=lookDirection.cross(right).normalize();

            //Z_near<0，右手系
            float theta = fov*M_PI/180.0;
            float half_height=tan(theta/2)*focus_dist;

            float half_width=half_height*aspect;

            

            horizontal=focus_dist*half_width*right;
            vertical=focus_dist*half_height*up;
            lowerLeftCorner=origin-horizontal/2-vertical/2-focus_dist*lookDirection;
            lens_radius=aperture/2;
        } 
        //      x       y
        yyz::Ray getRay(double u, double v)const
        {
            Vector3 rd=lens_radius*randomInUnitDisk();
            Vector3 offset=right*rd.x()+up*rd.x();

            return yyz::Ray(origin+offset, 
                (lowerLeftCorner + u * horizontal + v * vertical) - origin-offset);
        }

    private:
        yyz::Vector3 origin;



        yyz::Vector3 lookDirection;
        yyz::Vector3 up;
        yyz::Vector3 right;

        yyz::Position3 lowerLeftCorner;
        yyz::Vector3 horizontal;
        yyz::Vector3 vertical;
        float fov;
        float aspect;
        float z_near;

        float lens_radius;


    };
}

#endif