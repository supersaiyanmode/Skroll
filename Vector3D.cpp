#include <cmath>
#include "Vector3D.h"

Vector3D::Vector3D():x(array[0]), y(array[1]), z(array[2]){
    for (int i=0; i<3; array[i++]=0);
}
Vector3D::Vector3D(double x_,double y_,double z_):x(array[0]), y(array[1]), z(array[2]){
    array[0] = x_;
    array[1] = y_;
    array[2] = z_;
}
Vector3D::Vector3D(const std::vector<double>& v):x(array[0]), y(array[1]), z(array[2]){
    for (int i=0; i<3; i++)
        array[i]=v[i];
}
Vector3D& Vector3D::operator=(const Vector3D& other){
    for (int i=0; i<3; i++)
        array[i]=other.array[i];
    return *this;
}

Vector3D& Vector3D::normalise(){
    double mag = magnitude();
    for (int i=0; i<3; i++)
        array[i]/=mag;
    return *this;
}

double Vector3D::magnitude() const{
    return std::sqrt(array[0]*array[0] + array[1]*array[1] + array[2]*array[2]);
}
    
Vector3D Vector3D::operator+(const Vector3D& other) const{
    return Vector3D(array[0]+other.array[0], array[1]+other.array[1], array[2]+other.array[2]);
}

Vector3D Vector3D::operator-(const Vector3D& other) const{
    return Vector3D(array[0]-other.array[0], array[1]-other.array[1], array[2]-other.array[2]);
}

double const& Vector3D::operator[](unsigned index) const{
    return array[index];
}
double& Vector3D::operator[] (unsigned index){
    return array[index];
}

Vector3D Vector3D::operator*(const Vector3D& other) const{
    return Vector3D(array[1]*other.array[2]-array[2]*other.array[1], array[2]*other.array[0]-array[0]*other.array[2], array[0]*other.array[1]-array[1]*other.array[0]);
}

Vector3D Vector3D::operator*(double other) const{
    return Vector3D(other*array[0], other*array[1], other*array[2]);
}

Vector3D Vector3D::operator-() const{
    return Vector3D(-array[0],-array[1],-array[2]);
}

std::ostream& operator<<(std::ostream& out, const Vector3D& v){
    return out<<"("<<v[0]<<","<<v[1]<<","<<v[2]<<")";
}

Vector3D Vector3D::getRatioVector(const Vector3D& v1, const Vector3D& v2, double ratio){
    if (ratio > 1.0)
        ratio = 1.0;
    if (ratio < 0.0)
        ratio = 0.0;
    return v1 + (v2-v1)*ratio;
}