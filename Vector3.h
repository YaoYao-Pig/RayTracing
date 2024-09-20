#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include <vector>
namespace yyz
{



    class Vector3
    {
    public:
        Vector3():e(3){};
        Vector3(float x, float y, float z) : e{x, y, z} {}
        Vector3(const Vector3 &v) : e{v.e[0], v.e[1], v.e[2]} {}
        inline float &x() { return e[0]; }
        inline float &y() { return e[1]; }
        inline float &z() { return e[2]; }
        inline float &r() { return e[0]; }
        inline float &g() { return e[1]; }
        inline float &b() { return e[2]; }
        inline float x() const { return e[0]; }
        inline float y() const { return e[1]; }
        inline float z() const { return e[2]; }
        inline float r() const { return e[0]; }
        inline float g() const { return e[1]; }
        inline float b() const { return e[2]; }
        ~Vector3() = default;
        const Vector3 &operator+() const;
        Vector3 operator-() const;

        Vector3 operator+(const Vector3 &v) const;
        Vector3 operator-(const Vector3 &v) const;
        Vector3 operator*(const Vector3 &v) const;
        Vector3 operator*(float s) const;
        Vector3 operator/(const Vector3 &v) const;
        Vector3 operator/(float s) const;
        float operator[](int index) const;
        float &operator[](int index);

        Vector3 &operator+=(const Vector3 &v);
        Vector3 &operator-=(const Vector3 &v);
        Vector3 &operator*=(float s);
        Vector3 &operator*=(const Vector3 &v);
        Vector3 &operator/=(float s);
        Vector3 &operator/=(const Vector3 &v);

        float dot(const Vector3 &v) const;
        Vector3 cross(const Vector3 &v) const;
        
        float length() const;
        float squaredLength() const;
        float makeUnitVector();
        

        inline Vector3 normalize()const{
            return Vector3(*this/length());
        }

    private:
        std::vector<float> e;//{0.0f,0.0f,0.0f};
    };

    //成员函数实现：
    inline const Vector3 &Vector3::operator+() const { return *this; }
    inline Vector3 Vector3::operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    inline Vector3 Vector3::operator+(const Vector3 &v) const { return Vector3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]); }
    inline Vector3 Vector3::operator-(const Vector3 &v) const { return Vector3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]); }
    inline Vector3 Vector3::operator*(const Vector3 &v) const { return Vector3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]); }
    inline Vector3 Vector3::operator*(float s) const { return Vector3(e[0] * s, e[1] * s, e[2] * s); }
    inline Vector3 Vector3::operator/(const Vector3 &v) const { return Vector3(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]); }
    inline Vector3 Vector3::operator/(float s) const { return Vector3(e[0] / s, e[1] / s, e[2] / s); }
    
    
    inline float Vector3::operator[](int index) const { return e[index]; }
    inline float &Vector3::operator[](int index) { return e[index]; }
    inline Vector3 &Vector3::operator+=(const Vector3 &v)
    {
        *this = *this + v;
        return *this;
    }
    inline Vector3 &Vector3::operator-=(const Vector3 &v)
    {
        *this = *this - v;
        return *this;
    }

    inline Vector3 &Vector3::operator*=(float s)
    {
        e[0] *= s;
        e[1] *= s;
        e[2] *= s;
        return *this;
    }

    inline Vector3 &Vector3::operator*=(const Vector3 &v)
    {
        *this = *this * v;
        return *this;
    }

    inline Vector3 &Vector3::operator/=(float s)
    {
        e[0] /= s;
        e[1] /= s;
        e[2] /= s;
        return *this;
    }

    inline Vector3 &Vector3::operator/=(const Vector3 &v)
    {
        *this = *this / v;
        return *this;
    }

    inline float Vector3::length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline float Vector3::squaredLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }


    inline float Vector3::dot(const Vector3 &v)const
    {
        return this->x() * v.x() + this->y() * v.y() + this->z() * v.z();
    }

    inline Vector3 Vector3::cross(const Vector3 &v)const
    {
        return Vector3(this->y() * v.z() - this->z() * v.y(),
                       this->z() * v.x() - this->x() * v.z(),
                       this->x() * v.y() - this->y() * v.x());
    }

    //非成员函数实现：

    inline Vector3 operator*(float s,const Vector3 &v){
        return Vector3(v*s);
    }


    using Position3=Vector3;
    using Direction3=Vector3;
    using Color3=Vector3;

}

#endif