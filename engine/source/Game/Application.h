

#ifndef SGENGINE_APPLICATION_H
#define SGENGINE_APPLICATION_H

#include "ApplicationController.h"
#include <string>

namespace sge {
    
    class Application{

    private:
        
        static double _lastUpdate;
        static double _lastDraw;

        static void init();
        static void update();
        
        
    public:
        
        static int run(ApplicationController* controller, const std::string& configFile);
    
    };

}

#endif
