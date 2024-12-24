#include "Action.h"

namespace sge {

    Action::Action(){

        _startTime=0;
        _endTime=0;
        _time=0;
        _duration=0;
        _repeats=0;
        _isRunning=false;
        
    }

    Action::~Action(){

    }

}