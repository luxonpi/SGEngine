

#ifndef SGENGINE_VEC3_H
#define SGENGINE_VEC3_H

// derived from the gameplay engine
// https://github.com/gameplay3d/GamePlay

#include <iostream>
#include <string>
#include <math.h>

namespace sge{
    
    class Vec3{
        
    public:
        
        float x;
        float y;
        float z;

        //Vec3(float xyz);
        Vec3();
        Vec3(float x, float y, float z);
        Vec3(const Vec3& vec);
        ~Vec3();
        
        Vec3 cross(const Vec3& v) const;
        void clamp(const Vec3& min, const Vec3& max);
        float distance(const Vec3& v) const;
        float distanceSquared(const Vec3& v) const;
        float dot(const Vec3& v) const;
        float length() const;
        float lengthSquared() const;
        void negate();
        Vec3 normalized();
        void normalize();
        void scale(float scalar);
        void scale(const Vec3& scale);
        void rotate(const Vec3& point, float angle);
        
        void set(float x, float y, float z);
        void set(const Vec3& v);
        
        Vec3 reflect(const Vec3& normalVec);
        
        const Vec3 operator+(const Vec3& v) const;
        Vec3& operator+=(const Vec3& v);
        const Vec3 operator-(const Vec3& v) const;
        Vec3& operator-=(const Vec3& v);
        const Vec3 operator-() const;
        const Vec3 operator*(float x) const;
        
        inline Vec3 operator*(const Vec3& v) const{
        
            return Vec3(v.x*x, v.y*y, v.z*z);
        
        }
        
     

        Vec3& operator*=(float x);
        Vec3 operator*(Vec3 x);

        const Vec3 operator/(float x) const;
        bool operator<(const Vec3& v) const;
        bool operator==(const Vec3& v) const;
        bool operator!=(const Vec3& v) const;
        
        friend std::ostream &operator<<( std::ostream &output,
                                        const Vec3& v )
        {
            output << "( " << v.x << ", " << v.y << ", " << v.z << " )";
            return output;
        }
        
        void print(std::string name){
            
            std::cout<< name << ": " << *this << std::endl;
            
        }
        
    };
    
    
    
}

inline sge::Vec3 pow(sge::Vec3 vec3, float power){

    return sge::Vec3(powf(vec3.x, power),powf(vec3.y, power),powf(vec3.z, power));
    
}


#endif
