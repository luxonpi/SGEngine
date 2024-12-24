

#include "ShadowMap.h"
#include "SMath.h"
#include "SBase.h"
#include "Director.h"
#include <limits>       // std::numeric_limits

namespace sge {

    ShadowMap* ShadowMap::create(const Vec2& size, SInt depthFormat){
    
        return new ShadowMap(size.x,size.y,1,depthFormat);
    
    }
    
    ShaderState* ShadowMap::getShaderState(){
    
        return &_shaderState;
    
    }

    
    ShadowMap* ShadowMap::createCascaded(const Vec2& size, SInt depthFormat, std::vector<Vec2> ranges){
    
        ShadowMap *sm=new ShadowMap(size.x,size.y, (int) ranges.size(),depthFormat);
        sm->_ranges=ranges;
        
        return sm;

    }
    
    ShadowMap::ShadowMap(float width, float height, unsigned int splits, SInt depthFormat){

        _splits=splits;
        
        // Minimum is one
        assert(_splits);
        
        biasMatrix=Mat4(0.5, 0.0, 0.0, 0.5,
                        0.0, 0.5, 0.0, 0.5,
                        0.0, 0.0, 0.5, 0.5,
                        0.0, 0.0, 0.0, 1.0);
        
    
        for (int i=0; i<_splits; i++) {
            
            FrameBuffer* buffer=FrameBuffer::create(width,height,0,depthFormat,0);
            buffer->getRenderTargetDepth()->getTexture()->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);
            
            buffer->getRenderTargetDepth()->getTexture()->setMagFilter(TextureFilter::NEAREST);
            buffer->getRenderTargetDepth()->getTexture()->setMinFilter(TextureFilter::NEAREST);


            _buffers.push_back(buffer);
            
            Camera* cam= Camera::createOrthographic(1, 1, 1, 1, 1);
            _cameras.push_back(cam);
        }
        
        _subCamera= Camera::createPerspective(2, 2, 2, 2);
        
        _ranges.push_back(Vec2(0, 1));
        _ranges.push_back(Vec2(1, 2));
     

        
    }
    
    void ShadowMap::clear(){
    
        for (int i=0; i<_splits; i++) {
            
            _buffers[i]->clear(false, true, false);
            
        }
        
    }
    
    void ShadowMap::finish(){
    
        for (int i=0; i<_splits; i++) {
            
            // Compute the MVP matrix from the light's point of view
            Mat4 depthProjectionMatrix = _cameras[i]->getProjectionMatrix();
            Mat4 depthViewMatrix =_cameras[i]->getViewMatrix();
            Mat4 depthModelMatrix = _cameras[i]->getModelMatrix();
            
            Mat4 depthMVP = _cameras[i]->getViewProjectionMatrix();
            Mat4 depthBiasMVP = biasMatrix*depthMVP;
            
            std::stringstream ssBias; ssBias<<"u_shadowBiasMVP["<<i<<"]";
            std::stringstream ssSampler; ssSampler<<"u_shadowMap["<<i<<"]";
            
            _shaderState.setUniform4m(ssBias.str(), &depthBiasMVP[0], false);
            _shaderState.setUniformTexture(ssSampler.str(), getTextureForIndex(i), 7+i);
            
        }
        
        _shaderState.setUniform4f("u_splits", Vec4(_ranges[0].x*_viewCamLength, _ranges[1].x*_viewCamLength,
                                                   _ranges[2].x*_viewCamLength, _ranges[3].x*_viewCamLength));

        
    }
    
    
    void ShadowMap::renderLayerIntoLevel(RenderLayer* layer, Camera* lightcamera, Camera* viewcamera, int level){
    
       // calcOrthographicProjections(lightcamera, viewcamera);
        _camera=lightcamera;
        _cameras[0]=lightcamera;
        
        Director::getInstance()->getRenderer()->renderLayer(layer,_buffers[level], _cameras[0], "posOnly");
        
    }
    
    void ShadowMap::renderLayer(RenderLayer* layer, Camera* lightcamera, Camera* viewcamera){
    
       // calcOrthographicProjections(lightcamera, viewcamera);
        _camera=lightcamera;
        _cameras[0]=lightcamera;

        for (int i=0; i<_splits; i++) {

            Director::getInstance()->getRenderer()->renderLayer(layer,_buffers[i], _cameras[i], "posOnly");

        }
        
    }
    
    void ShadowMap::calcOrthographicProjections( Camera* lightcamera, Camera* viewcamera){
        
        // Get the light space tranform
        lightcamera->setPosition(viewcamera->transform().getTranslation());
        Mat4 LightM = lightcamera->getViewMatrix();

        _viewCamLength= viewcamera->getFarPlane()-viewcamera->getNearPlane();
        
        for (uint i = 0; i<_splits ; i++) {
            
            _subCamera->copy(viewcamera);
            _subCamera->setNearPlane(_ranges[i].x*_viewCamLength);
            _subCamera->setFarPlane(_ranges[i].y*_viewCamLength);
            
            Vec4 frustumCorners[8];
            
            Vec3 corners[8];
            _subCamera->getFrustum().getCorners(&corners[0]);
            
            for (int a=0; a<8; a++) {
                
                frustumCorners[a]= Vec4(corners[a].x,corners[a].y,corners[a].z,1.0);
            }
            
            
            Vec4 frustumCornersL[8];
            
            float minX = std::numeric_limits<float>::max();
            float maxX = std::numeric_limits<float>::min();
            float minY = std::numeric_limits<float>::max();
            float maxY = std::numeric_limits<float>::min();
            float minZ = std::numeric_limits<float>::max();
            float maxZ = std::numeric_limits<float>::min();
            
            for (uint j = 0 ; j < 8 ; j++) {
                
                // Transform the frustum coordinate from world to light space
                frustumCornersL[j] = LightM* frustumCorners[j];
                
                minX = min(minX, frustumCornersL[j].x);
                maxX = max(maxX, frustumCornersL[j].x);
                minY = min(minY, frustumCornersL[j].y);
                maxY = max(maxY, frustumCornersL[j].y);
                minZ = min(minZ, frustumCornersL[j].z);
                maxZ = max(maxZ, frustumCornersL[j].z);
            }
            
            Mat4 matrix;
            Mat4::createOrthographicOffCenter(minX,maxX,minY,maxY,maxZ,minZ, &matrix);
            
            _cameras[i]->setProjectionMatrix(matrix);
            _cameras[i]->setPosition(viewcamera->transform().getTranslation());
            _cameras[i]->setDirection(lightcamera->getDirection());
        
        }

        
    }
    
    
    Camera* ShadowMap::getCameraAtIndex(int index){
    
        assert(index<_cameras.size());
        return _cameras[index];
    
    }
    
    Texture* ShadowMap::getTextureForIndex(unsigned int index){
    
        if(index>=_buffers.size()) return NULL;
        return _buffers[index]->getRenderTargetDepth()->getTexture();
    
    }


}
