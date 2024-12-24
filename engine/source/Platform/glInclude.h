

#ifndef GL_MAX_TEXTURE_UNITS
#define GL_MAX_TEXTURE_UNITS 5
#endif

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)

#ifdef _WIN64
//define something for Windows (64-bit only)
#endif


#elif __APPLE__
#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#define MOBILE_TARGET 1

#elif TARGET_OS_IPHONE
//#include <OpenGLES/ES2/gl.h>
//#include <OpenGLES/ES2/glext.h>

#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>

#define MOBILE_TARGET 1


#elif TARGET_OS_MAC
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
//#include <OpenGL/gl3ext.h>



#else
// Unsupported platform

#endif

#elif __linux
// linux

#elif __unix // all unices not caught above
// Unix

#elif __posix
// POSIX

#endif

// Glfunctoins
#ifndef __GL_FUNCTION_DEFINES__
#define __GL_FUNCTION_DEFINES__

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#ifdef _WIN64
//define something for Windows (64-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#define MOBILE_TARGET 1

#define SIRNIC_RGBA16F GL_RGBA16F_EXT

#elif TARGET_OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#define MOBILE_TARGET 1

#define SIRNIC_RGBA16F GL_RGBA16F_EXT

inline void sirnicGenVertexArrays(const GLuint& count, GLuint* bufferId ){
    
    glGenVertexArraysOES(count, bufferId);
    
}


inline void sirnicBindVertexArray(const GLint& bufferId){
    
    glBindVertexArrayOES(bufferId);
    
}

inline void sirnicDeleteVertexArray(const GLuint& count, GLuint* bufferId){
    
    glDeleteVertexArraysOES(count, bufferId);
    
    
}

inline void sirnicVertexAttribDivisor(const GLuint& index, const GLuint& divisor){
    
    glVertexAttribDivisorEXT(index, divisor);

}



inline void sirnicDrawElementsInstanced(const GLenum& mode, const GLsizei& count, const GLenum& type, const GLvoid *indices, const GLsizei& instanceCount){

    glDrawElementsInstancedEXT(mode, count, type, indices, instanceCount  );

}


//#define GL_RED GL_RED_EXT

#elif TARGET_OS_MAC

#define SIRNIC_RGBA16F GL_RGBA16F_ARB
#define MULTIPLE_RENDER_TARGETS
#define TEXTURE_ARRAY

inline void sirnicDrawElementsInstanced(const GLenum& mode, const GLsizei& count, const GLenum& type, const GLvoid *indices, const GLsizei& instanceCount){
    
    glDrawElementsInstancedARB(mode, count, type, indices, instanceCount );
    
}

inline void sirnicVertexAttribDivisor(const GLuint& index, const GLuint& divisor){

    glVertexAttribDivisorARB(index, divisor);

}

inline void sirnicBindVertexArray(const GLint& bufferId){

    //  glBindVertexArray(bufferId);
    glBindVertexArray(bufferId);

}

inline void sirnicGenVertexArrays(const GLuint& count, GLuint* bufferId ){
    
    glGenVertexArrays(count, bufferId);
    
}

inline void sirnicDeleteVertexArray(const GLuint& count, GLuint* bufferId){

    glDeleteVertexArrays(count, bufferId);
    
    
}

#else
// Unsupported platform
#endif
#elif __linux
// linux
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif


#endif

