

#ifndef SGENGINE_LIGHT_H
#define SGENGINE_LIGHT_H

#include <iostream>

#include "Node.h"
#include "Color.h"
#include "Entity.h"

namespace sge {
    
    enum LightType{
        
        LightType_POINT,
        LightType_DIRECTION,
        LightType_SPOT,
        LightType_HEMI

    };
    
    class Light: public Entity{
        
    private:
    
        Vec3 _direction;
        Vec3 _color;
        
        float _intensity;
        float _radius;
        int _shadowMapIndex;
    
        LightType _type;
    
        Light();
        virtual ~Light();

    public:
        
        static Light* create(const LightType& type, const float& intensity, const float& radius);

        void setDirection(const Vec3& direction);
        Vec3 getDirection();

        void setColor(const Vec3& color);
        Vec3 getColor();
        
        void setShadowMapIndex(unsigned int index);
        unsigned int getShadowMapIndex();
        
        void setIntensity(const float& intensity);
        float getIntensity();
        
        void setRadius(const float& radius);
        float getRadius();
        
        void setType(const LightType& type);
        LightType getType();
        

    };
    
}

#endif
