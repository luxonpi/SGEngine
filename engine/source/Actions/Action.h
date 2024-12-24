

#ifndef Action_H
#define Action_H

#include <stdio.h>
#include "Entity.h"

namespace sge {
    
class Action{

protected:

public:
    
    float _startTime;
    float _endTime;
    float _time;
    float _duration;
    int _repeats;
    bool _isRunning;
        
    virtual void updateEntity(Entity* entity)=0;
    virtual void start(Entity* entity)=0;
    virtual void end(Entity* entity)=0;

	Action();
	virtual ~Action();
	
};
    
}

#endif
