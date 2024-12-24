

#include "Light.h"
#include "Director.h"

namespace sge {
    
    Light* Light::create(const LightType& type, const float& intensity, const float& radius){
    
        Light* light= new Light();
    
        light->setIntensity(intensity);
        light->setType(type);
        light->setRadius(radius);
        
        return light;
        
    }
    
    Light::Light(){
    
        Vec2 winS= Director::getInstance()->getWindowSize();

        _direction.set(0, 0, 0);
    
        _color.set(1,1,1);
        _intensity=1;
        _radius=25;
        _shadowMapIndex=0;
        
        _contentBox.min.set(-_radius*0.5, -_radius*0.5, -_radius*0.5);
        _contentBox.max.set(_radius*0.5, _radius*0.5, _radius*0.5);
        
        _type=LightType_POINT;
    
    }
    
    
    void Light::setShadowMapIndex(unsigned int index){
    
        _shadowMapIndex=index;
    
    }
    
    unsigned int Light::getShadowMapIndex(){
    
        return _shadowMapIndex;
    
    }
    
    Light::~Light(){
    

    }
    
    void Light::setDirection(const Vec3& direction){
    
        _direction=direction;

    }
    
    Vec3 Light::getDirection(){
    
        return _direction;
    
    }
    
    void Light::setColor(const Vec3& color){
    
        _color=color;
    
    }
    
    Vec3 Light::getColor(){
    
        return _color;
    
    }
    
    void Light::setIntensity(const float& intensity){
    
        _intensity=intensity;
    
    }
    
    float Light::getIntensity(){
    
        return _intensity;
    
    }
    
    void Light::setRadius(const float& radius){
    
        _radius=radius;
    
        _contentBox.min.set(-_radius*0.5, -_radius*0.5, -_radius*0.5);
        _contentBox.max.set(_radius*0.5, _radius*0.5, _radius*0.5);
    
    }
    
    float Light::getRadius(){
    
        return _radius;
    
    }
    
    void Light::setType(const LightType& type){
    
        _type=type;
    
    }
    
    LightType Light::getType(){
    
        return _type;
    
    }
    
    
    
}