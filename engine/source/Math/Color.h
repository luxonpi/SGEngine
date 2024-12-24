

#ifndef SGENGINE_COLOR_H
#define SGENGINE_COLOR_H

#include <iostream>
#include "Vec3.h"
#include "Vec4.h"

namespace sge {
    
class Color{
    
private:
    
    void checkColor();

  
public:
    
    bool operator==(const Color& c) const;

    
    float r;
    float g;
    float b;
    float a;
    
    Color();
    Color(float r, float g, float b , float a);
    Color(const std::string& hex);
    
    void setHex(std::string hex);
    void setColor(float r, float g, float b , float a);
    
    static Color interpolate(Color color1, float p , Color color2);
    
    std::string getHex() const;
    
    Vec3 getVec3();
    Vec4 getVec4();

    static Color white;
    static Color black;
    static Color grey;
    static Color blue;
    static Color red;
    static Color green;
    static Color yellow;
    static Color cyan;
    static Color purble;
    static Color clear;

    static Color randomDebugColor();
    
};

}

#endif
