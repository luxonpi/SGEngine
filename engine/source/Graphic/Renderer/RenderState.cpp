

#include "RenderState.h"
#include "SCamera.h"
#include "GraphicDeviceDefines.h"

namespace sge {

    RenderState::RenderState(){
    

        camera=NULL;
    
    }
    
    RenderState::RenderState(RenderState* copy){
        
        camera=copy->camera;
        view=copy->view;
        model=copy->model;
        projection=copy->projection;
        shaderState=copy->shaderState;
        blendFunc=copy->blendFunc;
        drawMode=copy->drawMode;
        
    }
    
    
}