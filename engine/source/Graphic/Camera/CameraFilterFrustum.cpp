
#include "SCamera.h"
#include "CameraFilterFrustum.h"
#include "GraphicDeviceDefines.h"

namespace sge {
    
    CameraFilterFrustum::CameraFilterFrustum(){
    
    
    
    }
    
    CameraFilterFrustum::~CameraFilterFrustum(){
    
    
    }
    
    bool CameraFilterFrustum::checkVisibiltyForRootNodeAndCamera(Node* node, Camera* camera){
    
         node->getRenderObject()->setHiddenForCamera(camera, false, true);
        
        checkVisibiltyForNodeAndCamera(node, camera);
    
        return true;
    }
    
    
    bool CameraFilterFrustum::checkVisibiltyForNodeAndCamera(Node* node, Camera* camera){
      
        bool visible=true;
        
        switch (node->getRenderObject()->getFrustumCulling()) {
                
            case FrustumCulling::NONE:
                break;
                
            case FrustumCulling::SPHERE:
                if(!node->getBoundingSphere().intersects(camera->getFrustum())) visible=false;
                
                break;
                
            case FrustumCulling::BOX:
                if(!node->getBoundingBox().intersects(camera->getFrustum())) visible=false;
                
                break;
                
            default:
                break;
        }
        
        if(!visible) node->getRenderObject()->setHiddenForCamera(camera, true, true);
        else{
    
            for (int i=0; i<node->getChildren()->size(); i++) {
                
                checkVisibiltyForNodeAndCamera(node->getChildren()->at(i), camera);
                
            }
        
        }
    
        return visible;

    
    }


    
    
}