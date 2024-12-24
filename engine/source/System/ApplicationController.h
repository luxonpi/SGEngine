

#ifndef SGENGINE_APPLICATIONCONTROLLER_H
#define SGENGINE_APPLICATIONCONTROLLER_H

#include <stdio.h>

namespace sge {
    
    class ApplicationController{
    
    private:
        
        
    public:
        
        ApplicationController();
        ~ApplicationController();

        virtual void willLaunch()=0;
        virtual void didFinishLaunching()=0;
        virtual void entersBackground()=0;
        virtual void enterForeground()=0;
        
    };
    
}


#endif
