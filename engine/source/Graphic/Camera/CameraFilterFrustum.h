

#ifndef CameraFilterFrustum_H
#define CameraFilterFrustum_H

#include <stdio.h>
#include "CameraFilter.h"

namespace sge {
    
    class CameraFilterFrustum: public CameraFilter{

    private:

        virtual bool checkVisibiltyForNodeAndCamera(Node* node, Camera* camera);

    public:
        CameraFilterFrustum();
        ~CameraFilterFrustum();
	
        virtual bool checkVisibiltyForRootNodeAndCamera(Node* node, Camera* camera);

    };
    
}

#endif
