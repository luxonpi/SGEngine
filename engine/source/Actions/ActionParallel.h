

#ifndef ActionParallel_H
#define ActionParallel_H

#include <stdio.h>
#include "Action.h"

namespace sge {
    
    class ActionParallel: public Action{
        
    protected:
        
        ActionParallel();
        virtual ~ActionParallel();
        
        std::vector<Action*> _actions;
        
    public:
        
        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
        
        static ActionParallel* create(std::vector<Action*> actions);
       	
    };
    
}


#endif
