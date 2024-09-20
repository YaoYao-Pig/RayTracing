#include<iostream>
#include"Ray.h"
#include"Vector3.h"
#include"Shape.h"
#include"HitableList.h"
#include"Camera.h"
#include<math.h>
#include<random>
#include<time.h>
using namespace std;
using namespace yyz;

#define MAXFLOAT 3.402823466e+38F

#define RANDOM_N  999
/*
g++ -c Ray.cpp -o Ray.o
g++ -c Camera.cpp -o Camera.o
g++ -c HitableList.cpp -o HitableList.o
g++ -c Shape.cpp -o Shape.o
g++ -c main.cpp -o main.o
g++ Ray.o Camera.o HitableList.o Shape.o main.o -o main.exe
*/

Vector3 randomInUnitSphere(){
    Vector3 p;
    do{
        float r[3];
        for(int i=0;i<3;++i){
            srand(time(NULL));
            r[i]=rand()%(RANDOM_N+1)/(float(RANDOM_N+1));
        }
        p=2.0*Vector3(r[0],r[1],r[2])-Vector3(1,1,1);
    }while(p.dot(p)>=1.0);
    return p;
}


Color3 getColor(const yyz::Ray& r,Hitable* world){
    hitRecord hitRecord;
    bool isHit=world->hit(r,0.001,MAXFLOAT,hitRecord);

    //取正数最小解
    if(isHit) {
        Vector3 target=hitRecord.p+hitRecord.normal+randomInUnitSphere();
        return 0.5*getColor(Ray(hitRecord.p,target-hitRecord.p),world);
    }
    else{
        Vector3 unitDirection=r.getDirection().normalize();
        float t=0.5*(unitDirection.y()+1.0);
        return (1.0-t)*Vector3(1.0,1.0,1.0)+t*Vector3(0.5,0.7,1.0);
    }
    
}


int main(){
    int nx=200;
    int ny=100;
    int ns=100;//抗锯齿采样次数
        
    Camera camera(Position3(0,0,0),Vector3(4.0,0.0,0.0),Vector3(0.0,2.0,0.0),Position3(-2.0,-1.0,-1.0));

    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";

    //从左下角开始，向右，向上，分别增加4.0和2.0，相当于一个坐标轴的范围
    
    


    //创建球体
    vector<Hitable*> list;
    list.push_back(new Sphere(Position3(0,0,-1),0.5f));
    list.push_back(new Sphere(Position3(0,-100.5,-1),100));

    Hitable* world=new HitableList(list);


    //遍历像素
    for(int j=ny-1;j>=0;j--){
        for(int i=0;i<nx;i++){
            
            Color3 color;
            //反走样,增加采样次数；
            //在一个像素点的范围内，发射更多不同方向的Ray，然后再把这些不同方向的Ray的Color取平均
            for(int s=0;s<ns;s++){
                srand(time(NULL));
                float tmp=rand()%(RANDOM_N+1)/(float(RANDOM_N+1));
                float u=float(i+tmp)/float(nx);
                srand(time(NULL));
                tmp=rand()%(RANDOM_N+1)/(float(RANDOM_N+1));
                float v=float(j+tmp)/float(ny);
                //发射Ray
                Ray ray=camera.getRay(u,v);
                color+=getColor(ray,world);
            }
            
            color/=float(ns);
            int ir=int(255.99*color.r());
            int ig=int(255.99*sqrt(color.g()));
            int ib=int(255.99*sqrt(color.b()));
            cout<<ir<<" "<<ig<<" "<<ib<<"\n";
        }   
    }


    return 0;
}