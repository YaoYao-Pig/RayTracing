#include<iostream>
#include"Ray.h"
#include"Vector3.h"
#include"Shape.h"
#include"HitableList.h"
#include"Camera.h"
#include"Header.h"
#include<math.h>
#include<random>
#include<time.h>
#include"Utils.h"
#include"Material.h"
using namespace std;
using namespace yyz;


/*

g++ -c Ray.cpp -o Ray.o
g++ -c Utils.cpp -o Utils.o
g++ -c Material.cpp  -o Material.o
g++ -c Camera.cpp -o Camera.o
g++ -c HitableList.cpp -o HitableList.o
g++ -c Shape.cpp -o Shape.o
g++ -c main.cpp -o main.o
g++ Ray.o Utils.o Material.o Camera.o HitableList.o Shape.o main.o -o main.exe
*/



int num=0;
Color3 getColor(const yyz::Ray& r,Hitable* world,int depth){
    hitRecord hitRecord;
    bool isHit=world->hit(r,0.001,MAXFLOAT,hitRecord);

    //取正数最小解
    if(isHit) {
        Ray scattered;
        Vector3 attenuation;
        if(depth<50 && hitRecord.mat_ptr->scatter(r,hitRecord,attenuation,scattered)){
            //cout<<"num:"<<depth<<endl;
            return attenuation*getColor(scattered,world,depth+1);
        }
        else{
            return Vector3(0,0,0);
        }
        
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
    int ns=50;//抗锯齿采样次数
    srand(time(NULL));

    Camera camera(Position3(0,0,0),Vector3(4.0,0.0,0.0),Vector3(0.0,2.0,0.0),Position3(-2.0,-1.0,-1.0));

    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";

    //从左下角开始，向右，向上，分别增加4.0和2.0，相当于一个坐标轴的范围
    
    


    //创建球体
    vector<Hitable*> list;
    list.push_back(new Sphere(Position3(0,0,-1),0.5,new Lambertian(Vector3(0.8,0.3,0.3))));
    list.push_back(new Sphere(Position3(0,-100.5,-1),100,new Lambertian(Vector3(0.8,0.8,0.0))));
    list.push_back(new Sphere(Position3(1,0,-1),0.5,new Metal(Vector3(0.8,0.6,0.2),0.3f)));
    //list.push_back(new Sphere(Position3(-1,0,-1),0.5,new Glass(1.5)));
    list.push_back(new Sphere(Position3(-1,0,-1),-0.45,new Glass(1.5)));
    Hitable* world=new HitableList(list);


    //遍历像素
    for(int j=ny-1;j>=0;j--){
        //std::cout<<"cow:"<<j<<endl;
        for(int i=0;i<nx;i++){
           // std::cout<<"row:"<<i<<endl;
            Color3 color;
            //反走样,增加采样次数；
            //在一个像素点的范围内，发射更多不同方向的Ray，然后再把这些不同方向的Ray的Color取平均
            for(int s=0;s<ns;s++){
                float u=float(i+getRandom0to1())/float(nx);
                float v=float(j+getRandom0to1())/float(ny);
                //发射Ray
                Ray ray=camera.getRay(u,v);
                color+=getColor(ray,world,0);
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