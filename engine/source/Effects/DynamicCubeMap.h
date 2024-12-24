

#ifndef DynamicCubeMap_H
#define DynamicCubeMap_H

#include <stdio.h>
#include "SBase.h"
#include "SCamera.h"
#include "FrameBuffer.h"
#include "RenderLayer.h"
#include "TextureCubeMap.h"
#include "RenderTarget.h"
#include "Compositor.h"

namespace sge {
    
    class DynamicCubeMap{

    private:
        
        static Vec3 ups[6];
        static Vec3 dir[6];

        DynamicCubeMap(int width, int height, SInt format, SInt depthFormat);
        ~DynamicCubeMap();
        
        TextureCubeMap* _textureCubeMap;
        Compositor _compositor;

        Camera* _camera;
        FrameBuffer* _frameBuffer;
        RenderTarget* _renderTarget;
        ShaderModule* _module;
        

    public:
      
        static DynamicCubeMap* create(int width, int height, SInt format, SInt depthFormat);
        
        void renderInLayer(RenderLayer* layer, Vec3 position, bool clear);

        
        TextureCubeMap* getTexture();
        
	
    };

}

#endif
