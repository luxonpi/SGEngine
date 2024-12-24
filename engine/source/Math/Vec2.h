

#ifndef SGENGINE_VEC2_H
#define SGENGINE_VEC2_H

// derived from the gameplay engine
// https://github.com/gameplay3d/GamePlay

#include <iostream>
#include <string>

namespace sge{

class Vec2{
    
public:

    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
    Vec2(const Vec2& vec);
    ~Vec2();
    
    static Vec2 fromAngle(float angle);

    void clamp(const Vec2& min, const Vec2& max);
    float distance(const Vec2& v) const;
    float distanceSquared(const Vec2& v) const;
    float dot(const Vec2& v) const;
    float length() const;
    float lengthSquared() const;
    
    float angleRadian();
    float angleDegree();
    float angleToVec(const Vec2& v);
    
    void negate();
    Vec2 normalized();
    void normalize();
    void scale(float scalar);
    void scale(const Vec2& scale);
    void rotate(const Vec2& point, float angle);

    void set(float x, float y);
    void set(const Vec2& v);

    const Vec2 operator+(const Vec2& v) const;
    Vec2& operator+=(const Vec2& v);
    const Vec2 operator-(const Vec2& v) const;
    Vec2& operator-=(const Vec2& v);
    const Vec2 operator-() const;
    const Vec2 operator*(float x) const;
    Vec2& operator*=(float x);
    const Vec2 operator/(float x) const;
    bool operator<(const Vec2& v) const;
    bool operator==(const Vec2& v) const;
    bool operator!=(const Vec2& v) const;
    
    friend std::ostream &operator<<( std::ostream &output,
                                    const Vec2& v )
    {
        output << "( " << v.x << ", " << v.y << " )";
        return output;
    }
    
    void print(std::string name){
        
        std::cout<< name << ": " << *this << std::endl;
        
    }

};



}


#endif
