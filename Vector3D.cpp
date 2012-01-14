#include <cmath>
#include <iostream>
#include "Vector3D.h"

Vector3D::Vector3D():x(0.0),y(0.0),z(0.0){}
Vector3D::Vector3D(double x_,double y_,double z_):x(x_), y(y_), z(z_){}
Vector3D::Vector3D(const std::vector<double>& v):x(v[0]), y(v[1]), z(v[2]){}

void Vector3D::normalise(){
    double mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
}

double Vector3D::magnitude() const{
    return std::sqrt(x*x + y*y + z*z);
}
    
Vector3D Vector3D::operator+(const Vector3D& other){
    return Vector3D(x+other.x, y+other.y, z+other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other){
    return Vector3D(x-other.x, y-other.y, z-other.z);
}

double& Vector3D::operator[](int index){
    switch(index){
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
    std::cout<<"All the best!"<<std::endl;
    //let it segfault here.
}

Vector3D Vector3D::operator*(const Vector3D& other){
    return Vector3D(y*other.z-z*other.y, z*other.x-x*other.z, x*other.y-y*other.x);
}

Vector3D Vector3D::operator-(){
    return Vector3D(-x,-y,-z);
}
