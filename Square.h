/* 
 * File:   Square.h
 * Author: neckbird
 *
 * Created on 04 October 2013, 11:18
 */

#ifndef SQUARE_H
#define	SQUARE_H

#include "SDL/SDL.h"
#include "Globals.h"
#include "Global_Functions.h"
#include "Constants.h"

class Square {
public:
    Square(int, int);
    ~Square();
    void handle_event();
    void show();
    void set_state(int);
    int get_state();
private:
    SDL_Rect box;
    SDL_Rect* clip;
    int state;
};

#endif	/* SQUARE_H */

