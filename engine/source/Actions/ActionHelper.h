

#ifndef ActionHelper_H
#define ActionHelper_H

#include <stdio.h>
#include "Action.h"

namespace sge {
    
    class ActionWait: public Action{
        
    protected:
        
        ActionWait();
        
    public:
        
        virtual ~ActionWait();
        
        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
        
        static ActionWait* create(float time);
       	
    };
    
    class ActionFunction: public Action{
        
    protected:
        
        ActionFunction();
        std::function< void() > _callback;

    public:
        
        virtual ~ActionFunction();
        
        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
        
        static ActionFunction* create(std::function< void() > callback);
       	
    };
    
}

#endif
