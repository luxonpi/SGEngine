

#ifndef SGENGINE_GRAPHICSDEVICEOPENGL_H
#define SGENGINE_GRAPHICSDEVICEOPENGL_H

#include "GraphicDevice.h"

namespace sge {
    
    class GraphicDeviceOpenGL: public GraphicDevice{

    private:
        
        SInt _cullFaceTable[3];
        SInt _blendTable[13];
        SInt _depthFuncTable[8];
        SInt _drawModeTable[4];
        SInt _textureTypeTable[9];
        SInt _textureFormatTable[13];
        SInt _dataTypeTable[10];
        SInt _textureFilterTable[6];
        SInt _textureWrapTable[6];
        SInt _bufferDrawType[3];
        SInt _bufferTypeTable[3];

        SUint createSubShader(const std::string& text, unsigned int type, Shader* shader);
        void checkShaderError(SUint shaderID, SUint flag, bool isProgram, const std::string& errorMessage, bool printSource,Shader* shader);

    public:
        
        virtual void startUp();
        virtual void unbindBuffer(SUint bufferType);

        // Shader
        virtual void generateShader(Shader* shader);
        virtual void releaseShader(Shader* shader);
        virtual void attachSource(Shader* shader, const std::string& source, const SUint& type);
        virtual void bindAttribLocation(Shader* shader, const SUint& location, const std::string& name);
        virtual void linkShader( Shader* shader );
        virtual SInt getUniformLocation(Shader* shader, const std::string& name);
        virtual void bindShader(Shader* shader);

        virtual void enableVertexAttributeArray(const SUint& location);
        virtual void setVertexAttributePointer(const SUint& index, const SInt& size, const SUint& dataType, const bool& normalized, const SUint& stride, SInt pointer);

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
        
        virtual void generateVertexArrayObject(VertexArrayObject* vao);
        virtual void releaseVertexArrayObject(VertexArrayObject* vao);
        
        virtual void generateFramebuffer(FrameBuffer* framebuffer);
        virtual void releaseFramebuffer(FrameBuffer* framebuffer);
        
        virtual void bindVertexArrayObject(VertexArrayObject* vao);
        virtual void bindTexture(Texture* texture, const SUint& location);
        virtual void releaseTexture(Texture* texture);
        virtual void setTextureData(Texture* texture, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data);
        virtual void setCubeMapTextureData(Texture* texture, SUint side, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data);
        
        virtual void generateTexture(Texture* texture);


        virtual void setTextureFilter(Texture* texture);
        virtual void setTextureWrap(Texture* texture);
        
        virtual void setRenderTargetToFramebuffer(FrameBuffer* buffer, RenderTarget* renderTarget);
    
        // Draw
        virtual void drawElements(const SUint& drawType, const SUint& indicesCount, const void * indices);
        virtual void drawArraysInstanced(const SUint& drawType,  const SUint& first,  const SUint& count, const SUint& instancecount);
        virtual void setVertexAttributeDivisor(const SUint& location, const SUint& divisor);

        virtual void clearFrameBuffer(FrameBuffer* framebuffer, bool color, bool depth, bool stencil);

        virtual void bindFrameBuffer(FrameBuffer* framebuffer);
        virtual void checkFrameBufferStatus(FrameBuffer* framebuffer);
        virtual void setViewPort(SInt x, SInt y, SInt w, SInt h);

        GraphicDeviceOpenGL();
        ~GraphicDeviceOpenGL();
	
    };
    
}





#endif
