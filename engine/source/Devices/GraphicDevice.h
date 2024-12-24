

#ifndef SGENGINE_GRAPHICSDEVICE_H
#define SGENGINE_GRAPHICSDEVICE_H

#include "SBase.h"

namespace sge {
    
    class Shader;
    class VertexArrayObject;
    class BlendFunc;
    class Texture;
    class VertexBuffer;
    class VertexArrayObject;
    class FrameBuffer;
    class RenderTarget;

    class GraphicDevice{
        
    private:
        
    protected:
        
        FrameBuffer* _screenFramebuffer;
        
        GraphicDevice();
        ~GraphicDevice();
        
    public:
        
        FrameBuffer* getScreenFrameBuffer();
        
        virtual void startUp();
        
        // Shader
        virtual void generateShader(Shader* shader);
        virtual void releaseShader(Shader* shader);
        virtual void attachSource(Shader* shader, const std::string& source, const SUint& type);
        virtual void bindAttribLocation(Shader* shader, const SUint& location, const std::string& name);
        virtual void linkShader( Shader* shader );
        virtual SInt getUniformLocation(Shader* shader, const std::string& name);
        virtual void bindShader(Shader* shader);
        virtual void unbindBuffer(SUint bufferType);
        
        // State
        virtual void setCullFace(const SUint& cullface);
        virtual void setBlendFunc(const BlendFunc& blendFunc);
        virtual void setBlendingEnabled(const bool& enabled);
        virtual void setDepthFunc( const SUint& depthFunc );
        virtual void setDepthWritingEnabled(const bool& enabled);
        virtual void setDepthTestEnabled(const bool& enabled);
        
        // Data
        virtual void bindVertexBuffer(VertexBuffer* buffer);
        virtual void bufferVertexBufferData(VertexBuffer* buffer);
        
        virtual void generateVertexBuffer(VertexBuffer* buffer);
        virtual void releaseVertexBuffer(VertexBuffer* buffer);
        
        virtual void generateFramebuffer(FrameBuffer* framebuffer);
        virtual void releaseFramebuffer(FrameBuffer* framebuffer);
        
        virtual void generateVertexArrayObject(VertexArrayObject* vao);
        virtual void releaseVertexArrayObject(VertexArrayObject* vao);
        
        virtual void bindVertexArrayObject(VertexArrayObject* vao);
        virtual void bindTexture(Texture* texture, const SUint& location);
        
        virtual void generateTexture(Texture* texture);
        
        virtual void releaseTexture(Texture* texture);
        virtual void setTextureData(Texture* texture, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data);
        virtual void setCubeMapTextureData(Texture* texture, SUint side, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data);

        virtual void setTextureFilter(Texture* texture);
        virtual void setTextureWrap(Texture* texture);
        
        virtual void setVertexAttributeDivisor(const SUint& location, const SUint& divisor);

        virtual void enableVertexAttributeArray(const SUint& location);
        virtual void setVertexAttributePointer(const SUint& index, const SInt& size, const SUint& dataType, const bool& normalized, const SUint& stride, SInt pointer);
        //Draw
        virtual void drawElements(const SUint& drawType, const SUint& indicesCount, const void * indices);
        virtual void drawArraysInstanced(const SUint& drawType,  const SUint& first,  const SUint& count, const SUint& instancecount);
        
        virtual void clearFrameBuffer(FrameBuffer* framebuffer, bool color, bool depth, bool stencil);
        
        virtual void checkFrameBufferStatus(FrameBuffer* framebuffer);
        
        virtual void bindFrameBuffer(FrameBuffer* framebuffer);
        virtual void setViewPort(SInt x, SInt y, SInt w, SInt h);
        
        virtual void setRenderTargetToFramebuffer(FrameBuffer* buffer, RenderTarget* renderTarget);
        

    };
    
}

bool _CheckRenderError(const char* file, int line);
#define checkRenderError() _CheckRenderError(__FILE__, __LINE__)

#endif