#ifndef EXOGROUNDS_INGAMEMODULEVIEW_H
#define EXOGROUNDS_INGAMEMODULEVIEW_H

#include <stdio.h>
#include "SGEngine.h"

class InGameModuleView: public sge::View{

protected:
    
    sge::View* _background;

    InGameModuleView();
    ~InGameModuleView();
    
    void initInGameModuleView();
    
public:
    
    virtual void setSize(const sge::Vec2& size);
    
    static InGameModuleView* create(float width, float height);

};

#endif