

#include "Vec2.h"
#include <math.h>

namespace sge{

Vec2::Vec2(): x(0.0f), y(0.0f){}
Vec2::Vec2(float x, float y): x(x), y(y){}
Vec2::Vec2(const Vec2& copy){set(copy);}
Vec2::~Vec2(){}
    
Vec2 Vec2::fromAngle(float angle){

    Vec2 a=Vec2(sin(angle*0.017453292519943), cos(angle*0.017453292519943));
    return a;
    
}
    
float Vec2::angleRadian(){
    
    float angleInRadians = atan2(y, x);
    return angleInRadians;
}
    
float Vec2::angleDegree(){
    
    float angleInDegrees = (angleRadian() / M_PI) * 180.0;
    return angleInDegrees;
}
    
float Vec2::angleToVec(const Vec2& v){

    Vec2 dif= Vec2(x-v.x,y-v.y);
    float angle= dif.angleDegree();
    
    return angle;
}

void Vec2::clamp(const Vec2& min, const Vec2& max){

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
}


float Vec2::distance(const Vec2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;

    return sqrt(dx * dx + dy * dy);
}

float Vec2::distanceSquared(const Vec2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    return (dx * dx + dy * dy);
}

float Vec2::dot(const Vec2& v) const
{
    return (x * v.x + y * v.y);
}

float Vec2::length() const
{
    return sqrt(x * x + y * y);
}

float Vec2::lengthSquared() const
{
    return (x * x + y * y);
}

void Vec2::negate()
{
    x = -x;
    y = -y;
}

Vec2 Vec2::normalized(){
    
    Vec2 v=Vec2(*this);
    v.normalize();
    
    return v;
}

void Vec2::normalize(){

    float n = x * x + y * y;
    // Already normalized.
    if (n == 1.0f)
        return;

    n = sqrt(n);
    // Too close to zero.
//    if (n < MATH_TOLERANCE)
//        return;

    n = 1.0f / n;
    x *= n;
    y *= n;
}

void Vec2::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
}

void Vec2::scale(const Vec2& scale)
{
    x *= scale.x;
    y *= scale.y;
}

void Vec2::rotate(const Vec2& point, float angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    if (point.x==0 && point.y==0)
    {
        float tempX = x * cosAngle - y * sinAngle;
        y = y * cosAngle + x * sinAngle;
        x = tempX;
    }
    else
    {
        float tempX = x - point.x;
        float tempY = y - point.y;

        x = tempX * cosAngle - tempY * sinAngle + point.x;
        y = tempY * cosAngle + tempX * sinAngle + point.y;
    }
}

void Vec2::set(float x, float y)
{
    this->x = x;
    this->y = y;
}


void Vec2::set(const Vec2& v)
{
    this->x = v.x;
    this->y = v.y;
}

    const Vec2 Vec2::operator+(const Vec2& v) const{
        
        return Vec2(x+v.x, y+v.y);
    }
    
    Vec2& Vec2::operator+=(const Vec2& v){
        
        x+=v.x;
        y+=v.y;
        return *this;
    }
    
    const Vec2 Vec2::operator-(const Vec2& v) const{
    
        return Vec2(x-v.x, y-v.y);
    }
    
    Vec2& Vec2::operator-=(const Vec2& v)
    {
        x-=v.x;
        y-=v.y;
        return *this;
    }
    
    const Vec2 Vec2::operator-() const
    {
        Vec2 result(*this);
        result.negate();
        return result;
    }
    
    const Vec2 Vec2::operator*(float x) const
    {
        Vec2 result(*this);
        result.scale(x);
        return result;
    }
    
    Vec2& Vec2::operator*=(float x)
    {
        scale(x);
        return *this;
    }
    
    const Vec2 Vec2::operator/(const float x) const
    {
        return Vec2(this->x / x, this->y / x);
    }
    
    bool Vec2::operator<(const Vec2& v) const
    {
        if (x == v.x)
        {
            return y < v.y;
        }
        return x < v.x;
    }
    
    bool Vec2::operator==(const Vec2& v) const
    {
        return x==v.x && y==v.y;
    }
    
    bool Vec2::operator!=(const Vec2& v) const
    {
        return x!=v.x || y!=v.y;
    }
    
    const Vec2 operator*(float x, const Vec2& v)
    {
        Vec2 result(v);
        result.scale(x);
        return result;
    }


}
