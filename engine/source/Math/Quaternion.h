

// derived from the gameplay engine
// https://github.com/gameplay3d/GamePlay

#ifndef SGENGINE_QUATERNION_H
#define SGENGINE_QUATERNION_H

#include "Vec3.h"
#include "SMath.h"
#include "Plane.h"
class Mat4;

namespace sge{

class Quaternion{
    
    friend class Curve;
    friend class Transform;

public:

    float x;
    float y;
    float z;
    float w;

    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(float* array);
    Quaternion(const Mat4& m);
    Quaternion(const Vec3& axis, float angle);
    Quaternion(const Quaternion& copy);
    Quaternion(const Vec3& axis);

    ~Quaternion();

    static const Quaternion& identity();
    static const Quaternion& zero();

    bool isIdentity() const;
    bool isZero() const;

    static void createFromRotationMatrix(const Mat4& m, Quaternion* dst);
    static void createFromAxisAngle(const Vec3& axis, float angle, Quaternion* dst);

    
    Vec3 getEulerRotation();
    
    /**
     * Sets this quaternion to the conjugate of itself.
     */
    void conjugate();

    /**
     * Gets the conjugate of this quaternion in dst.
     *
     * @param dst A quaternion to store the conjugate in.
     */
    void conjugate(Quaternion* dst) const;

    /**
     * Sets this quaternion to the inverse of itself.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     *
     * @return true if the inverse can be computed, false otherwise.
     */
    bool inverse();

    /**
     * Gets the inverse of this quaternion in dst.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     *
     * @param dst A quaternion to store the inverse in.
     * 
     * @return true if the inverse can be computed, false otherwise.
     */
    bool inverse(Quaternion* dst) const;

    /**
     * Multiplies this quaternion by the specified one and stores the result in this quaternion.
     *
     * @param q The quaternion to multiply.
     */
    void multiply(const Quaternion& q);

    /**
     * Multiplies the specified quaternions and stores the result in dst.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param dst A quaternion to store the result in.
     */
    static void multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst);

    /**
     * Normalizes this quaternion to have unit length.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method does nothing.
     */
    void normalize();

    /**
     * Normalizes this quaternion and stores the result in dst.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method simply copies
     * this vector into dst.
     *
     * @param dst A quaternion to store the result in.
     */
    void normalize(Quaternion* dst) const;

    /**
     * Sets the elements of the quaternion to the specified values.
     *
     * @param x The new x-value.
     * @param y The new y-value.
     * @param z The new z-value.
     * @param w The new w-value.
     */
    
    void set(const Vec3& eulerRotation);

    void set(float x, float y, float z, float w);

    /**
     * Sets the elements of the quaternion from the values in the specified array.
     *
     * @param array An array containing the elements of the quaternion in the order x, y, z, w.
     */
    void set(float* array);

    /**
     * Sets the quaternion equal to the rotational part of the specified matrix.
     *
     * @param m The matrix.
     */
    void set(const Mat4& m);

    /**
     * Sets the quaternion equal to the rotation from the specified axis and angle.
     * 
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    void set(const Vec3& axis, float angle);

    /**
     * Sets the elements of this quaternion to a copy of the specified quaternion.
     *
     * @param q The quaternion to copy.
     */
    void set(const Quaternion& q);
    void lookRotation(const Vec3& dir);

    /**
     * Sets this quaternion to be equal to the identity quaternion.
     */
    void setIdentity();

    /**
     * Converts this Quaternion4f to axis-angle notation. The axis is normalized.
     *
     * @param e The Vec3f which stores the axis.
     * 
     * @return The angle (in radians).
     */
    float toAxisAngle(Vec3* e) const;

  
    static void lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    static void slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    static void squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst);


    inline const Quaternion operator*(const Quaternion& q) const;
    inline Quaternion& operator*=(const Quaternion& q);

private:

    static void slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw);

    static void slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
};

}

#include "Quaternion.inl"

#endif
