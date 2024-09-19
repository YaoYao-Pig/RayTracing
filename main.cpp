#include<iostream>
#include"Ray.h"
#include"Vector3.h"
using namespace std;

yyz::Vector3 color(const yyz::Ray& r){

}


int main(){
    int nx=200;
    int ny=100;


    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    for(int j=ny-1;j>=0;j--){
        for(int i=0;i<nx;i++){
            yyz::Vector3 color(float(i)/float(nx), float(j)/float(ny),0.2); 
            int ir=int(255.99*color.r());
            int ig=int(255.99*color.g());
            int ib=int(255.99*color.b());
            cout<<ir<<" "<<ig<<" "<<ib<<"\n";
        }   
    }


    return 0;
}