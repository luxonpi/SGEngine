

#ifndef SGENGINE_CAMERA_H
#define SGENGINE_CAMERA_H

#include "Frustum.h"
#include "Rectangle.h"
#include "Vec2.h"
#include "Entity.h"
#include "CameraFilter.h"

namespace sge{

    class Camera: public Entity{
    
    public:
    
        enum Type{
        
            PERSPECTIVE = 1,
            ORTHOGRAPHIC = 2
        };

    private:
    
        Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
        Camera(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane);
    
        Camera& operator=(const Camera&);
        
        Camera::Type _type;
        float _fieldOfView;
        float _zoom[2];
        float _aspectRatio;
        float _nearPlane;
        float _farPlane;
    
        Vec3 direction;
    
        mutable  Mat4 _view;
        mutable  Mat4 _projection;
        mutable  Mat4 _viewProjection;
        mutable  Mat4 _inverseView;
        mutable  Mat4 _inverseViewProjection;
        mutable  Mat4 _inverseProjection;

        mutable Frustum _bounds;
        mutable long _bits;
    
        Vec3 _up;
        
        std::vector<CameraFilter*> _cameraFilter;
    
    public:
        bool _middle;
    
        virtual ~Camera();
        
        void addCameraFilter(CameraFilter* filter);
        void removeCameraFilter(CameraFilter* filter);


        static Camera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
        static Camera* createOrthographic(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane);
        static Camera* create2D(float width, float height);
    
        void setWindowsSize(float width, float height);

        Camera::Type getCameraType() const;

        float getFieldOfView() const;
        void setFieldOfView(float fieldOfView);

        float getZoomX() const;
        void setZoomX(float zoomX);
        float getZoomY() const;
        void setZoomY(float zoomY);

        float getAspectRatio() const;
        void setAspectRatio(float aspectRatio);

        float getNearPlane() const;
        void setNearPlane(float nearPlane);
        
        float getFarPlane() const;
        void setFarPlane(float farPlane);

        void setProjectionMatrix(const Mat4& matrix);
        void setViewMatrix(const Mat4& view);

        void resetProjectionMatrix();
    
        const Mat4& getViewProjectionMatrix();
        const Mat4& getInverseViewProjectionMatrix();
        const Mat4& getInverseProjectionMatrix();

        const Mat4& getViewMatrix();
        const Mat4& getInverseViewMatrix();
        const Mat4& getProjectionMatrix();
        const Frustum& getFrustum();

        void project(const Rectangle& viewport, const Vec3& position, float* x, float* y, float* depth = NULL) ;
        void project(const Rectangle& viewport, const Vec3& position, Vec2* out) ;
        void project(const Rectangle& viewport, const Vec3& position, Vec3* out) ;
        void unproject(const Rectangle& viewport, float x, float y, float depth, Vec3* dst) ;
        void pickRay(const Rectangle& viewport, float x, float y, Ray* dst) ;

        void copy(Camera* camera);

        void setUp(const Vec3& up);
        Vec3 getUp();
        
        Vec3 getDirection();
    
        virtual void setPosition(Vec3 pos);
        virtual void setDirection(Vec3 dir);
    
        virtual void lookAt(Vec3 point);
    
    };

}

#endif
