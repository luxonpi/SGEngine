

#ifndef ActionRepeatForever_H
#define ActionRepeatForever_H

#include <stdio.h>
#include "Action.h"

namespace sge {
    
    class ActionRepeatForever: public Action{
        
    protected:
        
        ActionRepeatForever();
        virtual ~ActionRepeatForever();
        
        Action* _action;
        
    public:
        
        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
        
        static ActionRepeatForever* create(Action* action);
       	
    };
    
}


#endif
