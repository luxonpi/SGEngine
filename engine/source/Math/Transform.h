

#ifndef SGENGINE_TRANSFORMATION_H
#define SGENGINE_TRANSFORMATION_H

#include "SBase.h"
#include "Quaternion.h"
#include "Matrix.h"

namespace sge {
    
class Transform{
    
public:
    
    enum MatrixDirtyBits{
        
        DIRTY_TRANSLATION   = 0x01,
        DIRTY_SCALE         = 0x02,
        DIRTY_ROTATION      = 0x04,
        DIRTY_NOTIFY        = 0x08
        
    };
    
    class Listener{
        
    public:
        
        virtual ~Listener() { }
        virtual void transformChanged(Transform* transform) = 0;
    };

private:
    
    mutable Quaternion _rotation;
    
    mutable Vec3 _translation;
    mutable Vec3 _scale;
    
    mutable Mat4 _matrix;
    
    std::list<Listener*> _listeners;
    mutable char _matrixDirtyBits;

public:
    
    Transform();
    ~Transform();
    
    Transform operator+(const Transform& trans);

    void dirty(char matrixDirtyBits);
    bool isDirty();

    // Listener
    void addListener(Transform::Listener* listener, long cookie = 0);
    void removeListener(Transform::Listener* listener);
    void transformChanged();

    
    // Setter
    void setTranslationX(float x);
    void setTranslationY(float y);
    void setTranslationZ(float z);
    void setTranslation(float x, float y, float z);
    void setTranslation(const Vec3& translation);

    void setScale(const Vec3& scale);
    void setScale(float scale);

    void setScale(float scaleX, float scaleY, float scaleZ);
    void setScaleX(float scale);
    void setScaleY(float scale);
    void setScaleZ(float scale);

    void setRotation(float qx, float qy, float qz, float qw);
    void setRotation(const Quaternion& rotation);
    void setRotation(const Vec3& axis, float angle);
    void setRotation(const Vec3& euler);
    void setRotationFromDirection(const Vec3& directionNormalized);
    
    
    // Getter
    Vec3 getTranslation();
    Quaternion getRotation();
    Vec3 getScale();


    const Mat4& getMatrix();
    Mat4 getRotationMatrix();

    



};
    
}

#endif
