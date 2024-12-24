

#ifndef SGENGINE_VERTEXARRAYOBJECT_H
#define SGENGINE_VERTEXARRAYOBJECT_H

#include <stdio.h>
#include <unordered_map>
#include <memory>

#include "SBase.h"
#include "VertexBuffer.h"
#include "GraphicDeviceOpenGL.h"

namespace sge {
    class Mesh;
    
    class AttributePointer{
    
    public:
        
        VertexBuffer* buffer;
        unsigned int position;
        unsigned int componentSize;
        unsigned int stride;
        unsigned int pointer;
        SUint dataType;
        bool normalized;
        int divisor;

        AttributePointer(VertexBuffer* pBuffer,SUint pComponentSize,SUint pdataType, SUint pStride, SUint ppointer, SUint pPosition){
        
            buffer=pBuffer;
            position=pPosition;
            componentSize=pComponentSize;
            stride=pStride;
            pointer=ppointer;
            dataType=pdataType;
            normalized=false;
            divisor=0;
        }
    
    };
    
    class VertexArrayObject{

        friend GraphicDevice;
        friend GraphicDeviceOpenGL;
        
        protected:
    
        static VertexArrayObject* _boundVAO;
    
            std::vector<AttributePointer> _attributePointer;

            VertexArrayObject();
            ~VertexArrayObject();
        
            unsigned int _updatePriotity;
    
            void* _indiciesData;
            unsigned long _indiciesSize;
        
            VertexBuffer* _indiciesBuffer;
    
        public:
        
            void clear();
        
            //VertexArrayObject* clone();
            void copy(VertexArrayObject* vao);
        
            SUint _vaoID;
            SUint getID();

            bool update;
        
            void bind();
            void unbind();
    
            void setIndicies(void* indicies, unsigned long size);

            static VertexArrayObject* create();
        
            AttributePointer* getAttributePointerForBuffer(VertexBuffer* vertexBuffer);
        
            void addAttributePointer(AttributePointer attributePointer);
            void removeAttributeForBuffer(VertexBuffer* vertexBuffer);

            void updateImmediately();
            void updateWithPriority(unsigned int priotity);
        
        
            void destroy();
    
    };

}

#endif