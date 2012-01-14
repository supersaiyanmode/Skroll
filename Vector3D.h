#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>
struct Vector3D{
    double x,y,z;
    
    Vector3D();
    Vector3D(double,double,double);
    Vector3D(const std::vector<double>&);
    
    void normalise();
    double magnitude() const;
    
    Vector3D operator+(const Vector3D&);
    Vector3D operator-(const Vector3D&);
    Vector3D operator*(const Vector3D&);
    Vector3D operator-();
    
    double& operator[](int);
};

#endif //VECTOR3D_H