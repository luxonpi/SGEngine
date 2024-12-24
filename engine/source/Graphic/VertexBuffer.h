

#ifndef VertexBuffer_H
#define VertexBuffer_H

#include <stdio.h>
#include "SBase.h"
#include "GraphicDeviceOpenGL.h"

namespace sge {

    class AttributePointer;
    
    class VertexBuffer{

        friend GraphicDevice;
        friend GraphicDeviceOpenGL;
        
    public:
        
        SUint _id;
        unsigned long _dataSize;
        
        void* _data;
        SUint _drawType;
        SUint _type;

        bool _buffered;
        
        VertexBuffer();
        ~VertexBuffer();
        
    public:
        
        void clear();
        
        SUint getBufferID();
        static VertexBuffer* create(void* data, unsigned int dataSize);

        void setData(void* data, const unsigned long& size);
        
        void setDrawType(SUint type);
        void setType(SUint type);

        void setDataSize(unsigned long size);
        
        void bind();
        void bufferData();
        
    };

}

#endif
