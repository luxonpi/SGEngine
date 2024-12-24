

#ifndef SGENGINE_MESH_H
#define SGENGINE_MESH_H

#include <string>
#include <vector>
#include <unordered_map>

#include "SMath.h"

#include "MeshData.h"

#include "Shader.h"
#include "Texture.h"
#include "BoundingBox.h"

#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "Material.h"
#include "Resources.h"

#define MESH_NORMALS 1
#define MESH_COLORS 2
#define MESH_TEXCOORDS 4
#define MESH_TANGENTS 8
#define MESH_BONES 16
#define MESH_POSONLY 32

namespace sge {

    class Mesh: public Resource{

    public:

        VertexArrayObject* _vertexArrayObject;
        VertexArrayObject* _vertexArrayObject_PositionOnly;

        static std::unordered_map<std::string, Mesh*> meshInstances;
    
        VertexBuffer* _positionAttribute;
        VertexBuffer* _normalAttribute;
        VertexBuffer* _colorAttribute;
        VertexBuffer* _texCoordAttribute;
        VertexBuffer* _tangentsAttribute;
        VertexBuffer* _boneAttribute;
        
        void initWithFlags(unsigned int attributeFlags);

    public:
        
        void removeAttribute(unsigned int attributeFlags);
        
        Mesh(unsigned int attributeFlags);
        Mesh(sge::VertexArrayObject* vao);

        Mesh();
        ~Mesh();
        
        std::vector<Vec3> positions;
        std::vector<Vec2> texCoords;
        std::vector<Vec3> normals;
        std::vector<Vec3> colors;
        std::vector<Vec3> tangents;
        
        std::vector<VertexBoneData> bones;
        std::vector<SUint> indices;
        
        VertexArrayObject* getVAO();
        VertexArrayObject* getVAO_PositionOnly();

        // Build from fileName, mesh name and  meshNumber
        std::string meshID;
    
        static Mesh* getInstancedMesh(std::string meshID);
        static void insertInstancedMesh(Mesh* mesh, std::string key);
    
        BoundingBox contentBox;
        Material material;
    
        static Mesh* makeCube();
        static Mesh* cube;
        static Mesh* makePlane();
        static Mesh* plane;
        static Mesh* makeSphere();
        static Mesh* sphere;

        
        static Mesh* getStaticMesh(std::string name);
        static void tintMesh(const Color& color, Mesh* mesh);
       
        void setTexCoords(const std::vector<Vec2> texCoords);
        void setColors(const std::vector<Vec3>& Colors);
        
        std::string name;
        
        virtual void update();
        void clear();

    };
}

#endif
