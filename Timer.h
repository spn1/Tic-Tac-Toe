/* 
 * File:   Timer.h
 * Author: neckbird
 *
 * Created on 21 September 2013, 18:51
 */

#ifndef TIMER_H
#define	TIMER_H

#include "SDL/SDL.h"

class Timer {
public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    
    int get_ticks();
    bool is_started();
    bool is_paused();
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
};

#endif	/* TIMER_H */

