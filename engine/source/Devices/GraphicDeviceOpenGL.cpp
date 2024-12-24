

#include "GraphicDeviceOpenGL.h"
#include "glInclude.h"

#include "Shader.h"
#include "FrameBuffer.h"
#include "VertexArrayObject.h"
#include "GraphicDeviceDefines.h"
#include "Texture.h"
#include "TextureCubeMap.h"
#include "FrameBuffer.h"
#include "RenderTarget.h"
#include "Director.h"

/*

// Stencil Defines
class StencilFunction{
    
    STENCIL_NEVER = GL_NEVER,
    STENCIL_ALWAYS = GL_ALWAYS,
    STENCIL_LESS = GL_LESS,
    STENCIL_LEQUAL = GL_LEQUAL,
    STENCIL_EQUAL = GL_EQUAL,
    STENCIL_GREATER = GL_GREATER,
    STENCIL_GEQUAL = GL_GEQUAL,
    STENCIL_NOTEQUAL = GL_NOTEQUAL
};

// Stencil operation Defines
class StencilOperation{
    
    STENCIL_OP_KEEP = GL_KEEP,
    STENCIL_OP_ZERO = GL_ZERO,
    STENCIL_OP_REPLACE = GL_REPLACE,
    STENCIL_OP_INCR = GL_INCR,
    STENCIL_OP_DECR = GL_DECR,
    STENCIL_OP_INVERT = GL_INVERT,
    STENCIL_OP_INCR_WRAP = GL_INCR_WRAP,
    STENCIL_OP_DECR_WRAP = GL_DECR_WRAP
};

 */

namespace sge{
    
    GraphicDeviceOpenGL::GraphicDeviceOpenGL(){}
    GraphicDeviceOpenGL::~GraphicDeviceOpenGL(){}

void GraphicDeviceOpenGL::startUp(){

    // Map Enums
    Vec2 winS= Director::getInstance()->getWindowSize();
    
    _screenFramebuffer= new FrameBuffer(winS.x,winS.y);
    SInt defaultFBO=0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    _screenFramebuffer->_fboID=defaultFBO;
    
    glDepthMask(true);
    
    // CullFace
    _cullFaceTable[0]= GL_BACK;
    _cullFaceTable[1]= GL_FRONT;
    _cullFaceTable[2]= GL_FRONT_AND_BACK;

    //Blends
    _blendTable[Blend::ZERO]= GL_ZERO;
    _blendTable[Blend::ONE]= GL_ONE;
    _blendTable[Blend::SRC_COLOR]= GL_SRC_COLOR;
    _blendTable[Blend::ONE_MINUS_SRC_COLOR]= GL_ONE_MINUS_SRC_COLOR;
    _blendTable[Blend::DST_COLOR]= GL_DST_COLOR;
    _blendTable[Blend::ONE_MINUS_DST_COLOR]= GL_ONE_MINUS_DST_COLOR;
    _blendTable[Blend::SRC_ALPHA]= GL_SRC_ALPHA;
    _blendTable[Blend::ONE_MINUS_SRC_ALPHA]= GL_ONE_MINUS_SRC_ALPHA;
    _blendTable[Blend::DST_ALPHA]= GL_DST_ALPHA;
    _blendTable[Blend::ONE_MINUS_DST_ALPHA]= GL_ONE_MINUS_DST_ALPHA;
    _blendTable[Blend::CONSTANT_ALPHA]= GL_CONSTANT_ALPHA;
    _blendTable[Blend::ONE_MINUS_CONSTANT_ALPHA]= GL_ONE_MINUS_CONSTANT_ALPHA;
    _blendTable[Blend::SRC_ALPHA_SATURATE]= GL_SRC_ALPHA_SATURATE;
    
    // DepthFuncs
    _depthFuncTable[DepthFunc::NEVER] = GL_NEVER;
    _depthFuncTable[DepthFunc::LESS] = GL_LESS;
    _depthFuncTable[DepthFunc::EQUAL] = GL_EQUAL;
    _depthFuncTable[DepthFunc::LEQUAL] = GL_LEQUAL;
    _depthFuncTable[DepthFunc::GREATER] = GL_GREATER;
    _depthFuncTable[DepthFunc::NOTEQUAL] = GL_NOTEQUAL;
    _depthFuncTable[DepthFunc::GEQUAL] = GL_GEQUAL;
    _depthFuncTable[DepthFunc::ALWAYS] = GL_ALWAYS;
    
    // DrawModes
    _drawModeTable[DrawMode::TRIANGLES]= GL_TRIANGLES;
    _drawModeTable[DrawMode::LINES]= GL_LINES;
    _drawModeTable[DrawMode::POINTS]= GL_POINTS;
    _drawModeTable[DrawMode::TRIANGLE_STRIP]= GL_TRIANGLE_STRIP;
    
    // Texture Types
    _textureTypeTable[TextureType::NORMAL2D]= GL_TEXTURE_2D;
    _textureTypeTable[TextureType::ARRAY]= GL_TEXTURE_2D_ARRAY;
    _textureTypeTable[TextureType::CUBE_MAP]= GL_TEXTURE_CUBE_MAP;
    _textureTypeTable[TextureType::CUBE_MAP_POSITIVE_X]= GL_TEXTURE_CUBE_MAP_POSITIVE_X;
    _textureTypeTable[TextureType::CUBE_MAP_NEGATIVE_X]= GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
    _textureTypeTable[TextureType::CUBE_MAP_POSITIVE_Y]= GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
    _textureTypeTable[TextureType::CUBE_MAP_NEGATIVE_Y]= GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
    _textureTypeTable[TextureType::CUBE_MAP_POSITIVE_Z]= GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
    _textureTypeTable[TextureType::CUBE_MAP_NEGATIVE_Z]= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
    

    // Texture Formats
    _textureFormatTable[TextureFormat::RGB]= GL_RGB;
    _textureFormatTable[TextureFormat::RGBA]= GL_RGBA;
    _textureFormatTable[TextureFormat::DEPTH]= GL_DEPTH_COMPONENT;
    _textureFormatTable[TextureFormat::STENCIL]= GL_DEPTH_STENCIL;
    _textureFormatTable[TextureFormat::RED]= GL_RED;
    _textureFormatTable[TextureFormat::RGBA16F]= GL_RGBA16F;
    _textureFormatTable[TextureFormat::RGBA32F]= GL_RGBA32F;
    _textureFormatTable[TextureFormat::RGB16F]= GL_RGB16F;
    _textureFormatTable[TextureFormat::DEPTH16]= GL_DEPTH_COMPONENT16;
    _textureFormatTable[TextureFormat::DEPTH32]= GL_DEPTH_COMPONENT32F;
    _textureFormatTable[TextureFormat::DEPTH24_STENCIL8]= GL_DEPTH24_STENCIL8;
    _textureFormatTable[TextureFormat::DEPTH_STENCIL]= GL_DEPTH_STENCIL;

    // DataTypes
    _dataTypeTable[DataType::UNSIGNED_BYTE]= GL_UNSIGNED_BYTE;
    _dataTypeTable[DataType::BYTE]= GL_BYTE;
    _dataTypeTable[DataType::UNSIGNED_INT]= GL_UNSIGNED_INT;
    _dataTypeTable[DataType::UNSIGNED_SHORT]= GL_UNSIGNED_SHORT;
    _dataTypeTable[DataType::INT]= GL_INT;
    _dataTypeTable[DataType::SHORT]= GL_SHORT;
    _dataTypeTable[DataType::FLOAT]= GL_FLOAT;
    
#ifdef GL_DOUBLE
    _dataTypeTable[DataType::DOUBLE]= GL_DOUBLE;
#endif
    
#ifdef GL_UNSIGNED_INT_8_8_8_8_REV
   
    _dataTypeTable[DataType::UNSIGNED_INT_8_8_8_8_REV]= GL_UNSIGNED_INT_8_8_8_8_REV;

#else
    
    _dataTypeTable[DataType::UNSIGNED_INT_8_8_8_8_REV]= GL_UNSIGNED_INT;

#endif
    
    _dataTypeTable[DataType::UNSIGNED_INT_24_8]= GL_UNSIGNED_INT_24_8;

    // TextureValues
    _textureFilterTable[TextureFilter::NEAREST]= GL_NEAREST;
    _textureFilterTable[TextureFilter::LINEAR]= GL_LINEAR;
    _textureFilterTable[TextureFilter::LINEAR_MIPMAP_LINEAR]= GL_LINEAR_MIPMAP_LINEAR;
    _textureFilterTable[TextureFilter::LINEAR_MIPMAP_NEAREST]= GL_LINEAR_MIPMAP_NEAREST;
    _textureFilterTable[TextureFilter::NEAREST_MIPMAP_LINEAR]= GL_NEAREST_MIPMAP_LINEAR;
    _textureFilterTable[TextureFilter::NEAREST_MIPMAP_NEAREST]= GL_NEAREST_MIPMAP_NEAREST;
    
    // TexureWrap Table
    _textureWrapTable[TextureWrap::REPEAT]= GL_REPEAT;
    
    
    
#ifdef GL_CLAMP
    
    _textureWrapTable[TextureWrap::CLAMP]= GL_CLAMP;
    
#else
    
    _textureWrapTable[TextureWrap::CLAMP]= GL_CLAMP_TO_EDGE;
    
#endif
    
    
    
    
    _textureWrapTable[TextureWrap::REPEAT_MIRRORED]= GL_MIRRORED_REPEAT;
    _textureWrapTable[TextureWrap::CLAMP_TO_EDGE]= GL_CLAMP_TO_EDGE;
    
    _bufferDrawType[BufferDrawType::STREAM]= GL_STREAM_DRAW;
    _bufferDrawType[BufferDrawType::STATIC]= GL_STATIC_DRAW;
    _bufferDrawType[BufferDrawType::DYNAMIC]= GL_DYNAMIC_DRAW;
    
    _bufferTypeTable[BufferType::ARRAY]= GL_ARRAY_BUFFER;
    _bufferTypeTable[BufferType::ELEMENT_ARRAY]= GL_ELEMENT_ARRAY_BUFFER;

}

// Shader
void GraphicDeviceOpenGL::generateShader(Shader* shader){
    
    shader->_shaderID = glCreateProgram();
    
}

SUint GraphicDeviceOpenGL::createSubShader(const std::string& text, unsigned int type, Shader* shader){

    SUint shaderID = glCreateShader(type);
    
    if(shader == 0)
        std::cerr << "Error compiling shader type " << type << std::endl;
    
    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = (GLint) text.length();
    
    glShaderSource(shaderID, 1, p, lengths);
    glCompileShader(shaderID);
    
    checkShaderError(shaderID, GL_COMPILE_STATUS, false, "Error compiling shader!",true,shader);
    checkRenderError();
    
    return shaderID;
    

}
    
void GraphicDeviceOpenGL::bindShader(Shader* shader){
    
    glUseProgram(shader->_shaderID);
 
}

void GraphicDeviceOpenGL::releaseShader(Shader* shader){


    
    glDeleteProgram(shader->_shaderID);
    shader->_shaderID=-1;

    checkRenderError();
}

void GraphicDeviceOpenGL::attachSource(Shader* shader, const std::string& source, const SUint& type){
    
    if(type==ShaderType::VERTEX) shader->_subShaderIDs[type] = createSubShader(source,   GL_VERTEX_SHADER,shader);
    else if(type==ShaderType::FRAGMENT) shader->_subShaderIDs[type] = createSubShader(source,   GL_FRAGMENT_SHADER,shader);
   // else if(type==ShaderType::GEOMETRY) shader->_subShaderIDs[type] = createSubShader(source,   GL_GEOMETRY_SHADER,shader);

    glAttachShader(shader->_shaderID, shader->_subShaderIDs[type]);

}

void GraphicDeviceOpenGL::bindAttribLocation(Shader* shader, const SUint& location, const std::string& name){

    glBindAttribLocation(shader->_shaderID, location, name.c_str());

}
    
SInt GraphicDeviceOpenGL::getUniformLocation(Shader* shader, const std::string& name){
    
    return glGetUniformLocation(shader->_shaderID, name.c_str());
    
}
void GraphicDeviceOpenGL::unbindBuffer(SUint bufferType){
    
    glBindBuffer(_bufferTypeTable[bufferType], 0);

}


void GraphicDeviceOpenGL::linkShader( Shader* shader ){

    glLinkProgram(shader->_shaderID);
    checkShaderError(shader->_shaderID, GL_LINK_STATUS, true, "Error linking shader program",false,shader);
    
    glValidateProgram(shader->_shaderID);
    checkShaderError(shader->_shaderID, GL_LINK_STATUS, true, "Invalid shader program",false,shader);
    
    for(unsigned int i = 0; i < 4; i++){
    
        if(shader->_subShaderIDs[i]==-1) continue;
    
        glDetachShader(shader->_shaderID, shader->_subShaderIDs[i]);
        glDeleteShader(shader->_subShaderIDs[i]);
        
        shader->_subShaderIDs[i]=-1;
        
    }

}

void GraphicDeviceOpenGL::checkShaderError(SUint shaderID, SUint flag, bool isProgram, const std::string& errorMessage, bool printSource, Shader* shader){

    GLint success = 0;
    GLchar error[1024] = { 0 };
    
    if(isProgram)
        glGetProgramiv(shaderID, flag, &success);
    else
        glGetShaderiv(shaderID, flag, &success);
    
    if(success==0){
        
        if(printSource){
            
            std::cout << std::endl;
            Shader::printShaderSourceWithLineNumbers(shader->_vertexSource);
            std::cout << std::endl;
            Shader::printShaderSourceWithLineNumbers(shader->_fragSource);
            std::cout << std::endl;
        }
        
        if(isProgram) glGetProgramInfoLog(shaderID, sizeof(error), NULL, error);
        else glGetShaderInfoLog(shaderID, sizeof(error), NULL, error);
        
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }


}
    
// State
void GraphicDeviceOpenGL::setCullFace(const SUint& cullface){
    
    if(cullface==CullFace::NONE || cullface>=4){
    
        glDisable(GL_CULL_FACE);
    
    }else{
    
        glEnable(GL_CULL_FACE);
        glCullFace(_cullFaceTable[cullface-1]);
        
    }
    
}
    
    
void GraphicDeviceOpenGL::setRenderTargetToFramebuffer(FrameBuffer* buffer, RenderTarget* renderTarget){
    
    if(renderTarget->_renderTargetType==RENDERTARGET_TYPE_COLOR){
    
        GLint attachment = GL_COLOR_ATTACHMENT0 + renderTarget->_index;
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, _textureTypeTable[renderTarget->getTextureTarget()], renderTarget->getTexture()->getID() ,0);

        return;
    }
    
    
    if(renderTarget->_renderTargetType==RENDERTARGET_TYPE_DEPTH){
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _textureTypeTable[renderTarget->getTextureTarget()], renderTarget->getTexture()->getID() ,0);
        
        return;
    }
    
    
    if(renderTarget->_renderTargetType==RENDERTARGET_TYPE_STENCIL){
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _textureTypeTable[renderTarget->getTextureTarget()], renderTarget->getTexture()->getID() ,0);
        
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, _textureTypeTable[renderTarget->getTextureTarget()], renderTarget->getTexture()->getID() ,0);
        
        return;
    }
    

}

    
void GraphicDeviceOpenGL::setBlendFunc(const BlendFunc& blendFunc){
    
    glBlendFunc(_blendTable[blendFunc.src], _blendTable[blendFunc.dst]);
    glEnable(GL_BLEND);

}
    
    void GraphicDeviceOpenGL::setBlendingEnabled(const bool& enabled){
        
        if(enabled){
        
            glEnable(GL_BLEND);
            return;
        }

        glDisable(GL_BLEND);

        
    }
    
    void GraphicDeviceOpenGL::setDepthFunc( const SUint& depthFunc ){
        
        glDepthFunc(_depthFuncTable[depthFunc]);
        
    }
    
    void GraphicDeviceOpenGL::setDepthWritingEnabled(const bool& enabled){
        
        if(enabled){
        
            glDepthMask(GL_TRUE);
            return;

        }
        
        glDepthMask(GL_FALSE);
        
    }
    
    void GraphicDeviceOpenGL::setDepthTestEnabled(const bool& enabled){
        
        if(enabled){
        
            glEnable(GL_DEPTH_TEST);
            return;
        }

        glDisable(GL_DEPTH_TEST);
        
    }
    
    // Data
    void GraphicDeviceOpenGL::bindVertexBuffer(VertexBuffer* buffer){
    
        if(!buffer){
        
            return;
        }
        
        
        glBindBuffer(_bufferTypeTable[buffer->_type], buffer->_id);
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::bufferVertexBufferData(VertexBuffer* buffer){
    
        bindVertexBuffer(buffer);
        glBufferData(_bufferTypeTable[buffer->_type], buffer->_dataSize, buffer->_data, _bufferDrawType[buffer->_drawType]);
        checkRenderError();

    
    }
    
    void GraphicDeviceOpenGL::generateVertexBuffer(VertexBuffer* buffer){
    
        glGenBuffers(1, &buffer->_id);
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::releaseVertexBuffer(VertexBuffer* buffer){

        glDeleteBuffers(1, &buffer->_id);
        buffer->_id=0;
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::generateVertexArrayObject(VertexArrayObject* vao){
    
        checkRenderError();
        sirnicGenVertexArrays(1, &vao->_vaoID);
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::releaseVertexArrayObject(VertexArrayObject* vao){
    
        sirnicDeleteVertexArray(1, &vao->_vaoID);
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::bindVertexArrayObject(VertexArrayObject* vao){
    
        if(vao==NULL){
        
            sirnicBindVertexArray(0);
            return;
        }
        
        sirnicBindVertexArray(vao->getID());
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::bindTexture(Texture* texture, const SUint& location){
    
        if(!texture){
        
            // Possible bug if not using corresponding type
            glActiveTexture(GL_TEXTURE0+location);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            return;
        
        }
        
        glActiveTexture(GL_TEXTURE0+location);
        glBindTexture(_textureTypeTable[texture->getType()], texture->getID());

    }

    void GraphicDeviceOpenGL::generateTexture(Texture* texture){
       
        glGenTextures(1, &texture->_id);
    
    }
    
    void GraphicDeviceOpenGL::releaseTexture(Texture* texture){
    
        glDeleteTextures(1, &texture->_id);
        texture->_id=0;
    }
    
    
    void GraphicDeviceOpenGL::setTextureData(Texture* texture, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data){
    
        bindTexture(texture, 0);
        glTexImage2D(_textureTypeTable[texture->getType()], 0 , _textureFormatTable[internalFormat] , width , height , 0 , _textureFormatTable[dataFormat] , _dataTypeTable[texture->_dataType] , data);
        
        bindTexture(NULL, 0);
        if(checkRenderError()){
        
        
        }

    }
    
    void GraphicDeviceOpenGL::setCubeMapTextureData(Texture* texture, SUint side, SInt level, SInt internalFormat, SUint width, SUint height, SInt dataFormat, void* data){
    
        bindTexture(texture, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+side, 0 , _textureFormatTable[internalFormat] , width , height , 0 , _textureFormatTable[dataFormat] , _dataTypeTable[texture->_dataType] , data);
        
        bindTexture(NULL, 0);
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::setTextureFilter(Texture* texture){
        
        bindTexture(texture, 0);
        glTexParameteri(_textureTypeTable[texture->getType()], GL_TEXTURE_MAG_FILTER, _textureFilterTable[texture->_magFilter]);
        glTexParameteri(_textureTypeTable[texture->getType()], GL_TEXTURE_MIN_FILTER, _textureFilterTable[texture->_minFilter]);
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::setTextureWrap(Texture* texture){
    
        bindTexture(texture, 0);
        glTexParameteri(_textureTypeTable[texture->getType()], GL_TEXTURE_WRAP_S, _textureWrapTable[texture->_warp]);

        glTexParameteri(_textureTypeTable[texture->getType()], GL_TEXTURE_WRAP_T, _textureWrapTable[texture->_warp]);

        glTexParameteri(_textureTypeTable[texture->getType()], GL_TEXTURE_WRAP_R, _textureWrapTable[texture->_warp]);
     
        checkRenderError();

    }
    
    
    // Draw
    void GraphicDeviceOpenGL::drawElements(const SUint& drawType, const SUint& indicesCount, const void * indices){
    
        glDrawElements(_drawModeTable[drawType], indicesCount, GL_UNSIGNED_INT, indices);
        checkRenderError();

    
    }

    void GraphicDeviceOpenGL::drawArraysInstanced(const SUint& drawType,  const SUint& first,  const SUint& count, const SUint& instancecount){
    
        glDrawArraysInstanced(_drawModeTable[drawType], first, count, instancecount);
        checkRenderError();

    }
    
    void GraphicDeviceOpenGL::setVertexAttributeDivisor(const SUint& location, const SUint& divisor){
    
        glVertexAttribDivisor(location, divisor);
        checkRenderError();

    }
   
    void GraphicDeviceOpenGL::setVertexAttributePointer(const SUint& index, const SInt& size, const SUint& dataType, const bool& normalized, const SUint& stride, SInt pointer){
        
        glVertexAttribPointer(index, size, _dataTypeTable[dataType], normalized, stride,  (const void*) pointer);
        checkRenderError();

    }

    
    void GraphicDeviceOpenGL::enableVertexAttributeArray(const SUint& location){
    
        glEnableVertexAttribArray(location);
        checkRenderError();

    }

    
    void GraphicDeviceOpenGL::clearFrameBuffer(FrameBuffer* framebuffer, bool color, bool depth, bool stencil){
    
        int bits=0;
        
        if(color) bits|=GL_COLOR_BUFFER_BIT;
        if(depth) bits|=GL_DEPTH_BUFFER_BIT;
        if(stencil) bits|=GL_STENCIL_BUFFER_BIT;
        
        Color c= framebuffer->getClearColor();
        glClearColor(c.r, c.g, c.b, c.a);
        glClear(bits);
        
    }

    void GraphicDeviceOpenGL::generateFramebuffer(FrameBuffer* framebuffer){
    
        glGenFramebuffers(1, &framebuffer->_fboID);

    }
    
    void GraphicDeviceOpenGL::releaseFramebuffer(FrameBuffer* framebuffer){
    
        glDeleteBuffers(1, &framebuffer->_fboID);
    
    }
    
    void GraphicDeviceOpenGL::bindFrameBuffer(FrameBuffer* framebuffer){
    
        if(!framebuffer){
        
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return;
            
        }
    
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->_fboID);
        

    }

    void GraphicDeviceOpenGL::checkFrameBufferStatus(FrameBuffer* framebuffer){
    
        GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE){
            
            std::cout<<"Framebuffer status incomplete: "<< fboStatus << std::endl;
            
        }
    
    }

    
    void GraphicDeviceOpenGL::setViewPort(SInt x, SInt y, SInt w, SInt h){
    
        glViewport(x,y , w, h);
    
    }



}

bool _CheckRenderError(const char* file, int line)
{
    GLenum err ( glGetError() );
    
    while ( err != GL_NO_ERROR )
    {
        std::string error;
        switch ( err )
        {
            case GL_INVALID_OPERATION:  error="INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:       error="INVALID_ENUM";           break;
            case GL_INVALID_VALUE:      error="INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:      error="OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }
        std::cout << "GL_" << error.c_str() <<" - " << file << ":" << line << std::endl;
        err = glGetError();
        
        return true;
    }
    
    return false;
}

