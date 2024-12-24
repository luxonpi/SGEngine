

#ifndef SGENGINE_EXPOSURE_MEASURER_H
#define SGENGINE_ExposureMeasurer_H

#include <stdio.h>
#include "Sprite.h"
#include "FrameBuffer.h"
#include "SCamera.h"
#include "View.h"

namespace sge {
    
    class ExposureMeasurer{
        
    private:
        
    protected:
        
        Camera* _camera;
        View* _view;
        FrameBuffer* _buffer[2];
        FrameBuffer* _finalBuffer;
        
        Vec2 initSize;
        
        void initWithDimensions(float width, float height);
        
        ExposureMeasurer();
        ~ExposureMeasurer();
        
    public:
        
        static ExposureMeasurer* create(float width, float height);
        float getExposure(Texture* texture);
        
    };
    
}

#endif
