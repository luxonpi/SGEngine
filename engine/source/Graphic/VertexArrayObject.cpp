    

#include "VertexArrayObject.h"
#include "Mesh.h"
#include "Director.h"
#include "glInclude.h"

namespace sge {
    
    VertexArrayObject* VertexArrayObject::_boundVAO=NULL;


    VertexArrayObject::VertexArrayObject(){

        _vaoID = 0;
        _indiciesData=NULL;
        _indiciesSize=0;
       
        // Create the VAO
        Director::getInstance()->getGraphicDevice()->generateVertexArrayObject(this);

        _indiciesBuffer= VertexBuffer::create(NULL, 0);
        _indiciesBuffer->setType(BufferType::ELEMENT_ARRAY);
        Director::getInstance()->getGraphicDevice()->generateVertexBuffer(_indiciesBuffer);
    
        checkRenderError();

        update=false;
        
    }
    
    void VertexArrayObject::clear(){
    
        _attributePointer.clear();
        _indiciesData=NULL;
        _indiciesSize=0;

        _indiciesBuffer->clear();
        // to do
        // if last owner of vertex buffer -> release them
        
    }
    
    void VertexArrayObject::copy(VertexArrayObject* vao){
        
        clear();
        
        for (int i=0; i<vao->_attributePointer.size(); i++) {
    
                AttributePointer ap= vao->_attributePointer[i];
                addAttributePointer(ap);
        
        }
        
        setIndicies(vao->_indiciesData, vao->_indiciesSize);
        
        updateImmediately();
        
    }
    
    VertexArrayObject::~VertexArrayObject(){}

    VertexArrayObject* VertexArrayObject::create(){

        return new VertexArrayObject();
    
    }
    
    void VertexArrayObject::setIndicies(void* indicies, unsigned long size){
    
        _indiciesData= indicies;
        _indiciesSize= size;
        
        bind();

        _indiciesBuffer->setData(indicies, size);
        _indiciesBuffer->bufferData();
        
        checkRenderError();
        
        unbind();
        Director::getInstance()->getGraphicDevice()->unbindBuffer(BufferType::ELEMENT_ARRAY);
    
    }
    
    void VertexArrayObject::bind(){
        
        if(_boundVAO) _boundVAO->unbind();
    
        _boundVAO=this;
        Director::getInstance()->getGraphicDevice()->bindVertexArrayObject(this);

    }
    
    void VertexArrayObject::unbind(){
    
        Director::getInstance()->getGraphicDevice()->bindVertexArrayObject(NULL);
        _boundVAO=NULL;
        
    }
    
    void VertexArrayObject::updateWithPriority(unsigned int priotity){
    
        updateImmediately();
        
    }
    
    
    void VertexArrayObject::updateImmediately(){
        
        GraphicDevice* gDevice=Director::getInstance()->getGraphicDevice();

        update=true;
        bind();
        
        VertexBuffer* buffer=NULL;
        
        for (int i=0; i<_attributePointer.size(); i++) {
            
            AttributePointer* ap= &_attributePointer[i];
          
            if(ap->componentSize==16){
            
                ap->buffer->bind();
                ap->buffer->bufferData();
            
                glBindBuffer(GL_ARRAY_BUFFER, ap->buffer->getBufferID());

                int pos= ap->position;

                for (unsigned int i = 0; i < 4 ; i++) {
                    glEnableVertexAttribArray(pos + i);
                    glVertexAttribPointer(pos + i, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4,
                                          (const GLvoid*)(sizeof(GLfloat) * i * 4));
                    sirnicVertexAttribDivisor(pos + i, 1);
                }
                
        
                checkRenderError();

                continue;
            
            }else if(ap->componentSize==9){
            
                ap->buffer->bind();
                ap->buffer->bufferData();
                
                glBindBuffer(GL_ARRAY_BUFFER, ap->buffer->getBufferID());

                int pos= ap->position;
                
                for (unsigned int i = 0; i < 3 ; i++) {
                    glEnableVertexAttribArray(pos + i);
                    glVertexAttribPointer(pos + i, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3 * 3,
                                          (const GLvoid*)(sizeof(GLfloat) * i * 3));
                    sirnicVertexAttribDivisor(pos + i, 1);
                    
                }
                
            
                checkRenderError();

                continue;

            }
            
    
            if(buffer!=ap->buffer){
                ap->buffer->bind();
                ap->buffer->bufferData();
                buffer=ap->buffer;
            }
            checkRenderError();
            
            // Set attribute pointer
            gDevice->enableVertexAttributeArray(ap->position);
            gDevice->setVertexAttributePointer(ap->position, ap->componentSize, ap->dataType, ap->normalized, ap->stride, ap->pointer);
            checkRenderError();
            
            if(ap->divisor!=0){
            
                gDevice->setVertexAttributeDivisor(ap->position, ap->divisor);

            
            }
            
        }
        
        // Upload indices
        if(_indiciesSize>0 && _indiciesData!=NULL){

            _indiciesBuffer->setData(_indiciesData, _indiciesSize);
            _indiciesBuffer->bufferData();

        }
        
        checkRenderError();
 
        unbind(); 
        gDevice->unbindBuffer(BufferType::ARRAY); 
        gDevice->unbindBuffer(BufferType::ELEMENT_ARRAY);
        
        checkRenderError();
 

    
    }
    
    AttributePointer* VertexArrayObject::getAttributePointerForBuffer(VertexBuffer* vertexBuffer){
    
        for (int i=0; i<_attributePointer.size(); i++) {
            
            if(_attributePointer[i].buffer==vertexBuffer) return &_attributePointer[i];
            
        }
    
        return NULL;
    }

    void VertexArrayObject::removeAttributeForBuffer(VertexBuffer* vertexBuffer){
    
        for (int i=0; i<_attributePointer.size(); i++) {
            
            if(_attributePointer[i].buffer==vertexBuffer){
                
                _attributePointer.erase(_attributePointer.begin()+i);
                break;
            
            
            }
            
        }
        
    
    }
    
    void VertexArrayObject::addAttributePointer(AttributePointer attributePointer){
    
        _attributePointer.push_back(attributePointer);
        
    }

    SUint VertexArrayObject::getID(){
    
        return _vaoID;
    
    }
    
  
    void VertexArrayObject::destroy(){
        
        
        
    }

}


