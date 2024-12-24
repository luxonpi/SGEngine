

#include "Node.h"
#include "Shader.h"
#include "RenderLayer.h"

#define NODE_DIRTY_WORLD 1
#define NODE_DIRTY_BOUNDS 2
#define NODE_DIRTY_HIERARCHY 4
#define NODE_DIRTY_ALL (NODE_DIRTY_WORLD | NODE_DIRTY_BOUNDS | NODE_DIRTY_HIERARCHY)

namespace sge {

    Node::Node(){
        
        _tag=0;
                
        _parent=NULL;
        _childCount=0;
        _renderObject=new RenderObject(this);
        
        _dirtyBits |= NODE_DIRTY_HIERARCHY;
        _dirtyBits |= NODE_DIRTY_WORLD | NODE_DIRTY_BOUNDS;
        
        _transform.addListener(this);
        
    }
    
    void Node::transformChanged(Transform* transform){
    
        _dirtyBits |= NODE_DIRTY_WORLD;
        transformChanged();
    
    }
    
    Transform& Node::transform(){
    
        return _transform;
    
    }
    
    Node::~Node(){
    
        delete _renderObject;
    
    }
    
    // Static create method
    Node* Node::create(){
        
        Node* node= new Node();
        return node;
        
    }
    
    void Node::renderWithRenderer(Renderer* renderer, RenderState* renderState){}
    
    RenderObject* Node::getRenderObject(){
    
        return _renderObject;

    }
    
    void Node::setRenderObject(RenderObject* renderObject){
    
        if(renderObject==NULL) _renderObject=RenderObject::getNullObject();
        else _renderObject=renderObject;

    }
        
    const std::string& Node::getTypeName(){
        
        return _typeName;
        
    }
    
    void Node::setTypeName(const std::string& name){
        
        _typeName=name;
        
    }
    
    // Relation methods
    void Node::addChild(Node* child){
        
        // This node is already present in our hierarchy
        if (child->_parent == this){
            return;
        }
        
        // Remove first ff already part of other Node
        if (child->_parent){
            
            child->_parent->removeChild(child);
        }
        
        _dirtyBits |= NODE_DIRTY_BOUNDS;
        
        
        child->hierarchyChanged();
        child->_parent=this;
        _children.push_back(child);
        
    }
    
    void Node::removeFromParent(){
        
        if(_parent){
            
            _parent->removeChild(this);
            hierarchyChanged();
        }
        
    }
    
    void Node::removeAllChilds(){
        
        for(int i=0; i<_children.size(); i=0){
            
            _children[i]->_parent=NULL;
            _children[i]->hierarchyChanged();
            _children.erase(_children.begin()+i);
            
        }
        
    }
    
    void Node::removeChild(Node* child){
        
        child->_parent=NULL;
        
        for(int i=0; i<_children.size(); i++){
            
            if(_children[i]==child){
                
                _children.erase(_children.begin()+i);
                child->hierarchyChanged();
                
                return;
                
            }
            
        }
        
    }
    
    
    const Mat4& Node::getNormalMatrix(){
        
        if (_dirtyBits & NODE_DIRTY_WORLD) getModelMatrix();
        return _worldNormalMatrix;
        
    }
    
    const Mat4& Node::getModelMatrix(){
        
        if (_dirtyBits & NODE_DIRTY_WORLD){
            
            _dirtyBits &= ~NODE_DIRTY_WORLD;
            
            _worldMatrix= transform().getMatrix();
            
            if(_parent){
                
                _worldMatrix=_parent->getModelMatrix()*_worldMatrix;

            }

            // Our world matrix was just updated, so call getWorldMatrix() on all child nodes
            // to force their resolved world matrices to be updated.
            for (int i=0; i< _children.size(); i++){
                
                _children[i]->_dirtyBits |= NODE_DIRTY_WORLD;
                
            }
            
            _worldNormalMatrix=_worldMatrix;
            _worldNormalMatrix.inverse();
            _worldNormalMatrix.transpose();
            
        }
        
        return _worldMatrix;
        
    }
    
    
    
    
    const unsigned int Node::getNumberOfChilds(){
        
        return  (unsigned int) _children.size();
        
    }
    
   
    
    const std::string& Node::getID(){
        
        return _id;
        
    }
    
    // Setter
    void Node::setID(const std::string & idname){
        
        _id=idname;
        
    }
    
    void Node::setTag(const int& tag){
        
        _tag=tag;
        
    }
    
    void Node::setContentBox(const BoundingBox& box){
        
        _contentBox=box;
        
    }
    
    // Getter
    const int& Node::getTag(){
        
        return _tag;
        
    }
    
    std::vector<Node*>* Node::getChildren(){
        
        return &_children;
        
    }
    
    Node* Node::getParent(){
        
        return _parent;
    }
    
    void Node::updateBounds(){
        
        _boundingBox.min=_contentBox.min;
        _boundingBox.max=_contentBox.max;
        
        _boundingBox.transform(getModelMatrix());
        
        for (int i=0; i<_children.size(); i++) {
            
            _boundingBox.merge(_children[i]->getBoundingBox());
            
        }
        
        _boundingSphere.set(_boundingBox);
        
    }
    
    const BoundingBox& Node::getBoundingBox(){
        
        if (_dirtyBits & NODE_DIRTY_BOUNDS){
            
            _dirtyBits &= ~NODE_DIRTY_BOUNDS;
            updateBounds();
            
        }
        
        return _boundingBox;
    }
    
    const BoundingSphere& Node::getBoundingSphere(){
        
        if (_dirtyBits & NODE_DIRTY_BOUNDS){
            
            _dirtyBits &= ~NODE_DIRTY_BOUNDS;
            updateBounds();
            
        }
        
        return _boundingSphere;
        
    }
    
    const BoundingBox& Node::getContentBox(){
        
        return _contentBox;
        
    }
    
    
    void Node::hierarchyChanged(){
        
        // When our hierarchy changes our world transform is affected, so we must dirty it.
        _dirtyBits |= NODE_DIRTY_HIERARCHY;
        transformChanged();
        
    }
    
    void Node::transformChanged(){
        
        // Our local transform was changed, so mark our world matrices dirty.
        _dirtyBits |= NODE_DIRTY_WORLD | NODE_DIRTY_BOUNDS;
        
        for (int i=0; i<_children.size(); i++) {
            
            _children[i]->transformChanged();
            
        }
        
        _renderObject->transformChanged();
        
    }
    
    void Node::setBoundsDirty(){
        
        // Mark ourself and our parent nodes as dirty
        _dirtyBits |= NODE_DIRTY_BOUNDS;
        
        // Mark our parent bounds as dirty as well
        if (_parent)
            _parent->setBoundsDirty();
        
    }
    
    Node* Node::getChildForID(const std::string& idName, bool recursive){
    
        for (int i=0; i<_children.size(); i++) {
            
            if(_children[i]->_id==idName) return _children[i];
            
        }
        
        if(recursive){
        
            for (int i=0; i<_children.size(); i++) {
            
                Node* found= _children[i]->getChildForID(idName,recursive);
                if(found) return found;
            
            }
        
        }
        
        return NULL;
    
    }


    

} // Namespace end
