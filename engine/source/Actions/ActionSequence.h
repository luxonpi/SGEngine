

#ifndef ActionSequence_H
#define ActionSequence_H

#include <stdio.h>
#include "Action.h"

namespace sge {
    
    class ActionSequence: public Action{
        
    protected:
        
        ActionSequence();
        virtual ~ActionSequence();
 
        std::vector<Action*> _actions;
        Action* _runningAction;
        unsigned int _indexOfRunningAction;
        
        void runNextAction(Entity* entity);
        
    public:
        
        void updateEntity(Entity* entity);
        void start(Entity* entity);
        void end(Entity* entity);
        
        static ActionSequence* create(std::vector<Action*> actions);
       	
    };
    
}


#endif
