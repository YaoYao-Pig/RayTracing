#include<iostream>
#include"Ray.h"
#include"Vector3.h"
using namespace std;
using namespace yyz;
Color3 getColor(const yyz::Ray& r){
    Vector3 unitDirection=r.getDirection().normalize();
    float t=0.5*(unitDirection.y()+1.0);
    return (1.0-t)*Vector3(1.0,1.0,1.0)+t*Vector3(0.5,0.7,1.0);
}


int main(){
    int nx=200;
    int ny=100;


    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    Position3 eye(0,0,0);

    Position3 lowerLeftCorner(-2.0,-1.0,-1.0);
    //从左下角开始，向右，向上，分别增加4.0和2.0，相当于一个坐标轴的范围
    Vector3 horizontal(4.0,0.0,0.0);
    Vector3 vertical(0.0,2.0,0.0);
    

    
    for(int j=ny-1;j>=0;j--){
        for(int i=0;i<nx;i++){
            float u=float(i)/float(nx);
            float v=float(j)/float(ny);

            //发射Ray
            Vector3 dir=lowerLeftCorner+u*horizontal+v*vertical;
            Ray ray(eye,dir);
            Color3 color=getColor(ray);
            int ir=int(255.99*color.r());
            int ig=int(255.99*color.g());
            int ib=int(255.99*color.b());
            cout<<ir<<" "<<ig<<" "<<ib<<"\n";
        }   
    }


    return 0;
}