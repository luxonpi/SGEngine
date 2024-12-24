

#include "Color.h"
#include <sstream>

namespace sge {

using namespace std;

Color Color::white=Color(255,255,255,1);
Color Color::black=Color(0,0,0,1);
Color Color::grey=Color(150,150,150,1);
Color Color::blue=Color(0,0,255,1);
Color Color::red=Color(255,0,0,1);
Color Color::green=Color(0,255,0,1);
Color Color::yellow=Color(255,255,0,1);
Color Color::cyan=Color(0,255,255,1);
Color Color::purble=Color(255,0,255,1);
Color Color::clear=Color(0,0,0,0);

    // TO DO COPY OPERATOR
    
Color Color::randomDebugColor(){

    int r=rand()%6;
    
    switch (r) {
        case 0: return Color::blue;
            break;
        case 1: return Color::red;
            break;
        case 2: return Color::green;
            break;
        case 3: return Color::yellow;
            break;
        case 4: return Color::cyan;
            break;
        case 5: return Color::purble;
            break;
            
        default:
            break;
    }

    return Color::white;

}

Color::Color(){

    a=1;
    r=1;
    g=1;
    b=1;

}
    
Vec3 Color::getVec3(){
    
    return Vec3(r, g, b);

}
    
Vec4 Color::getVec4(){
    
    return Vec4(r, g, b, a);
}

Color::Color(float r, float g, float b , float a){

    this->a=a;
    this->r=r/255.;
    this->g=g/255.;
    this->b=b/255.;

    checkColor();
}
    
bool Color::operator==(const Color& c) const{
    
        return r==c.r && g==c.g && b==c.b && a==c.a;

}

//Color::Color(float r, float g, float b , float a){
//
//    this->a=a;
//    this->r=r;
//    this->g=g;
//    this->b=b;
//
//    checkColor();
//}

void Color::setColor(float r, float g, float b , float a){

    this->a=a;
    this->r=r;
    this->g=g;
    this->b=b;
    
    checkColor();
}

void Color::setHex(std::string hex){

    // http://www.coderslexicon.com/code/76/
    
    int* rgb = new int[3];
    stringstream ss;
    string str;
    
    // Drop a hash if the value has one
    if (hex[0] == '#') {
        hex.erase(0,1);
    }
    
    int size = (int) hex.size();
    
    for (int i = 0; i < 3; i++) {
        
        // Determine 3 or 6 character format.
        if (size == 3) { str = string(2, hex[i]); }
        else if (size == 6) { str = hex.substr(i * 2, 2); }
        else { break; }
        
        ss << std::hex << str;
        ss >> rgb[i];
        ss.clear();
    }
    
    
    r=rgb[0]/255.;
    g=rgb[1]/255.;
    b=rgb[2]/255.;
    

    a=1;
    
    delete [] rgb;
    
    checkColor();


}

Color::Color(const std::string& hex){

    setHex(hex);
    
 }

std::string Color::getHex() const{
    
    int rgbNum = (((int)(r*255) & 0xff) << 16)| (((int)(g*255) & 0xff) << 8) | ((int)(b*255) & 0xff);
        
    static std::string hexDigits = "0123456789ABCDEF";
        
    std::string rgb;
    for (int i=(3*2) - 1; i>=0; i--) {
        rgb += hexDigits[((rgbNum >> i*4) & 0xF)];
    }
        
    return rgb;

}

Color Color::interpolate(Color color1, float p , Color color2){

    float nr=color1.r*p+color2.r*(1-p);
    float ng=color1.g*p+color2.g*(1-p);
    float nb=color1.b*p+color2.b*(1-p);
    float na=color1.a*p+color2.a*(1-p);

    Color ret= Color(nr*255, ng*255, nb*255 , na*255);
    ret.checkColor();
    
    return ret;

}

void Color::checkColor(){

    if(r<0) r=0;
    if(g<0) g=0;
    if(b<0) b=0;
    if(a<0) a=0;
    
    if(r>1) r=1;
    if(g>1) g=1;
    if(b>1) b=1;
    if(a>1) a=1;

}

}