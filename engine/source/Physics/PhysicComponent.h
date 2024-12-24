

#ifndef SGENGINE_PHYSICCOMPONENT_H
#define SGENGINE_PHYSICCOMPONENT_H

#include <stdio.h>
#include <iostream>

#include "Node.h"
#include "UpdateDispenser.h"
#include "Component.h"

namespace sge {
    
    class PhysicsComponent: public Component{
        
    protected:
        
        static int MODE_STATIC;
        static int MODE_DYNAMIC;
                
        
        virtual void setTypeName();
        
    public:
        
        Vec3 _velocity;
        
        float _minimalHeight;
        float _mass;
        float _inverseMass;

        float _friction;
        float _bounciness;
        
        int _mode;

        
        void setMode(int mode);
        void setMass(float mass);
        void setMinimalHeight(float minimalHeight);
        void setFriction(float friction);
        void setBounciness(float bounciness);
        
        void setMoveVec(Vec3 vec, float velocity);
        void applyForce(Vec3 force);
        
        PhysicsComponent();
        ~PhysicsComponent();
        
        virtual void setEnabled(bool enabled);
   
        
        
    };
    
}




#endif
