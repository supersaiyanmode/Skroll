#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>
#include <iostream>

class Vector3D{
    double array[3];
    double &x,&y,&z;
public:
    Vector3D();
    Vector3D(double,double,double);
    Vector3D(const std::vector<double>&);
    
    Vector3D& normalise();
    double magnitude() const;
    
    Vector3D operator+(const Vector3D&);
    Vector3D operator-(const Vector3D&);
    Vector3D operator*(const Vector3D&);
    Vector3D operator-();
    
    double const& operator[] (unsigned) const;
    double& operator[] (unsigned); 
    
    Vector3D& operator=(const Vector3D&);
    
    friend std::ostream& operator<<(std::ostream&, const Vector3D&);
};

#endif //VECTOR3D_H