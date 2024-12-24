

#ifndef CameraFilter_H
#define CameraFilter_H

#include <stdio.h>
#include "Node.h"


// A Abstract class to provide the possiblity of adding custom culling methods
namespace sge {
    
    class Camera;
    class CameraFilter{

    private:

    public:
        CameraFilter();
        ~CameraFilter();
        
        virtual bool checkVisibiltyForRootNodeAndCamera(Node* node, Camera* camera);
	
    };
    
}

#endif
