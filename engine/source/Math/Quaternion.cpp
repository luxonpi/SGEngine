

#include "Quaternion.h"

namespace sge{

Quaternion::Quaternion(): x(0.0f), y(0.0f), z(0.0f), w(1.0f){}
Quaternion::Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w){}
Quaternion::Quaternion(float* array){ set(array); }
Quaternion::Quaternion(const Mat4& m){ set(m); }
Quaternion::Quaternion(const Vec3& axis, float angle){ set(axis, angle); }
Quaternion::Quaternion(const Quaternion& copy){ set(copy); }
Quaternion::Quaternion(const Vec3& axis){ set(axis); }
Quaternion::~Quaternion(){}
    
void Quaternion::set(const Vec3& eulerRotation){
    
    set(Vec3(1, 0, 0), eulerRotation.x);
    
    *this*=Quaternion(Vec3(0, 1, 0), eulerRotation.y);
    *this*=Quaternion(Vec3(0, 0, 1), eulerRotation.z);


}

const Quaternion& Quaternion::identity()
{
    static Quaternion value(0.0f, 0.0f, 0.0f, 1.0f);
    return value;
}

const Quaternion& Quaternion::zero()
{
    static Quaternion value(0.0f, 0.0f, 0.0f, 0.0f);
    return value;
}

bool Quaternion::isIdentity() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
}

bool Quaternion::isZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

void Quaternion::createFromRotationMatrix(const Mat4& m, Quaternion* dst)
{
    //m.getRotation(dst);
}

void Quaternion::createFromAxisAngle(const Vec3& axis, float angle, Quaternion* dst)
{

    float halfAngle = (angle/180*M_PI) * 0.5f;
    float sinHalfAngle = sinf(halfAngle);

    Vec3 normal(axis);
    normal.normalize();
    dst->x = normal.x * sinHalfAngle;
    dst->y = normal.y * sinHalfAngle;
    dst->z = normal.z * sinHalfAngle;
    dst->w = cosf(halfAngle);
}

void Quaternion::conjugate()
{
    conjugate(this);
}

void Quaternion::conjugate(Quaternion* dst) const
{

    dst->x = -x;
    dst->y = -y;
    dst->z = -z;
    dst->w =  w;
}

bool Quaternion::inverse()
{
    return inverse(this);
}

bool Quaternion::inverse(Quaternion* dst) const{
    

    float n = x * x + y * y + z * z + w * w;
    if (n == 1.0f)
    {
        dst->x = -x;
        dst->y = -y;
        dst->z = -z;
        dst->w = w;

        return true;
    }

    // Too close to zero.
    if (n < 0.000001f)
        return false;

    n = 1.0f / n;
    dst->x = -x * n;
    dst->y = -y * n;
    dst->z = -z * n;
    dst->w = w * n;

    return true;
}

void Quaternion::multiply(const Quaternion& q)
{
    multiply(*this, q, this);
}

void Quaternion::multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst)
{

    float x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    float y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    float z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    float w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
    dst->w = w;
}

void Quaternion::normalize()
{
    normalize(this);
}

void Quaternion::normalize(Quaternion* dst) const
{

    if (this != dst)
    {
        dst->x = x;
        dst->y = y;
        dst->z = z;
        dst->w = w;
    }

    float n = x * x + y * y + z * z + w * w;

    // Already normalized.
    if (n == 1.0f)
        return;

    n = sqrt(n);
    // Too close to zero.
    if (n < 0.000001f)
        return;

    n = 1.0f / n;
    dst->x *= n;
    dst->y *= n;
    dst->z *= n;
    dst->w *= n;
}

void Quaternion::set(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Quaternion::set(float* array)
{

    x = array[0];
    y = array[1];
    z = array[2];
    w = array[3];
}
    
void Quaternion::lookRotation(const Vec3& dir){
   
    // Based on Stan Melax's article in Game Programming Gems

    // Copy, since cannot modify local
    Vec3 v0 = Vec3(0, 1, 0);
    Vec3 v1 = dir;
    Vec3 fallbackAxis = Vec3();

    float d = v0.dot(v1);
    // If dot == 1, vectors are the same
    if (d >= 1.0f){
        (*this) = Quaternion::identity();
    }
    
    if (d < (1e-6f - 1.0f)){
        
        if (fallbackAxis != Vec3(0,0,0)){
            
            // rotate 180 degrees about the fallback axis
            set(fallbackAxis, 180);
        
        }else{
            
            // Generate an axis
            Vec3 axis = Vec3(1,0,0);
    
            axis.normalize();
            set(axis, 180);
        }
    }
    else
    {
        float s = sqrtf( (1+d)*2 );
        float invs = 1 / s;
        
        Vec3 c = v0.cross(v1);
        
        this->x = c.x * invs;
        this->y = c.y * invs;
        this->z = c.z * invs;
        this->w = s * 0.5f;
        normalize();
        
    }
    
}

void Quaternion::set(const Mat4& m)
{
    Quaternion::createFromRotationMatrix(m, this);
}

void Quaternion::set(const Vec3& axis, float angle)
{
    Quaternion::createFromAxisAngle(axis, angle, this);
}

void Quaternion::set(const Quaternion& q)
{
    this->x = q.x;
    this->y = q.y;
    this->z = q.z;
    this->w = q.w;
}

void Quaternion::setIdentity()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

Vec3 Quaternion::getEulerRotation(){
  
    Quaternion q(x, y, z, w);
    q.normalize();
    
    double sqw= q.w * q.w;
    double sqx= q.x * q.x;
    double sqy= q.y * q.y;
    double sqz= q.z * q.z;
    
    double rotxrad;
    double rotyrad;
    double rotzrad;
    
    rotxrad = (double)atan2l(2.0 * ( q.y * q.z + q.x * q.w ) , ( -sqx - sqy + sqz + sqw ));
    rotyrad = (double)asinl(-2.0 * ( q.x * q.z - q.y * q.w ));
    rotzrad = (double)atan2l(2.0 * ( q.x * q.y + q.z * q.w ) , (  sqx - sqy - sqz + sqw ));
    
    return Vec3(rotxrad*(180/M_PI), -rotyrad*(180/M_PI), rotzrad*(180/M_PI));

}
    
float Quaternion::toAxisAngle(Vec3* axis) const
{
    
//    if (axis)
//    {
//        axis->x = q.x;
//        axis->y = q.y;
//        axis->z = q.z;
//        axis->normalize();
//    }
//    return (2.0f * acos(q.w));
    
    return 0;
}

void Quaternion::lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst)
{
//    GP_ASSERT(dst);
//    GP_ASSERT(!(t < 0.0f || t > 1.0f));

    if (t == 0.0f)
    {
        memcpy(dst, &q1, sizeof(float) * 4);
        return;
    }
    else if (t == 1.0f)
    {
        memcpy(dst, &q2, sizeof(float) * 4);
        return;
    }

    float t1 = 1.0f - t;

    dst->x = t1 * q1.x + t * q2.x;
    dst->y = t1 * q1.y + t * q2.y;
    dst->z = t1 * q1.z + t * q2.z;
    dst->w = t1 * q1.w + t * q2.w;
}

void Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst)
{
//    GP_ASSERT(dst);
    slerp(q1.x, q1.y, q1.z, q1.w, q2.x, q2.y, q2.z, q2.w, t, &dst->x, &dst->y, &dst->z, &dst->w);
}

void Quaternion::squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst)
{
//    GP_ASSERT(!(t < 0.0f || t > 1.0f));

    Quaternion dstQ(0.0f, 0.0f, 0.0f, 1.0f);
    Quaternion dstS(0.0f, 0.0f, 0.0f, 1.0f);

    slerpForSquad(q1, q2, t, &dstQ);
    slerpForSquad(s1, s2, t, &dstS);
    slerpForSquad(dstQ, dstS, 2.0f * t * (1.0f - t), dst);
}

void Quaternion::slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw)
{
    // Fast slerp implementation by kwhatmough:
    // It contains no division operations, no trig, no inverse trig
    // and no sqrt. Not only does this code tolerate small constraint
    // errors in the input quaternions, it actually corrects for them.
//    GP_ASSERT(dstx && dsty && dstz && dstw);
//    GP_ASSERT(!(t < 0.0f || t > 1.0f));

    if (t == 0.0f)
    {
        *dstx = q1x;
        *dsty = q1y;
        *dstz = q1z;
        *dstw = q1w;
        return;
    }
    else if (t == 1.0f)
    {
        *dstx = q2x;
        *dsty = q2y;
        *dstz = q2z;
        *dstw = q2w;
        return;
    }

    if (q1x == q2x && q1y == q2y && q1z == q2z && q1w == q2w)
    {
        *dstx = q1x;
        *dsty = q1y;
        *dstz = q1z;
        *dstw = q1w;
        return;
    }

    float halfY, alpha, beta;
    float u, f1, f2a, f2b;
    float ratio1, ratio2;
    float halfSecHalfTheta, versHalfTheta;
    float sqNotU, sqU;

    float cosTheta = q1w * q2w + q1x * q2x + q1y * q2y + q1z * q2z;

    // As usual in all slerp implementations, we fold theta.
    alpha = cosTheta >= 0 ? 1.0f : -1.0f;
    halfY = 1.0f + alpha * cosTheta;

    // Here we bisect the interval, so we need to fold t as well.
    f2b = t - 0.5f;
    u = f2b >= 0 ? f2b : -f2b;
    f2a = u - f2b;
    f2b += u;
    u += u;
    f1 = 1.0f - u;

    // One iteration of Newton to get 1-cos(theta / 2) to good accuracy.
    halfSecHalfTheta = 1.09f - (0.476537f - 0.0903321f * halfY) * halfY;
    halfSecHalfTheta *= 1.5f - halfY * halfSecHalfTheta * halfSecHalfTheta;
    versHalfTheta = 1.0f - halfY * halfSecHalfTheta;

    // Evaluate series expansions of the coefficients.
    sqNotU = f1 * f1;
    ratio2 = 0.0000440917108f * versHalfTheta;
    ratio1 = -0.00158730159f + (sqNotU - 16.0f) * ratio2;
    ratio1 = 0.0333333333f + ratio1 * (sqNotU - 9.0f) * versHalfTheta;
    ratio1 = -0.333333333f + ratio1 * (sqNotU - 4.0f) * versHalfTheta;
    ratio1 = 1.0f + ratio1 * (sqNotU - 1.0f) * versHalfTheta;

    sqU = u * u;
    ratio2 = -0.00158730159f + (sqU - 16.0f) * ratio2;
    ratio2 = 0.0333333333f + ratio2 * (sqU - 9.0f) * versHalfTheta;
    ratio2 = -0.333333333f + ratio2 * (sqU - 4.0f) * versHalfTheta;
    ratio2 = 1.0f + ratio2 * (sqU - 1.0f) * versHalfTheta;

    // Perform the bisection and resolve the folding done earlier.
    f1 *= ratio1 * halfSecHalfTheta;
    f2a *= ratio2;
    f2b *= ratio2;
    alpha *= f1 + f2a;
    beta = f1 + f2b;

    // Apply final coefficients to a and b as usual.
    float w = alpha * q1w + beta * q2w;
    float x = alpha * q1x + beta * q2x;
    float y = alpha * q1y + beta * q2y;
    float z = alpha * q1z + beta * q2z;

    // This final adjustment to the quaternion's length corrects for
    // any small constraint error in the inputs q1 and q2 But as you
    // can see, it comes at the cost of 9 additional multiplication
    // operations. If this error-correcting feature is not required,
    // the following code may be removed.
    f1 = 1.5f - 0.5f * (w * w + x * x + y * y + z * z);
    *dstw = w * f1;
    *dstx = x * f1;
    *dsty = y * f1;
    *dstz = z * f1;
}

void Quaternion::slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst)
{
//    GP_ASSERT(dst);

    // cos(omega) = q1 * q2;
    // slerp(q1, q2, t) = (q1*sin((1-t)*omega) + q2*sin(t*omega))/sin(omega);
    // q1 = +- q2, slerp(q1,q2,t) = q1.
    // This is a straight-forward implementation of the formula of slerp. It does not do any sign switching.
    float c = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

    if (fabs(c) >= 1.0f)
    {
        dst->x = q1.x;
        dst->y = q1.y;
        dst->z = q1.z;
        dst->w = q1.w;
        return;
    }

    float omega = acos(c);
    float s = sqrt(1.0f - c * c);
    if (fabs(s) <= 0.00001f)
    {
        dst->x = q1.x;
        dst->y = q1.y;
        dst->z = q1.z;
        dst->w = q1.w;
        return;
    }

    float r1 = sin((1 - t) * omega) / s;
    float r2 = sin(t * omega) / s;
    dst->x = (q1.x * r1 + q2.x * r2);
    dst->y = (q1.y * r1 + q2.y * r2);
    dst->z = (q1.z * r1 + q2.z * r2);
    dst->w = (q1.w * r1 + q2.w * r2);
}

}
