#include "InGameModuleView.h"

using namespace sge;

InGameModuleView::InGameModuleView(){

}

InGameModuleView::~InGameModuleView(){

}

void InGameModuleView::initInGameModuleView(){
    
    _background= View::create(41, 41, "assets/ui/ui_module_bg.png");
    _background->setTintColor(Color(255, 255, 255, 0.2));
    this->addSubview(_background);

}

InGameModuleView* InGameModuleView::create(float width, float height){

    InGameModuleView* bpv= new InGameModuleView();
    
    bpv->initWithSizeColorTexture(width, height, Color(255, 255, 255, 1.0), NULL);
    bpv->initInGameModuleView();
    
    return bpv;

}

void InGameModuleView::setSize(const Vec2& size){

    View::setSize(size);
    
    _background->setPosition(0, 0);
    _background->setSize(size);
    

}
