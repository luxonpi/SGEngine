

#ifndef SGENGINE_RENDERER_H
#define SGENGINE_RENDERER_H

#include "SBase.h"

#include "RenderObject.h"
#include "SCamera.h"
#include "RenderLayer.h"
#include "FrameBuffer.h"

#include "RenderState.h"
#include "ShaderModule.h"

#include "Model.h"
#include "Timer.h"
#include "Light.h"

#include "ModelInstanced.h"
#include "Compositor.h"

#define RENDER_LAYER_SCENE 0
#define RENDER_LAYER_UI 19
#define RENDER_LAYER_SKY 2

namespace sge {

    class Mesh;
    class Director;

    class Renderer{

        friend Director;
        
    private:
        
        Renderer();
        ~Renderer();
        
        bool blendingEnabled;
        BlendFunc blendFunc;
        SUint cullFace;
        SUint depthFunc;
        
        RenderState _state;
        Material* _uploadedMaterial;
        Shader* _uploadedShader;

        Texture* _boundTextures[16];
        RenderLayer* _layer[20];
        
    public:
        
        RenderLayer* getRenderLayer(unsigned int index);
        
        Timer timer;
        void setGlobalUniformsToShader(Node* node, RenderState* renderState, Shader* shader);
            
        void uploadTexture(Texture* texture, uint position);
        void uploadMaterial(Material* material, const std::string& defines);
        
        void renderObject(RenderObject* renderObject, FrameBuffer* framebuffer, Camera* camera, const std::string& defines="");
        void renderLayer(RenderLayer* layer, FrameBuffer* framebuffer, Camera* camera, const std::string& defines="");

        void renderMeshWithRenderState(Node* node, Mesh* mesh, RenderState* renderState);
        void renderInstancedModelWithRenderState(ModelInstanced* instance, RenderState* renderState);

    


    };
    
}

#endif