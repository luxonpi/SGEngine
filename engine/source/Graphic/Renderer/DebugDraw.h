

#ifndef SGENGINE_DEBUGDRAW_H
#define SGENGINE_DEBUGDRAW_H

#include "SBase.h"

#include "RenderObject.h"
#include "SCamera.h"
#include "RenderLayer.h"
#include "FrameBuffer.h"

#include "RenderState.h"

#include "Model.h"

namespace sge {
    
    class DebugDraw{
        
    private:
        
        Mesh* _frustumMesh;
        Mesh* _cubeMesh;
        Mesh* _sphereMesh;
        
        Shader* _debugShader;
        RenderState _debugState;
        Node* _debugNode;
        
        Renderer* _renderer;
        
    public:
        
        void startUp();
        
        DebugDraw();
        ~DebugDraw();
        
        void renderDebugFrustum(Frustum* frustum, FrameBuffer* buffer, Camera* camera);
        void renderDebugCube( std::vector<Vec3> points, FrameBuffer* buffer, Camera* camera);
        
    };
    
}

#endif