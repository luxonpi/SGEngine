

#include "Transform.h"

namespace sge {

Transform::Transform(){

    _matrixDirtyBits|=DIRTY_TRANSLATION;

    _rotation.set(0,0,0,1);
    _translation.set(0, 0, 0);
    _scale.set(1, 1, 1);
    
}

Transform::~Transform(){}
   
void Transform::addListener(Transform::Listener* listener, long cookie){
    
    _listeners.push_back(listener);

}
    
void Transform::removeListener(Transform::Listener* listener){
    
    for (std::list<Listener*>::iterator itr = _listeners.begin(); itr != _listeners.end(); ++itr){
            
        if ((*itr) == listener){
                
                _listeners.erase(itr);
                break;
        }
    }

}
    
void Transform::transformChanged(){
    
    for (std::list<Listener*>::iterator itr = _listeners.begin(); itr != _listeners.end(); ++itr){
            
        Listener* l = *itr;
        l->transformChanged(this);
    }
    
}

    
void Transform::dirty(char matrixDirtyBits){
    
        _matrixDirtyBits |= matrixDirtyBits;
    
        transformChanged();

//        if (isTransformChangedSuspended())
//        {
//            if (!isDirty(DIRTY_NOTIFY))
//            {
//             //   suspendTransformChange(this);
//            }
//        }
//        else
//        {
//        }
}
    
bool Transform::isDirty(){
    
    return _matrixDirtyBits!=0;

}
    

const Mat4& Transform::getMatrix(){
    
    if (_matrixDirtyBits & (DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE)){
          
        bool hasScale = _scale!=Vec3(1, 1, 1);
        bool hasRotation = !_rotation.isIdentity();
        
        Mat4::createTranslation(_translation, &_matrix);
        
        if (hasRotation){
                
            _matrix.rotate(_rotation);
            
        }
            
        if (hasScale){
            
            _matrix.scale(_scale);
                
        }
            
        _matrixDirtyBits &= ~(DIRTY_TRANSLATION | DIRTY_ROTATION | DIRTY_SCALE);
    }
        
    return _matrix;

}
    
    
    Mat4 Transform::getRotationMatrix(){
    
        Mat4 der;
        Mat4::createRotation(Vec3(0, 1, 0), 0, &der);
        return der;
        
    }

    
    void Transform::setTranslationX(float x){
    
        _translation.x=x;
        dirty(DIRTY_TRANSLATION);
    }
    
    void Transform::setTranslationY(float y){
      
        _translation.y=y;
        dirty(DIRTY_TRANSLATION);
    
    }
    
    
    void Transform::setTranslationZ(float z){
    
        _translation.z=z;
        dirty(DIRTY_TRANSLATION);

    
    }
    
    void Transform::setTranslation(float x, float y, float z){
     
        _translation.set(x,y,z);
        dirty(DIRTY_TRANSLATION);
    
    }
    
    void Transform::setTranslation(const Vec3& translation){
    
        _translation=translation;
        dirty(DIRTY_TRANSLATION);
        
    }
    
    void Transform::setScale(float scale){
    
        _scale.set(scale, scale, scale);
        dirty(DIRTY_SCALE);

    }

    void Transform::setScale(const Vec3& scale){
        
        _scale=scale;
        dirty(DIRTY_SCALE);
        
    }
    
    void Transform::setScale(float scaleX, float scaleY, float scaleZ){
    
        _scale.set(scaleX, scaleY, scaleZ);
        dirty(DIRTY_SCALE);
    
    }
    
    void Transform::setScaleX(float scale){
    
        _scale.x=scale;
        dirty(DIRTY_SCALE);
    
    }
    
    void Transform::setScaleY(float scale){
    
        _scale.y=scale;
        dirty(DIRTY_SCALE);
    }
    
    void Transform::setScaleZ(float scale){
       
        _scale.z=scale;
        dirty(DIRTY_SCALE);
    
    }
    
    void Transform::setRotation(float qx, float qy, float qz, float qw) {
    
        _rotation.set(qx, qy, qz, qw);
        dirty(DIRTY_ROTATION);

    }
    
    void Transform::setRotation(const Quaternion& rotation) {
    
        _rotation=rotation;
        dirty(DIRTY_ROTATION);

    }
    
    void Transform::setRotation(const Vec3& axis, float angle) {
    
        _rotation.set(axis, angle);
        dirty(DIRTY_ROTATION);

    }
    
    void Transform::setRotation(const Vec3& euler) {
    
        _rotation.set(euler);
        dirty(DIRTY_ROTATION);

    }
    
    void Transform::setRotationFromDirection(const Vec3& directionNormalized){
    
        _rotation.lookRotation(directionNormalized);
        dirty(DIRTY_ROTATION);

    }

    
    
    // Getter
    Vec3 Transform::getTranslation() { return _translation; }
    Quaternion Transform::getRotation() { return _rotation; }
    Vec3 Transform::getScale(){ return _scale; }

    
//const glm::mat4& Transform::getMatrix(){
//    
//    if(!_matrixDirty) return _model;
//    
//    
//    _matrixDirty=false;
//    _model = glm::mat4(1.0);
//
//    Vec3 Origin= Vec3(_pivot.x*(contentBox.max.x-contentBox.min.x),
//                      _pivot.y*(contentBox.max.y-contentBox.min.y),
//                      _pivot.z*(contentBox.max.z-contentBox.min.z));
//    
//    _model= glm::translate(_model,glm::vec3(-Origin.x, -Origin.y,-Origin.z));
//
//    _model= glm::translate(_model,glm::vec3(_position.x, _position.y,_position.z));
//    
//    
//    _model= glm::translate(_model,glm::vec3(Origin.x, Origin.y,Origin.z));
//
//    _model= glm::rotate(_model, float(_rotation.x/180*M_PI), glm::vec3(1,0,0));
//    _model= glm::rotate(_model, float(_rotation.y/180*M_PI), glm::vec3(0,1,0));
//    _model= glm::rotate(_model, float(_rotation.z/180*M_PI), glm::vec3(0,0,1));
//  
//    _model= glm::scale(_model,glm::vec3(_scaleAll.x,_scaleAll.y,_scaleAll.z));
//
//    _model= glm::translate(_model,glm::vec3(-Origin.x, -Origin.y, -Origin.z));
//    
//    return _model;
//
//}

}
