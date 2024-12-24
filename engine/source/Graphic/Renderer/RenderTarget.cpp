

#include "RenderTarget.h"
#include "FrameBuffer.h"
#include "GraphicDeviceOpenGL.h"
#include "glInclude.h"

namespace sge{
    
    static std::vector<RenderTarget*> __renderTargets;
    
    RenderTarget::RenderTarget(const char* id)
    : _id(id ? id : ""), _texture(NULL)
    {
        
        _framebuffer=NULL;
        _index=0;
        
    }
    
    RenderTarget::~RenderTarget()
    {
        
        // Remove ourself from the cache.
        std::vector<RenderTarget*>::iterator it = std::find(__renderTargets.begin(), __renderTargets.end(), this);
        if (it != __renderTargets.end())
        {
            __renderTargets.erase(it);
        }
    }
    
    void RenderTarget::setIndex(unsigned int index){
 
        _index=index;
    
    }

    RenderTarget* RenderTarget::createColorTarget(Vec2 size, SUint internalFormat, SUint dataType, SUint index){
    
        // Create a new texture with the given width.
        Texture* texture=NULL;
        texture = Texture::create(size.x, size.y, TextureFormat::RGBA, internalFormat,dataType);
        texture->Resource::name="Framebuffer: RenderTarget Color";

        texture->setMagFilter(TextureFilter::NEAREST);
        texture->setMinFilter(TextureFilter::NEAREST);
        texture->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);

        RenderTarget* rt = create("", texture);
        rt->_renderTargetType=RENDERTARGET_TYPE_COLOR;
        rt->_textureTarget=TextureType::NORMAL2D;
        rt->_index=index;
        
        return rt;

    }
    
    RenderTarget* RenderTarget::createDepthTarget(Vec2 size, SUint internalFormat){
    
        // Create a new texture with the given width.
        Texture* texture=NULL;
        texture = Texture::create(size.x, size.y, TextureFormat::DEPTH, internalFormat, DataType::UNSIGNED_BYTE);
        texture->Resource::name="Framebuffer: RenderTarget Depth";
        texture->setMagFilter(TextureFilter::NEAREST);
        texture->setMinFilter(TextureFilter::NEAREST);
        texture->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);
 
        RenderTarget* rt = create("", texture);
        rt->_renderTargetType=RENDERTARGET_TYPE_DEPTH;
        rt->_textureTarget=TextureType::NORMAL2D;
        
        return rt;

    }
    
    RenderTarget* RenderTarget::createStencil(Vec2 size, SUint internalFormat){
    
        // Create a new texture with the given width.
        Texture* texture=NULL;
        texture = Texture::create(size.x, size.y,TextureFormat::DEPTH_STENCIL,TextureFormat::DEPTH24_STENCIL8, DataType::UNSIGNED_INT_24_8);
        texture->Resource::name="Framebuffer: RenderTarget Stencil";

        texture->setMagFilter(TextureFilter::NEAREST);
        texture->setMinFilter(TextureFilter::NEAREST);
        texture->setTextureWrap(TextureWrap::CLAMP_TO_EDGE);

        RenderTarget* rt = create("", texture);
        rt->_renderTargetType=RENDERTARGET_TYPE_STENCIL;
        rt->_textureTarget=TextureType::NORMAL2D;
        
        return rt;

    }

    RenderTarget* RenderTarget::create(const char* id, Texture* texture)
    {
        RenderTarget* renderTarget = new RenderTarget(id);
        renderTarget->_texture = texture;
        renderTarget->_textureTarget=TextureType::NORMAL2D;

        __renderTargets.push_back(renderTarget);
        
        return renderTarget;
    }
    
    RenderTarget* RenderTarget::getRenderTarget(const char* id)
    {
        
        // Search the vector for a matching ID.
        std::vector<RenderTarget*>::const_iterator it;
        for (it = __renderTargets.begin(); it < __renderTargets.end(); ++it)
        {
            RenderTarget* dst = *it;
            if (strcmp(id, dst->getId()) == 0)
            {
                return dst;
            }
        }
        
        return NULL;
    }
    
    void RenderTarget::setSize(const Vec2& size){
    
        glBindTexture(GL_TEXTURE_2D, _texture->getID());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, int(size.x), int(size.y),0, GL_RGB, GL_FLOAT, NULL);
      
    }
    
    void RenderTarget::setTextureTarget(SUint textureTarget){
    
        _textureTarget=textureTarget;
        if(_framebuffer) _framebuffer->attachRenderTarget(this);
    
    }

    SUint RenderTarget::getTextureTarget(){
    
        return _textureTarget;
    
    }

    
    const char* RenderTarget::getId() const
    {
        return _id.c_str();
    }
    
    Texture* RenderTarget::getTexture()
    {
        return _texture;
    }
    
    unsigned int RenderTarget::getWidth() const
    {
        return _texture->getSize().x;
    }
    
    unsigned int RenderTarget::getHeight() const
    {
        return _texture->getSize().y;
    }
    
}
