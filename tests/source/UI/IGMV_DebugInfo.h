#ifndef EXOGROUNDS_IGMV_DEBUGINFO_H
#define EXOGROUNDS_IGMV_DEBUGINFO_H

#include <stdio.h>
#include "SGEngine.h"
#include "InGameModuleView.h"

class IGMV_DebugInfo: public InGameModuleView{
    
private:
    
    sge::Label* _timeLabel;
    
    std::stringstream _stringStream;
    
    IGMV_DebugInfo();
    ~IGMV_DebugInfo();
    
    void initIGMV_DebugInfo();
    
public:
    
    virtual void setSize(const sge::Vec2& size);
    
    static IGMV_DebugInfo* create(float width, float height);
    
    void clear();
    void addInfoFloat(const std::string& name, float value);
    void addInfoInt(const std::string& name, int value);
    void addInfoVec3(const std::string& name, const sge::Vec3& value);

};



#endif