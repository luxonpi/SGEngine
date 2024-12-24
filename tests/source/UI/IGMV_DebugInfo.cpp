#include "IGMV_DebugInfo.h"

using namespace sge;

IGMV_DebugInfo::IGMV_DebugInfo(){}
IGMV_DebugInfo::~IGMV_DebugInfo(){}

void IGMV_DebugInfo::initIGMV_DebugInfo(){
    
    _timeLabel= Label::create("21:32", "assets/fonts/Gidole.otf", 12);
    _timeLabel->setColor(Color("ff0000"));
    _timeLabel->setPosition(0,0);
    _timeLabel->setZOrder(9);
    _background->addSubview(_timeLabel);
    
}

IGMV_DebugInfo* IGMV_DebugInfo::create(float width, float height){
    
    IGMV_DebugInfo* bpv= new IGMV_DebugInfo();
    
    bpv->initWithSizeColorTexture(width, height, Color(230, 230, 230, 1.0), NULL);
    bpv->initInGameModuleView();
    bpv->initIGMV_DebugInfo();
    
    return bpv;
    
}

void IGMV_DebugInfo::setSize(const sge::Vec2& size){
    
    InGameModuleView::setSize(size);
    
    _timeLabel->setPosition(10,size.y-5);
  
    
}

void IGMV_DebugInfo::clear(){

    _stringStream.str(std::string());
    _stringStream.clear();


}

void IGMV_DebugInfo::addInfoFloat(const std::string& name, float value){

    _stringStream<<name<<": " << value<< "\n";
    _timeLabel->setText(_stringStream.str());

}

void IGMV_DebugInfo::addInfoInt(const std::string& name, int value){

    _stringStream<<name<<": " << value<< "\n";
    _timeLabel->setText(_stringStream.str());


}

void IGMV_DebugInfo::addInfoVec3(const std::string& name, const sge::Vec3& value){

    _stringStream<<name<<": (" <<(int) value.x <<", " <<(int)value.y<< ", "<< (int)value.z << ")\n";
    _timeLabel->setText(_stringStream.str());

}
