

#ifndef SGENGINE_KEYEVENT_H
#define SGENGINE_KEYEVENT_H

#include <iostream>

class KeyEvent{

public:

    KeyEvent();
    KeyEvent(int c);
    KeyEvent(KeyEvent* copy);
    

    unsigned char KeyCode;
    bool passToLowerPriorities;
    
    static unsigned char SPACE;
    static unsigned char ENTER;
    static unsigned char SHIFT;
    static unsigned char PERIOD;
    static unsigned char COMMA;
    static unsigned char STRL;
    static unsigned char BACK;
    static unsigned char ESCAPE;

    static unsigned char UP;
    static unsigned char RIGHT;
    static unsigned char LEFT;
    static unsigned char DOWN;
    
    static unsigned char A;
    static unsigned char B;
    static unsigned char C;
    static unsigned char D;
    static unsigned char E;
    static unsigned char F;
    static unsigned char G;
    static unsigned char H;
    static unsigned char I;
    static unsigned char J;
    static unsigned char K;
    static unsigned char L;
    static unsigned char M;
    static unsigned char N;
    static unsigned char O;
    static unsigned char P;
    static unsigned char Q;
    static unsigned char R;
    static unsigned char S;
    static unsigned char T;
    static unsigned char U;
    static unsigned char V;
    static unsigned char W;
    static unsigned char X;
    static unsigned char Y;
    static unsigned char Z;
    
    static unsigned char NUM0;
    static unsigned char NUM1;
    static unsigned char NUM2;
    static unsigned char NUM3;
    static unsigned char NUM4;
    static unsigned char NUM5;
    static unsigned char NUM6;
    static unsigned char NUM7;
    static unsigned char NUM8;
    static unsigned char NUM9;

};

#endif
