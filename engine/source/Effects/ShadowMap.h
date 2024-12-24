

#ifndef SGENGINE_SHADOWMAP_H
#define SGENGINE_SHADOWMAP_H

#include "SBase.h"

#include "Shader.h"
#include "FrameBuffer.h"
#include "Light.h"
#include "RenderObject.h"
#include "RenderLayer.h"

namespace sge {
    
class ShadowMap{

protected:
    
    // Static Members
    Mat4 biasMatrix;

    unsigned int _splits;
    std::vector<FrameBuffer*> _buffers;
    
    Camera* _subCamera;
    Camera* _camera;
    
    std::vector<Camera*> _cameras;
    std::vector<Vec2> _ranges;
    
    float _viewCamLength;
    
    ShaderState _shaderState;

    ShadowMap(float width, float height, unsigned int splits, SInt depthFormat);
    
    
    
public:
    
    static ShadowMap* create(const Vec2& size, SInt depthFormat);
    static ShadowMap* createCascaded(const Vec2& size, SInt depthFormat, std::vector<Vec2> ranges);

    Camera* getCameraAtIndex(int index);
    
    void calcOrthographicProjections( Camera* lightcamera, Camera* viewcamera);
    
    ShaderState* getShaderState();

    void clear();
    void renderLayer(RenderLayer* layer, Camera* lightcamera, Camera* viewcamera);
    void renderLayerIntoLevel(RenderLayer* layer, Camera* lightcamera, Camera* viewcamera, int level);
    
    void finish();
    
    
    Texture* getTextureForIndex(unsigned int index);

};
    
}

#endif 