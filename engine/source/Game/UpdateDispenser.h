

#ifndef SGENGINE_UPDATEDISPENSER_H
#define SGENGINE_UPDATEDISPENSER_H

#include <stdio.h>
#include <functional>
#include <vector>

namespace sge {
    
class UpdateReceiver{

private:
    std::function< void(float) > _callback;
    float _interval;
    float _pastTime;
    int _priority;
    bool _enabled;
    
public:
    
    UpdateReceiver(std::function< void(float) > callback, float interval, int priority);
    void update(float delta);
    void setEnabled(const bool& enabled);
    bool isEnabled();

};


class UpdateDispenser{


private:
    std::vector<UpdateReceiver*> _receiver;
    
public:
    
    void addReceiver(UpdateReceiver* receiver);
    void removeReceiver(UpdateReceiver* receiver);
    
    void update(float delta);


};

}
#endif
