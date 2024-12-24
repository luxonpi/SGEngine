

#ifndef ActionRotateTo_H
#define ActionRotateTo_H

#include <stdio.h>
#include "Action.h"

namespace sge {
    
    class ActionRotateTo: public Action{
        
    protected:
        
        ActionRotateTo();
        
        Quaternion _starRotation;
        Quaternion _endRotation;
        
    public:
        
        virtual ~ActionRotateTo();
        
        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
        
        static ActionRotateTo* create(float time, const Vec3& rotation);
       	
    };
    
}

#endif
