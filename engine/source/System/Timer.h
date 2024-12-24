

#ifndef Timer_H
#define Timer_H

#include <stdio.h>
#include <chrono>
#include <vector>

namespace sge {
    
    class Timer{

        private:

        double _lastTime;
        double _time;
        bool _running;
    
        std::vector<float> _history;
        int _historyPos;
        
        std::chrono::time_point<std::chrono::system_clock> start, end;
    
        void updateTime();

        public:
    
        Timer();
        ~Timer();
    
        float getTimeInMs();
    
        void reset();
        void run();
        void pause();
	
    };
    
}

#endif
