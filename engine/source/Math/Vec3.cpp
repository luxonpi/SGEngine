

#include "Vec3.h"
#include <math.h>
#include "SMath.h"

namespace sge{

Vec3::Vec3(): x(0.0f), y(0.0f), z(0.0f){}
Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z){}
Vec3::Vec3(const Vec3& copy){ set(copy); }
//Vec3::Vec3(float xyz): x(xyz), y(xyz), z(xyz){}

Vec3::~Vec3(){}
    
Vec3 Vec3::reflect(const Vec3& normalVec){
    
    return Vec3(x, y, z) - normalVec * 2.f * this->dot(normalVec);
    
}

void Vec3::clamp(const Vec3& min, const Vec3& max){
    
    // Clamp the x value.
    if (x < min.x)
        x = min.x;
    if (x > max.x)
        x = max.x;

    // Clamp the y value.
    if (y < min.y)
        y = min.y;
    if (y > max.y)
        y = max.y;

    // Clamp the z value.
    if (z < min.z)
        z = min.z;
    if (z > max.z)
        z = max.z;
}

void Vec3::rotate(const Vec3& point, float angle){

    assert(0);
//    Vec3 EulerAngles(0, angle, 0);
//    
//    Vec3 vec=glm::rotate(glm::quat(EulerAngles), glm::vec3(x,y,z));
//
//    set(vec.x, vec.y, vec.z);


}

Vec3 Vec3::cross(const Vec3& v) const{
    
    Vec3 vector;
    vector.x = y*v.z - v.y*z;
    vector.y = v.x*z - x*v.z;
    vector.z = x*v.y - y*v.x;
    
    return vector;

}

float Vec3::distance(const Vec3& v) const{
    
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

float Vec3::distanceSquared(const Vec3& v) const{
    
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return (dx * dx + dy * dy + dz * dz);
}

float Vec3::dot(const Vec3& v) const{
    
    return (x * v.x + y * v.y + z * v.z);
}

float Vec3::length() const{
    
    return sqrt(x * x + y * y + z * z);
}

float Vec3::lengthSquared() const{
    
    return (x * x + y * y + z * z);
}

void Vec3::negate(){
    
    x = -x;
    y = -y;
    z = -z;
}

Vec3 Vec3::normalized(){
        
    Vec3 v=Vec3(*this);
    v.normalize();
        
    return v;
}
    
void Vec3::normalize(){
        
    float n = x * x + y * y+ z * z;
    // Already normalized.
    if (n == 1.0f)
        return;
        
    n = sqrt(n);
    
    if (n < 0.000002)
                return;
    
    n = 1.0f / n;
    x *= n;
    y *= n;
    z *= n;
}
    

void Vec3::scale(float scalar){
    x *= scalar;
    y *= scalar;
    z *= scalar;
}
    
void Vec3::scale(const Vec3& scale){
    
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;
}

void Vec3::set(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}


void Vec3::set(const Vec3& v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}
    
    const Vec3 Vec3::operator+(const Vec3& v) const{
        
        return Vec3(x+v.x, y+v.y, z+v.z);
    }
    
    Vec3& Vec3::operator+=(const Vec3& v){
        
        x+=v.x;
        y+=v.y;
        z+=v.z;

        return *this;
    }
    
    const Vec3 Vec3::operator-(const Vec3& v) const{
        
        return Vec3(x-v.x, y-v.y, z-v.z);
    }
    
    Vec3& Vec3::operator-=(const Vec3& v)
    {
        x-=v.x;
        y-=v.y;
        z-=v.z;

        return *this;
    }
    
    
    const Vec3 Vec3::operator-() const
    {
        Vec3 result(*this);
        result.negate();
        return result;
    }
    
    const Vec3 Vec3::operator*(float x) const
    {
        Vec3 result(*this);
        result.scale(x);
        return result;
    }
    
    Vec3 Vec3::operator*(Vec3 x)
    {
        Vec3 result(*this);
        result.scale(x);
        return result;
    }
    
    Vec3& Vec3::operator*=(float x)
    {
        scale(x);
        return *this;
    }
    
    const Vec3 Vec3::operator/(const float x) const
    {
        return Vec3(this->x / x, this->y / x,  this->z / x);
    }
    
    bool Vec3::operator<(const Vec3& v) const
    {
        if (x == v.x)
        {
            if (y == v.y)
            {
                return z < v.z;
            }
            return y < v.y;
        }
        return x < v.x;
    }
    
    bool Vec3::operator==(const Vec3& v) const
    {
        return x==v.x && y==v.y && z==v.z;
    }
    
    bool Vec3::operator!=(const Vec3& v) const
    {
        return x!=v.x || y!=v.y || z!=v.z;
    }
    
    const Vec3 operator*(float x, const Vec3& v)
    {
        Vec3 result(v);
        result.scale(x);
        return result;
    }


    
}
