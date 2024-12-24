

#ifndef SGENGINE_NODE_H
#define SGENGINE_NODE_H

// Primitives
#include "Vec3.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

// Glm
#include "SPath.h"
#include "SBase.h"

// Render Classes
#include "Transform.h"
#include "Quaternion.h"
#include "RenderObject.h"

namespace sge {
    
    class RenderLayer;
    class Camera;
    class SceneGraph;
    
    class Node: public RenderVisiter, public Transform::Listener{
    
        friend RenderLayer;
        friend SceneGraph;
        friend RenderObject;

    protected:
    
        // Con- Destructor
        Node();
        Node(const Node& object);

        // Render stuff
        RenderObject* _renderObject;

        // General Infos
        std::string _typeName;
        std::string _id;
        
        void* _userData;
        std::map<std::string, int>* _tags;
        int _tag;
    
        // Relations
        std::vector<Node*> _children;
        unsigned int _childCount;
        Node* _parent;
    
        // Transformations
        Transform _transform;
        
        Mat4 _worldMatrix;
        Mat4 _worldNormalMatrix;

        // Content Info
        BoundingBox _contentBox;
        BoundingBox _boundingBox;
        BoundingSphere _boundingSphere;

        mutable int _dirtyBits;

        void updateBounds();
    
        virtual void hierarchyChanged();
        virtual void transformChanged();
        virtual void setBoundsDirty();
        
        virtual void transformChanged(Transform* transform);

        
    public:
    
        static Node* create();
        virtual ~Node();
        
        Transform& transform();

        // Rendering
        RenderObject* getRenderObject();
        void setRenderObject(RenderObject* renderObject);
        virtual void renderWithRenderer(Renderer* renderer, RenderState* renderState);
   
        // Relations
        const unsigned int getNumberOfChilds();
        virtual void removeChild(Node* child);
        virtual void removeAllChilds();
        virtual void removeFromParent();
        virtual void addChild(Node* child);
        std::vector<Node*>* getChildren();
        Node* getParent();
        
        // General Info
        const std::string& getTypeName();
        void setTypeName(const std::string& name);
        const int& getTag();
        const std::string& getID();
        
        // Transformation    
        const BoundingBox& getBoundingBox();
        const BoundingSphere& getBoundingSphere();
        const BoundingBox& getContentBox();

        const Mat4& getModelMatrix();
        const Mat4& getNormalMatrix();

        
        // Setter
        virtual void setID(const std::string & idname);
        virtual void setContentBox(const BoundingBox& box);
        virtual void setTag(const int& tag);

        Node* getChildForID(const std::string& idName, bool recursive);
    
    };
    
} // Namespace

#endif
