

#include "SCamera.h"
#include "SMath.h"

// Camera dirty bits
#define CAMERA_DIRTY_VIEW 1
#define CAMERA_DIRTY_PROJ 2
#define CAMERA_DIRTY_VIEW_PROJ 4
#define CAMERA_DIRTY_INV_VIEW 8
#define CAMERA_DIRTY_INV_VIEW_PROJ 16
#define CAMERA_DIRTY_BOUNDS 32
#define CAMERA_DIRTY_ALL (CAMERA_DIRTY_VIEW | CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS)

// Other misc camera bits
#define CAMERA_CUSTOM_PROJECTION 64
#define CAMERA_CUSTOM_VIEW 128

namespace sge{
    
    void Camera::addCameraFilter(CameraFilter* filter){
    
        if(std::find(_cameraFilter.begin(), _cameraFilter.end(), filter)==_cameraFilter.end()) return;
        
        _cameraFilter.push_back(filter);
        
    
    }
    
    void Camera::removeCameraFilter(CameraFilter* filter){

        for (int i=0; i<_cameraFilter.size(); i++) {
            
            if(filter==_cameraFilter[i]){
            
                _cameraFilter.erase(_cameraFilter.begin()+i);
                i--;
            
            }
            
        }
    
    }
    
    void Camera::copy(Camera* camera){
        
        setPosition(camera->transform().getTranslation());
        setDirection(camera->getDirection());

        _type=camera->_type;
        _farPlane=camera->_farPlane;
        _nearPlane=camera->_nearPlane;
        
        _aspectRatio=camera->_aspectRatio;
        _fieldOfView=camera->_fieldOfView;
        _zoom[0]=camera->_zoom[0];
        _zoom[1]=camera->_zoom[1];
        _up=camera->_up;
        _middle=camera->_middle;

        _bits |=CAMERA_DIRTY_ALL;
        _bits |=CAMERA_DIRTY_VIEW|  CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

    }
    
    
    void Camera::lookAt(Vec3 point){
        
        direction=Vec3(point-transform().getTranslation()).normalized();
        _bits |=CAMERA_DIRTY_VIEW|  CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

        
    }
    
    
    void Camera::setPosition(Vec3 pos){
        
        _transform.setTranslation(pos);
        _bits |=CAMERA_DIRTY_VIEW|   CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

        
    }
    
    

    void Camera::setDirection(Vec3 dir){
        
        direction=dir;
        _bits |=CAMERA_DIRTY_VIEW|   CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

        
        
    }
    
    Vec3 Camera::getDirection(){
        
        return direction;
        
    }


Camera::Camera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
    : _type(PERSPECTIVE), _fieldOfView(fieldOfView), _aspectRatio(aspectRatio), _nearPlane(nearPlane), _farPlane(farPlane),
    _bits(CAMERA_DIRTY_ALL)
{
    
    _zoom[0] = 0;
    _zoom[1] = 0;
    _up.set(0, 1, 0);
    setDirection(Vec3(0, 0, -1));
    setPosition(Vec3(0, 0, 0));
    _middle=false;

}

Camera::Camera(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane)
    : _type(ORTHOGRAPHIC), _aspectRatio(aspectRatio), _nearPlane(nearPlane), _farPlane(farPlane),
	_bits(CAMERA_DIRTY_ALL)
{
    // Orthographic camera.
    _zoom[0] = zoomX;
    _zoom[1] = zoomY;
    _up.set(0, 1, 0);
    setDirection(Vec3(0, 0, -1));
    setPosition(Vec3(0, 0, 0));
    _middle=false;
}

Camera::~Camera(){}
    

Camera* Camera::createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    return new Camera(fieldOfView, aspectRatio, nearPlane, farPlane);
}

Camera* Camera::createOrthographic(float zoomX, float zoomY, float aspectRatio, float nearPlane, float farPlane)
{
    return new Camera(zoomX, zoomY, aspectRatio, nearPlane, farPlane);
}


Camera* Camera::create2D(float width, float height){
    
    return new Camera(width, height, height/width, -1, 1);
    
}
    
void Camera::setWindowsSize(float width, float height){

    _zoom[0] = width;
    _zoom[1] = height;
    
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

}


Camera::Type Camera::getCameraType() const
{
    return _type;
}

float Camera::getFieldOfView() const
{

    
    return _fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView)
{

    _fieldOfView = fieldOfView;
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;
}

float Camera::getZoomX() const
{

    return _zoom[0];
}

void Camera::setZoomX(float zoomX)
{

    _zoom[0] = zoomX;
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;
}

float Camera::getZoomY() const
{

    return _zoom[1];
}

void Camera::setZoomY(float zoomY)
{

    _zoom[1] = zoomY;
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;
}

float Camera::getAspectRatio() const
{
    return _aspectRatio;
}

void Camera::setAspectRatio(float aspectRatio)
{
    _aspectRatio = aspectRatio;
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;
}

float Camera::getNearPlane() const
{
    return _nearPlane;
}

void Camera::setNearPlane(float nearPlane)
{
    _nearPlane = nearPlane;
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;
}

float Camera::getFarPlane() const
{
    return _farPlane;
}

void Camera::setFarPlane(float farPlane)
{
    _farPlane = farPlane;
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;
}

const Mat4& Camera::getViewMatrix()
{
    if (!(_bits & CAMERA_CUSTOM_VIEW) && _bits & CAMERA_DIRTY_VIEW)
    {
         Mat4::createLookAt(transform().getTranslation(), transform().getTranslation()+direction, _up, &_view);
        _bits &= ~CAMERA_DIRTY_VIEW;
    }

    return _view;
}

const Mat4& Camera::getInverseViewMatrix()
{
    if (_bits & CAMERA_DIRTY_INV_VIEW)
    {
        
         getViewMatrix().inverse(&_inverseView);
        _bits &= ~CAMERA_DIRTY_INV_VIEW;
        
    }

    return _inverseView;
}

const Mat4& Camera::getProjectionMatrix()
{
    if (!(_bits & CAMERA_CUSTOM_PROJECTION) && (_bits & CAMERA_DIRTY_PROJ))
    {
        if (_type == PERSPECTIVE){
            
            Mat4::createPerspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane, &_projection);

        }else{
            
            // Create an ortho projection with the origin at the bottom left of the viewport, +X to the right and +Y up.
            if(!_middle){
        
                Mat4::createOrthographicOffCenter(0.0f, _zoom[0], 0.0f , _zoom[1], _nearPlane, _farPlane, &_projection);
                
            }else{
               
                Mat4::createOrthographic(_zoom[0], _zoom[1], _nearPlane, _farPlane, &_projection);
           }

        }

        _bits &= ~CAMERA_DIRTY_PROJ;
    }

    return _projection;
}

void Camera::setProjectionMatrix(const Mat4& matrix)
{
    _projection = matrix;
    _bits |= CAMERA_CUSTOM_PROJECTION;
    _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

}
    
void Camera::setViewMatrix(const Mat4& view){
    
    _view = view;
    _bits |= CAMERA_CUSTOM_VIEW;
    _bits |= CAMERA_DIRTY_VIEW | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

}

void Camera::resetProjectionMatrix()
{
    if (_bits & CAMERA_CUSTOM_PROJECTION)
    {
        _bits &= ~CAMERA_CUSTOM_PROJECTION;
        _bits |= CAMERA_DIRTY_PROJ | CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;

    }
}

const Mat4& Camera::getViewProjectionMatrix()
{
    if (_bits & CAMERA_DIRTY_VIEW_PROJ)
    {
        _viewProjection=getProjectionMatrix()*getViewMatrix();
        _bits &= ~CAMERA_DIRTY_VIEW_PROJ;
    }

    return _viewProjection;
}

const Mat4& Camera::getInverseViewProjectionMatrix()
{
    if (_bits & CAMERA_DIRTY_INV_VIEW_PROJ)
    {
        
        getViewProjectionMatrix().inverse(&_inverseViewProjection);
        _bits &= ~CAMERA_DIRTY_INV_VIEW_PROJ;
    }

    return _inverseViewProjection;
}
    
const  Mat4& Camera::getInverseProjectionMatrix(){
    
    getProjectionMatrix().inverse(&_inverseProjection);

    return _inverseProjection;

}

const Frustum& Camera::getFrustum()
{
    if (_bits & CAMERA_DIRTY_BOUNDS)
    {
        // Update our bounding frustum from our view projection matrix.
        _bounds.set(getViewProjectionMatrix());

        _bits &= ~CAMERA_DIRTY_BOUNDS;
    }

    return _bounds;
}

void Camera::project(const Rectangle& viewport, const Vec3& position, float* x, float* y, float* depth)
{
   
//    // Transform the point to clip-space.
    Vec4 clipPos= getViewProjectionMatrix()*Vec4(position.x, position.y, position.z, 1.0f);
    
    // Compute normalized device coordinates.
   // GP_ASSERT(clipPos.w != 0.0f);
    float ndcX = clipPos.x / clipPos.w;
    float ndcY = clipPos.y / clipPos.w;

    // Compute screen coordinates by applying our viewport transformation.
    *x = viewport.x + (ndcX + 1.0f) * 0.5f * viewport.width;
    *y = viewport.y + (1.0f - (ndcY + 1.0f) * 0.5f) * viewport.height;
    if (depth)
    {
        float ndcZ = clipPos.z ;
        *depth = ndcZ;
    }
}

void Camera::project(const Rectangle& viewport, const Vec3& position, Vec2* out)
{
    float x, y;
    project(viewport, position, &x, &y);
    out->set(x, y);
}

void Camera::project(const Rectangle& viewport, const Vec3& position, Vec3* out)
{
    float x, y, depth;
    project(viewport, position, &x, &y, &depth);
    out->set(x, y, depth);
}

void Camera::unproject(const Rectangle& viewport, float x, float y, float depth, Vec3* dst)
{
    
    // Create our screen space position in NDC.
   // GP_ASSERT(viewport.width != 0.0f && viewport.height != 0.0f);
    Vec4 screen((x - viewport.x) / viewport.width, ((viewport.height - y) - viewport.y) / viewport.height, depth, 1.0f);

    // Map to range -1 to 1.
    screen.x = screen.x * 2.0f - 1.0f;
    screen.y = screen.y * 2.0f - 1.0f;
    screen.z = screen.z * 2.0f - 1.0f;

    // Transform the screen-space NDC by our inverse view projection matrix.
    screen= getInverseViewProjectionMatrix()*screen;
    
    // Divide by our W coordinate.
    if (screen.w != 0.0f)
    {
        screen.x /= screen.w;
        screen.y /= screen.w;
        screen.z /= screen.w;
    }

    dst->set(screen.x, screen.y, screen.z);
}
    
void Camera::setUp(const Vec3& up){

    _up=up;
    _bits |=CAMERA_DIRTY_VIEW|   CAMERA_DIRTY_VIEW_PROJ | CAMERA_DIRTY_INV_VIEW_PROJ | CAMERA_DIRTY_BOUNDS | CAMERA_DIRTY_INV_VIEW;
   
}
    
Vec3 Camera::getUp(){
    
    return _up;

}

void Camera::pickRay(const Rectangle& viewport, float x, float y, Ray* dst) 
{
   // GP_ASSERT(dst);

    // Get the world-space position at the near clip plane.
    Vec3 nearPoint;
    unproject(viewport, x, y, 0.0f, &nearPoint);

    // Get the world-space position at the far clip plane.
    Vec3 farPoint;
    unproject(viewport, x, y, 1.0f, &farPoint);

    // Set the direction of the ray.
    Vec3 direction=farPoint-nearPoint;
    direction.normalize();

    dst->set(nearPoint, direction);
}

}
