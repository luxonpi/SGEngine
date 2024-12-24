

#include "Timer.h"

namespace sge {

Timer::Timer(){

    _lastTime=0;
    _time=0;
    _running=false;
    _history.resize(30);
    _historyPos=0;

}
    
Timer::~Timer(){}

float Timer::getTimeInMs(){
    
    float time=0;
    
    for (int i=0; i<_history.size(); i++) {
        
        time+=_history[i];
        
    }

    return int(time/_history.size()*100)/100.;

}

void Timer::reset(){

    _history[_historyPos]=_time;
    _historyPos++;
    if(_historyPos>=_history.size()) _historyPos=0;
    
    updateTime();
    
    _time=0;
    start = std::chrono::system_clock::now();

}

void Timer::updateTime(){

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    _time+= elapsed_seconds.count()*1000.0;

    start = std::chrono::system_clock::now();

}

void Timer::run(){

    _running=true;
    start = std::chrono::system_clock::now();

}

void Timer::pause(){

    _running=false;
    updateTime();
    
  
    
}
    
}
