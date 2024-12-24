

#ifndef ActionMoveTo_H
#define ActionMoveTo_H

#include <stdio.h>
#include "Action.h"

namespace sge {
    
    class ActionMoveTo: public Action{

    protected:
        
        ActionMoveTo();

        Vec3 _starPos;
        Vec3 _endPos;

    public:
        
        virtual ~ActionMoveTo();

        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
    
        static ActionMoveTo* create(float time, const Vec3& position);
       	
    };

}

#endif
