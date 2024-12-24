

#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Plane.h"

namespace sge
{
    
    
    static void updateMinMax(Vec3* point, Vec3* min, Vec3* max)
    {
        
        // Leftmost point.
        if (point->x < min->x)
        {
            min->x = point->x;
        }
        
        // Rightmost point.
        if (point->x > max->x)
        {
            max->x = point->x;
        }
        
        // Lowest point.
        if (point->y < min->y)
        {
            min->y = point->y;
        }
        
        // Highest point.
        if (point->y > max->y)
        {
            max->y = point->y;
        }
        
        // Farthest point.
        if (point->z < min->z)
        {
            min->z = point->z;
        }
        
        // Nearest point.
        if (point->z > max->z)
        {
            max->z = point->z;
        }
    }


BoundingBox::BoundingBox(){

    // Maybe move to an sperate function?
    max.set(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
    min.set(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

}

BoundingBox::BoundingBox(const Vec3& min, const Vec3& max)
{
    set(min, max);
}

BoundingBox::BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    set(minX, minY, minZ, maxX, maxY, maxZ);
}

BoundingBox::BoundingBox(const BoundingBox& copy)
{
    set(copy);
}

    
bool BoundingBox::contains2DPoint(const Vec2& point){
    
    if(point.x<min.x) return false;
    if(point.x>max.x) return false;
    if(point.y<min.y) return false;
    if(point.y>max.y) return false;
    return true;

}
    
BoundingBox::~BoundingBox()
{
}

const BoundingBox& BoundingBox::empty()
{
    static BoundingBox b;
    return b;
}

void BoundingBox::getCorners(Vec3* dst) const{

    // Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
    // Left-top-front.
    dst[0].set(min.x, max.y, max.z);
    // Left-bottom-front.
    dst[1].set(min.x, min.y, max.z);
    // Right-bottom-front.
    dst[2].set(max.x, min.y, max.z);
    // Right-top-front.
    dst[3].set(max.x, max.y, max.z);

    // Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
    // Right-top-back.
    dst[4].set(max.x, max.y, min.z);
    // Right-bottom-back.
    dst[5].set(max.x, min.y, min.z);
    // Left-bottom-back.
    dst[6].set(min.x, min.y, min.z);
    // Left-top-back.
    dst[7].set(min.x, max.y, min.z);
}

Vec3 BoundingBox::getCenter() const
{
    Vec3 center;
    getCenter(&center);
    return center;
}

void BoundingBox::getCenter(Vec3* dst) const{

    *dst=(max-min)*0.5;
    *dst+=min;
    
}

bool BoundingBox::intersects(const BoundingSphere& sphere) const
{
    return sphere.intersects(*this);
}

bool BoundingBox::intersects(const BoundingBox& box) const
{
    return ((min.x >= box.min.x && min.x <= box.max.x) || (box.min.x >= min.x && box.min.x <= max.x)) &&
            ((min.y >= box.min.y && min.y <= box.max.y) || (box.min.y >= min.y && box.min.y <= max.y)) &&
            ((min.z >= box.min.z && min.z <= box.max.z) || (box.min.z >= min.z && box.min.z <= max.z));
}

int BoundingBox::intersects(const Frustum& frustum) const{
    
    // The box must either intersect or be in the positive half-space of all six planes of the frustum.
//    return (intersects(frustum.getNear()) != Plane::INTERSECTS_BACK &&
//            intersects(frustum.getFar()) != Plane::INTERSECTS_BACK &&
//            intersects(frustum.getLeft()) != Plane::INTERSECTS_BACK &&
//            intersects(frustum.getRight()) != Plane::INTERSECTS_BACK &&
//            intersects(frustum.getBottom()) != Plane::INTERSECTS_BACK &&
//            intersects(frustum.getTop()) != Plane::INTERSECTS_BACK);
    
   
    // Ist anscheinend schneller
    int bitMap= intersects(frustum.getNear()) | intersects(frustum.getFar()) | intersects(frustum.getLeft()) | intersects(frustum.getRight()) |  intersects(frustum.getBottom()) |  intersects(frustum.getTop());

    
    if (bitMap & Plane::INTERSECTS_BACK){
        
        return COMPLETELY_OUT;
        
    }

    if (bitMap & Plane::INTERSECTS_INTERSECTING){
        
        return INTERSECTING;
        
    }

    
    return COMPLETELY_IN;

}

int BoundingBox::intersects(const Plane& plane) const
{
    // Calculate the distance from the center of the box to the plane.
    Vec3 center((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, (min.z + max.z) * 0.5f);
    float distance = plane.distance(center);

    // Get the extents of the box from its center along each axis.
    float extentX = (max.x - min.x) * 0.5f;
    float extentY = (max.y - min.y) * 0.5f;
    float extentZ = (max.z - min.z) * 0.5f;

    const Vec3& planeNormal = plane.getNormal();
    if (fabsf(distance) <= (fabsf(extentX * planeNormal.x) + fabsf(extentY * planeNormal.y) + fabsf(
        extentZ * planeNormal.z)))
    {
        return Plane::INTERSECTS_INTERSECTING;
    }

    return (distance > 0.0f) ? Plane::INTERSECTS_FRONT : Plane::INTERSECTS_BACK;
}

float BoundingBox::intersects(const Ray& ray) const
{
    // Intermediate calculation variables.
    float dnear = 0.0f;
    float dfar = 0.0f;
    float tmin = 0.0f;
    float tmax = 0.0f;

    const Vec3& origin = ray.getOrigin();
    const Vec3& direction = ray.getDirection();

    // X direction.
    float div = 1.0f / direction.x;
    if (div >= 0.0f)
    {
        tmin = (min.x - origin.x) * div;
        tmax = (max.x - origin.x) * div;
    }
    else
    {
        tmin = (max.x - origin.x) * div;
        tmax = (min.x - origin.x) * div;
    }
    dnear = tmin;
    dfar = tmax;

    // Check if the ray misses the box.
    if (dnear > dfar || dfar < 0.0f)
    {
        return Ray::INTERSECTS_NONE;
    }

    // Y direction.
    div = 1.0f / direction.y;
    if (div >= 0.0f)
    {
        tmin = (min.y - origin.y) * div;
        tmax = (max.y - origin.y) * div;
    }
    else
    {
        tmin = (max.y - origin.y) * div;
        tmax = (min.y - origin.y) * div;
    }

    // Update the near and far intersection distances.
    if (tmin > dnear)
    {
        dnear = tmin;
    }
    if (tmax < dfar)
    {
        dfar = tmax;
    }
    // Check if the ray misses the box.
    if (dnear > dfar || dfar < 0.0f)
    {
        return Ray::INTERSECTS_NONE;
    }

    // Z direction.
    div = 1.0f / direction.z;
    if (div >= 0.0f)
    {
        tmin = (min.z - origin.z) * div;
        tmax = (max.z - origin.z) * div;
    }
    else
    {
        tmin = (max.z - origin.z) * div;
        tmax = (min.z - origin.z) * div;
    }

    // Update the near and far intersection distances.
    if (tmin > dnear)
    {
        dnear = tmin;
    }
    if (tmax < dfar)
    {
        dfar = tmax;
    }

    // Check if the ray misses the box.
    if (dnear > dfar || dfar < 0.0f)
    {
        return Ray::INTERSECTS_NONE;
    }
    // The ray intersects the box (and since the direction of a Ray is normalized, dnear is the distance to the ray).
    return dnear;
}

bool BoundingBox::isEmpty() const
{
    return min.x == max.x && min.y == max.y && min.z == max.z;
}

void BoundingBox::merge(const BoundingBox& box)
{
    // Calculate the new minimum point.
    min.x = std::min(min.x, box.min.x);
    min.y = std::min(min.y, box.min.y);
    min.z = std::min(min.z, box.min.z);

    // Calculate the new maximum point.
    max.x = std::max(max.x, box.max.x);
    max.y = std::max(max.y, box.max.y);
    max.z = std::max(max.z, box.max.z);
}
    
void BoundingBox::merge(const Vec3& point){
    
    if (point.y<min.y) {
       min.y=point.y;
    }
   
    if (point.y>max.y ) {
        max.y=point.y;
    }
    
    if (point.x<min.x) {
        min.x=point.x;
    }
    
    if (point.x>max.x) {
        max.x=point.x;
    }
    
    if (point.z<min.z) {
        min.z=point.z;
    }
    
    if (point.z>max.z) {
        max.z=point.z;
    }

}

void BoundingBox::merge(const BoundingSphere& sphere)
{
    const Vec3& center = sphere.center;
    float radius = sphere.radius;

    // Calculate the new minimum point for the merged bounding box.
    min.x = std::min(min.x, center.x - radius);
    min.y = std::min(min.y, center.y - radius);
    min.z = std::min(min.z, center.z - radius);

    // Calculate the new maximum point for the merged bounding box.
    max.x = std::max(max.x, center.x + radius);
    max.y = std::max(max.y, center.y + radius);
    max.z = std::max(max.z, center.z + radius);
}

void BoundingBox::set(const Vec3& min, const Vec3& max)
{
    this->min = min;
    this->max = max;
}

void BoundingBox::set(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
    min.set(minX, minY, minZ);
    max.set(maxX, maxY, maxZ);
}



void BoundingBox::set(const BoundingBox& box)
{
    min = box.min;
    max = box.max;
}

void BoundingBox::set(const BoundingSphere& sphere)
{
    const Vec3& center = sphere.center;
    float radius = sphere.radius;

    // Calculate the minimum point for the box.
    min.x = center.x - radius;
    min.y = center.y - radius;
    min.z = center.z - radius;

    // Calculate the maximum point for the box.
    max.x = center.x + radius;
    max.y = center.y + radius;
    max.z = center.z + radius;
}

void BoundingBox::transform(const Mat4& matrix)
{
    // Calculate the corners.
    Vec3 corners[8];
    getCorners(corners);

    // Transform the corners, recalculating the min and max points along the way.
    Vec4 v=matrix* Vec4(corners[0].x,corners[0].y,corners[0].z,1);
    corners[0]=Vec3(v.x, v.y, v.z);
    
    Vec3 newMin = corners[0];
    Vec3 newMax = corners[0];

    for (int i = 1; i < 8; i++)
    {
        
        Vec4 v=matrix* Vec4(corners[i].x,corners[i].y,corners[i].z,1);
        corners[i]=Vec3(v.x, v.y, v.z);
        updateMinMax(&corners[i], &newMin, &newMax);
    
    }
    
    this->min.x = newMin.x;
    this->min.y = newMin.y;
    this->min.z = newMin.z;
    this->max.x = newMax.x;
    this->max.y = newMax.y;
    this->max.z = newMax.z;
}

}
