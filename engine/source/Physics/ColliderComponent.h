

#ifndef SGENGINE_COLLIDERCOMPONENT_H
#define SGENGINE_COLLIDERCOMPONENT_H

#include <stdio.h>
#include <iostream>

#include "Node.h"
#include "UpdateDispenser.h"
#include "Component.h"

namespace sge {
    
    class ColliderComponent: public Component{
        
    protected:
        
        virtual void setTypeName();
        
    public:
        
        void addSphere(Vec3 offset, float radius);
        void addBox(Vec3 offset, Vec3 size, Vec3 rotation);
        
        ColliderComponent();
        ~ColliderComponent();
        
        virtual void setEnabled(bool enabled);
        
    };
    
}


#endif
