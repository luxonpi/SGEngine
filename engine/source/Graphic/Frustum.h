

#ifndef SGENGINE_FRUSTUM_H
#define SGENGINE_FRUSTUM_H

#include "SMath.h"
#include "Ray.h"
#include "Plane.h"

namespace sge{

    class Frustum{
    
    private:
    
        void updatePlanes();
    
        Plane _near;
        Plane _far;
        Plane _bottom;
        Plane _top;
        Plane _left;
        Plane _right;
        Mat4 _matrix;
    
    public:

        // Gameplay code
        Frustum();
        Frustum(const Mat4& matrix);
        Frustum(const Frustum& frustum);
        ~Frustum();

        const Plane& getNear() const;
        const Plane& getFar() const;
        const Plane& getLeft() const;
        const Plane& getRight() const;
        const Plane& getBottom() const;
        const Plane& getTop() const;
    
        void getMatrix(Mat4* dst) const;

        /**
        * Gets the corners of the frustum in the specified array.
        *
        * The corners are stored in the following order:
        * (N-near, F-far, L-left, R-right, B-bottom, T-top)
        * LTN, LBN, RBN, RTN, RTF, RBF, LBF, LTF.
        *
        * @param corners The array (of at least size 8) to store the corners in.
        */
        void getCorners(Vec3* corners) const;
        void getSubCorners(Vec3* corners, float nearFactor, float farFactor) const;

        /**
         * Gets the corners of the frustum's near plane in the specified array.
         *
         * The corners are stored in the following order:
         * left-top, left-bottom, right-bottom, right-top.
         *
         * @param corners The array (of at least size 4) to store the corners in.
         */
        void getNearCorners(Vec3* corners) const;

        /**
         * Gets the corners of the frustum's far plane in the specified array.
         *
         * The corners are stored in the following order:
         * right-top, right-bottom, left-bottom, left-top.
         *
         * @param corners The array (of at least size 4) to store the corners in.
         */
        void getFarCorners(Vec3* corners) const;

        bool intersects(const Vec3& point) const;
        bool intersects(float x, float y, float z) const;
        bool intersects(const BoundingSphere& sphere) const;
        int intersects(const BoundingBox& box) const;
        float intersects(const Plane& plane) const;
        float intersects(const Ray& ray) const;
    
        void set(const Frustum& frustum);
        void set(const Mat4& matrix);

    };

}

#endif
