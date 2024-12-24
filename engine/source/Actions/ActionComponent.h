

#ifndef ActionManager_H
#define ActionManager_H

#include "SBase.h"
#include "Component.h"
#include "UpdateDispenser.h"

#include "Action.h"

#include <stdio.h>

namespace sge {
    
    class ActionComponent: public Component{
        
    protected:
        
        UpdateReceiver* _updateReceiver;
        virtual void setTypeName();
        
        Action* _testAction;
        
    public:
        
        bool isRunningAction();
        void runAction(Action* action);
        
        ActionComponent();
        ~ActionComponent();
        
        virtual void setEnabled(bool enabled);
        
        // Registered Functions
        void update(float delta);
        
    };
    
}

#endif
