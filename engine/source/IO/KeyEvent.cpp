

#include "KeyEvent.h"

KeyEvent::KeyEvent(){

    KeyCode=0;
    passToLowerPriorities=true;
}


KeyEvent::KeyEvent(int c){

    KeyCode=c;

}

KeyEvent::KeyEvent(KeyEvent* copy){

    KeyCode=copy->KeyCode;
    passToLowerPriorities=copy->passToLowerPriorities;

}


unsigned char KeyEvent::SPACE=32;
unsigned char KeyEvent::ENTER=13;
unsigned char KeyEvent::SHIFT=-1;
unsigned char KeyEvent::PERIOD=46;
unsigned char KeyEvent::COMMA=44;
unsigned char KeyEvent::STRL=-1;
unsigned char KeyEvent::BACK=127;
unsigned char KeyEvent::ESCAPE=27;

unsigned char KeyEvent::UP=0;
unsigned char KeyEvent::RIGHT=3;
unsigned char KeyEvent::LEFT=2;
unsigned char KeyEvent::DOWN=1;

unsigned char KeyEvent::A=97;
unsigned char KeyEvent::B=98;
unsigned char KeyEvent::C=99;
unsigned char KeyEvent::D=100;
unsigned char KeyEvent::E=101;
unsigned char KeyEvent::F=102;
unsigned char KeyEvent::G=103;
unsigned char KeyEvent::H=104;
unsigned char KeyEvent::I=105;
unsigned char KeyEvent::J=106;
unsigned char KeyEvent::K=107;
unsigned char KeyEvent::L=108;
unsigned char KeyEvent::M=109;
unsigned char KeyEvent::N=110;
unsigned char KeyEvent::O=111;
unsigned char KeyEvent::P=112;
unsigned char KeyEvent::Q=113;
unsigned char KeyEvent::R=114;
unsigned char KeyEvent::S=115;
unsigned char KeyEvent::T=116;
unsigned char KeyEvent::U=117;
unsigned char KeyEvent::V=118;
unsigned char KeyEvent::W=119;
unsigned char KeyEvent::X=120;
unsigned char KeyEvent::Y=121;
unsigned char KeyEvent::Z=122;

unsigned char KeyEvent::NUM0=48;
unsigned char KeyEvent::NUM1=49;
unsigned char KeyEvent::NUM2=50;
unsigned char KeyEvent::NUM3=51;
unsigned char KeyEvent::NUM4=52;
unsigned char KeyEvent::NUM5=53;
unsigned char KeyEvent::NUM6=54;
unsigned char KeyEvent::NUM7=55;
unsigned char KeyEvent::NUM8=56;
unsigned char KeyEvent::NUM9=57;
