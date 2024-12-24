

#include "DynamicCubeMap.h"
#include "Director.h"
#include "glInclude.h"

namespace sge {
    
Vec3 DynamicCubeMap::ups[6]={Vec3(0, -1, 0),Vec3(0, -1, 0),Vec3(0, 0, 1),Vec3(0, 0, 1),Vec3(0, -1, 0),Vec3(0, -1, 0)};
Vec3 DynamicCubeMap::dir[6]={Vec3(10, 0, 0),Vec3(-10, 0, 0),Vec3(0, 10, 0),Vec3(0, -10, 0),Vec3(0, 0, 10),Vec3(0, 0, -10)};

DynamicCubeMap* DynamicCubeMap::create(int width, int height, SInt format, SInt depthFormat){
    
    DynamicCubeMap* dynamicMap= new DynamicCubeMap(width, height,format,depthFormat);
    return dynamicMap;

}
    
DynamicCubeMap::DynamicCubeMap(int width, int height, SInt format, SInt depthFormat){
    
    
    _camera= Camera::createPerspective(90, 1, 0.01, 500);
    
    _textureCubeMap= TextureCubeMap::createEmpty(width, height, format);

    Director::getInstance()->getGraphicDevice()->bindTexture(_textureCubeMap, 0);
   // glGenerateMipmapEXT(GL_TEXTURE_CUBE_MAP);

    _renderTarget= RenderTarget::create("RenderTargetDynamicCube", _textureCubeMap);

    _frameBuffer = FrameBuffer::create(width, height, format, depthFormat, 0);
    _frameBuffer->setClearColor(Color(34, 162, 251, 1));

    // ToDo: Sollte framebuffer automatisch aktualisieren
    _renderTarget->setTextureTarget(TextureType::CUBE_MAP_POSITIVE_X);
    _renderTarget->setIndex(0);
    _frameBuffer->attachRenderTarget(_renderTarget);
    
//    _module= ShaderModule::createFromFiles({"support/shader/frag/Diffuse.glsl"});
//    _module->setConfigID("vertex");
//    
    
}

DynamicCubeMap::~DynamicCubeMap(){


}

TextureCubeMap* DynamicCubeMap::getTexture(){
    
    return _textureCubeMap;

}
    
void DynamicCubeMap::renderInLayer(RenderLayer* layer, Vec3 position, bool clear){

    _camera->setPosition(position);
    
    Renderer* renderer= Director::getInstance()->getRenderer();
    
    for (int i=0; i<6; i++) {

        _camera->setDirection(dir[i]);
        _camera->setUp(ups[i]);
        _renderTarget->setTextureTarget(TextureType::CUBE_MAP_POSITIVE_X+ (int)i);
        
        if(clear) _frameBuffer->clear(true,true,true);
        
        renderer->renderLayer(layer, _frameBuffer, _camera, NULL);
    
    }
    

}

}
