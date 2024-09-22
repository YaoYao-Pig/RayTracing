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

vector<Hitable*> randomScene(){
    vector<Hitable*>  world;

    // 地表材质：散射光材质，灰色
    Material* ground_material = new Lambertian(Color3(0.5, 0.5, 0.5));
    // 添加一个特别大的球作为地表
    world.push_back(new Sphere(Position3(0,-1000,0), 1000, ground_material));

    // 创建最多22*22个随机小球，即最多484个随机小球
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            // 随机一个选择材质的浮点数，主要用于随机不同材质的球的概率
            auto choose_mat = getRandom0to1();
            // 随机当前小球的中心位置
            Position3 center(a + 0.9*getRandom0to1(), 0.2, b + 0.9*getRandom0to1());

            // 如果中心位置不太靠世界坐标原点左右
            if ((center - Position3(4, 0.2, 0)).length() > 0.9) {
                Material* sphere_material;

                // 如果随机材质浮点数小于0.8，即创建散射材质，即80%的概率 
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color3::random() * Color3::random();
                    sphere_material = new Lambertian(albedo);
                    world.push_back(new Sphere(center, 0.2, sphere_material));
                }
                // 如果随机材质浮点数小于0.95，即创建金属材质，即15%的概率 
                else if (choose_mat < 0.95) {
                    // metal
                    Vector3 albedo = Color3::random(0.5, 1);
                    float fuzz = getRandom(0, 0.5);
                    sphere_material = new Metal(albedo, fuzz);
                    world.push_back(new Sphere(center, 0.2, sphere_material));
                }
                // 剩下的5%的概率创建玻璃球 
                else {
                    // glass
                    sphere_material = new Glass(1.5);
                    world.push_back(new Sphere(center, 0.2, sphere_material));
                }
            }
        }
    }

    // 玻璃大球
    auto material1 =new Glass(1.5);
    world.push_back(new Sphere(Position3(0, 1, 0), 1.0, material1));

    // 散射大球
    auto material2 = new Lambertian(Color3(0.4, 0.2, 0.1));
    world.push_back(new Sphere(Position3(-4, 1, 0), 1.0, material2));

    // 金属大球
    auto material3 = new Metal(Color3(0.7, 0.6, 0.5), 0.0);
    world.push_back(new Sphere(Position3(4, 1, 0), 1.0, material3));

    return world;
}


int main(){
    int nx=1200;
    int ny=600;
    int ns=1;//抗锯齿采样次数
    srand(time(NULL));


    Position3 origin=Position3(13,2,3);
    Position3 lookAt=Position3(0,0,0);
    Vector3 vup=Vector3(0,1,0);
    float aspect_ratio=1.5;

    //float aspect_ratio,float aperture,float focus_dist
    float dist_to_focus=10;
    auto aperture=0.1;

    Camera camera(20,aspect_ratio,origin,lookAt,vup,aperture,dist_to_focus);

    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    //创建球体
    vector<Hitable*> list=randomScene();
    Hitable* world=new HitableList(list);
    //遍历像素
    for(int j=ny-1;j>=0;j--){
        for(int i=0;i<nx;i++){
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