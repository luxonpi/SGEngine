

#include "VertexBuffer.h"
#include "Director.h"
#include "VertexArrayObject.h"

namespace sge {
    
    VertexBuffer::VertexBuffer(){
       
        _id=0;
        _data=NULL;
        _dataSize=0;
        _drawType=BufferDrawType::STATIC;
        _type= BufferType::ARRAY;
        _buffered=false;

        Director::getInstance()->getGraphicDevice()->generateVertexBuffer(this);

    }
    
    void VertexBuffer::clear(){
    
        _data=NULL;
        _dataSize=0;
    
    }
    
    VertexBuffer::~VertexBuffer(){
    
        Director::getInstance()->getGraphicDevice()->releaseVertexBuffer(this);

    }

    VertexBuffer* VertexBuffer::create(void* data, unsigned int dataSize){
    
        VertexBuffer* buffer= new VertexBuffer();
        buffer->setData(data,dataSize);
        return buffer;
    
    }
    
    void VertexBuffer::setData(void* data, const unsigned long& size){
    
        _data=data;
        _dataSize=size;

    }
    
    void VertexBuffer::setDataSize(unsigned long size){
    
        _dataSize=size;
        
    }
    
    void VertexBuffer::setDrawType(SUint type){
    
        _drawType=type;
    
    }
    
    void VertexBuffer::setType(SUint type){
    
        _type=type;
    
    }
    
    
    void VertexBuffer::bind(){
    
        Director::getInstance()->getGraphicDevice()->bindVertexBuffer(this);
        checkRenderError();

    }
    
    void VertexBuffer::bufferData(){
        
        Director::getInstance()->getGraphicDevice()->bufferVertexBufferData(this);
        _buffered=true;
        checkRenderError();

    }
    

    SUint VertexBuffer::getBufferID(){
    
        return _id;
    
    }



}