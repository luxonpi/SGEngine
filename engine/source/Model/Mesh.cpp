

#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "Mesh.h"

using namespace std;

namespace sge {
    
    std::unordered_map<std::string, Mesh*> Mesh::meshInstances;
 
    Mesh* Mesh::getInstancedMesh(std::string meshID){

        if(meshInstances.find(meshID)!=meshInstances.end()){
    
            return meshInstances[meshID];
        }

        return NULL;
    }


    void Mesh::insertInstancedMesh(Mesh* mesh, std::string key){
    
        meshInstances.insert(std::make_pair(key, mesh));
    
    }
    
    Mesh::Mesh(): Resource("mesh"){
    
        initWithFlags(MESH_NORMALS | MESH_COLORS | MESH_TEXCOORDS);
    
    }

    Mesh::Mesh(unsigned int attributeFlags): Resource("mesh"){
        
        initWithFlags(attributeFlags);
    
    }
    
    VertexArrayObject* Mesh::getVAO_PositionOnly(){
    
        return _vertexArrayObject_PositionOnly;
    
    }
    
    Mesh::Mesh(sge::VertexArrayObject* vao): Resource("mesh"){
    
        _vertexArrayObject=vao;
        
    }

    void Mesh::initWithFlags(unsigned int attributeFlags){
    
        _positionAttribute=NULL;
        _normalAttribute=NULL;
        _colorAttribute=NULL;
        _texCoordAttribute=NULL;
        _tangentsAttribute=NULL;
        _boneAttribute=NULL;
        _vertexArrayObject_PositionOnly=NULL;

        _vertexArrayObject= VertexArrayObject::create();
        
        _positionAttribute= VertexBuffer::create(&positions[0], 0);
       
        _vertexArrayObject->addAttributePointer(AttributePointer(_positionAttribute, 3,DataType::FLOAT, 0 ,0, POSITION_LOCATION));
        
        if (attributeFlags & MESH_BONES){
            
            _boneAttribute= VertexBuffer::create(&bones[0], 0);
            _vertexArrayObject->addAttributePointer(AttributePointer(_boneAttribute, 4,DataType::SHORT, sizeof(VertexBoneData), 0, BONE_ID_LOCATION));
            _vertexArrayObject->addAttributePointer(AttributePointer(_boneAttribute, 4,DataType::FLOAT, sizeof(VertexBoneData), sizeof(SShort)*4, BONE_WEIGHT_LOCATION));
            
            
        }
        
        
        
        if (attributeFlags & MESH_COLORS){

            _vertexArrayObject_PositionOnly= VertexArrayObject::create();
            _vertexArrayObject_PositionOnly->addAttributePointer(AttributePointer(_positionAttribute, 3,DataType::FLOAT, 0 ,0, POSITION_LOCATION));

            if (_boneAttribute){
                
                _vertexArrayObject_PositionOnly->addAttributePointer(AttributePointer(_boneAttribute, 4,DataType::SHORT, sizeof(VertexBoneData), 0, BONE_ID_LOCATION));
                _vertexArrayObject_PositionOnly->addAttributePointer(AttributePointer(_boneAttribute, 4,DataType::FLOAT, sizeof(VertexBoneData), sizeof(SShort)*4, BONE_WEIGHT_LOCATION));
                
                
            }
            
        }
        
        if (attributeFlags & MESH_COLORS){
            
            _colorAttribute= VertexBuffer::create(&colors[0], 0);
            _vertexArrayObject->addAttributePointer(AttributePointer(_colorAttribute, 3,DataType::FLOAT, 0,0, COLOR_LOCATION));
            
        }

        if (attributeFlags & MESH_TEXCOORDS){
            
            _texCoordAttribute= VertexBuffer::create(&texCoords[0], 0);
            _vertexArrayObject->addAttributePointer(AttributePointer(_texCoordAttribute, 2,DataType::FLOAT, 0,0, TEX_COORD_LOCATION));
            
        }
        
     
        if (attributeFlags & MESH_NORMALS){
            
            _normalAttribute= VertexBuffer::create(&normals[0], 0);
            _vertexArrayObject->addAttributePointer(AttributePointer(_normalAttribute, 3, DataType::FLOAT,0, 0, NORMAL_LOCATION));
            
        }

        if (attributeFlags & MESH_TANGENTS){
            
            _tangentsAttribute= VertexBuffer::create(&tangents[0], 0);
            _vertexArrayObject->addAttributePointer(AttributePointer(_tangentsAttribute, 3,DataType::FLOAT, 0,0, TANGENT_LOCATION));
            
        }
        
    
    }
    
    VertexArrayObject* Mesh::getVAO(){
    
        return _vertexArrayObject;

    }
    
    void Mesh::removeAttribute(unsigned int attributeFlags){
    
        if (attributeFlags & MESH_TANGENTS){
            
            _vertexArrayObject->removeAttributeForBuffer(_tangentsAttribute);
            delete _tangentsAttribute;
            _tangentsAttribute=NULL;
            
        }

        update();
    
    }

    void Mesh::update(){
    
        _vertexArrayObject->setIndicies(&indices[0], sizeof(indices[0]) * indices.size());
    
        if(_positionAttribute) _positionAttribute->setData(&positions[0],positions.size()*sizeof(positions[0]));
        if(_normalAttribute) _normalAttribute->setData(&normals[0],normals.size()*sizeof(normals[0]));
        if(_colorAttribute) _colorAttribute->setData(&colors[0],colors.size()*sizeof(colors[0]));
        if(_texCoordAttribute) _texCoordAttribute->setData(&texCoords[0],texCoords.size()*sizeof(texCoords[0]));
        if(_tangentsAttribute) _tangentsAttribute->setData(&tangents[0],tangents.size()*sizeof(tangents[0]));
        if(_boneAttribute) _boneAttribute->setData(&bones[0],bones.size()*sizeof(VertexBoneData));
        
        _vertexArrayObject->updateImmediately();

        if(_vertexArrayObject_PositionOnly){
            
            _vertexArrayObject_PositionOnly->setIndicies(&indices[0], sizeof(indices[0]) * indices.size());
            _vertexArrayObject_PositionOnly->updateImmediately();
            

        }
        
        Resource::sizeInByte=positions.size()*sizeof(positions[0]);
        Resource::sizeInByte+=normals.size()*sizeof(float)*3;
        Resource::sizeInByte+=colors.size()*sizeof(float)*3;
        Resource::sizeInByte+=tangents.size()*sizeof(float)*3;
        Resource::sizeInByte+=texCoords.size()*sizeof(float)*2;
        Resource::sizeInByte+=indices.size()*sizeof(SUint);
        Resource::sizeInByte+=bones.size()*sizeof(VertexBoneData);

        
    }
    
    void Mesh::setTexCoords(const std::vector<Vec2> texCoords){
    
        this->texCoords=texCoords;
        if(_texCoordAttribute) _texCoordAttribute->setDataSize(texCoords.size()*sizeof(texCoords[0]));
       
        update();

    }
    
    void Mesh::setColors(const std::vector<Vec3>& Colors){
    
        this->colors=Colors;
        if(_colorAttribute) _colorAttribute->setDataSize(Colors.size()*sizeof(colors[0]));
        _vertexArrayObject->updateImmediately();

    }

    
    void Mesh::clear(){
    
        indices.clear();
        positions.clear();
        normals.clear();
        tangents.clear();
        colors.clear();
        texCoords.clear();
        bones.clear();
        
        if(_positionAttribute) _positionAttribute->setDataSize(0);
        if(_normalAttribute) _normalAttribute->setDataSize(0);
        if(_colorAttribute) _colorAttribute->setDataSize(0);
        if(_texCoordAttribute) _texCoordAttribute->setDataSize(0);
        if(_tangentsAttribute) _tangentsAttribute->setDataSize(0);
        if(_boneAttribute) _boneAttribute->setDataSize(0);
       
        _vertexArrayObject->updateImmediately();
        _vertexArrayObject_PositionOnly->updateImmediately();

    }

    Mesh::~Mesh(){
    
        _vertexArrayObject_PositionOnly->clear();
        _vertexArrayObject_PositionOnly->destroy();
        _vertexArrayObject_PositionOnly=NULL;

        _vertexArrayObject->clear();
        _vertexArrayObject->destroy();
        _vertexArrayObject=NULL;
    
    }



}

