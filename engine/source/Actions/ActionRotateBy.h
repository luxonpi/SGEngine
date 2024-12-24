

#ifndef ActionRotateBy_H
#define ActionRotateBy_H

#include <stdio.h>
#include "Action.h"

namespace sge {
    
    class ActionRotateBy: public Action{
        
    protected:
        
        ActionRotateBy();
        
        Vec3 _starRotation;
        Vec3 _endRotation;
        
    public:
        
        virtual ~ActionRotateBy();
        
        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
        
        static ActionRotateBy* create(float time, const Vec3& rotation);
       	
    };
    
}

#endif
