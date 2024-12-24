

#include "Range.h"

Range::Range(){
    
    this->min=0;
    this->max=0;
}


Range::Range(float min, float max ){
    
    this->min=min;
    this->max=max;
    
}

void Range::set(float min, float max){

    this->min=min;
    this->max=max;
    
}

float Range::getRandom(){
    
    /*
     // Windows
     float nEnd=end*10000;
     float nStart=start*10000;
     if(nEnd==nStart) nStart-=1;
     
     int r = rand() * 10000 + rand() * 1000 + rand() * 100 + rand() * 10 + rand();
     float randomNum = (float)(r % (int)((nEnd - nStart))) + (nStart);
     return randomNum/10000;
     */
    
    float nEnd=max*10000;
    float nStart=min*10000;
    if(nEnd==nStart) nStart-=1;
    
    float randomNum = (float)(rand() % (int)((nEnd-nStart))) + (nStart);
    return randomNum/10000;
    
}

float Range::getLenght(){

    return fabs(max-min);

}
