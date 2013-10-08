/* 
 * File:   Button.h
 * Author: neckbird
 *
 * Created on 03 October 2013, 18:01
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "SDL/SDL.h"
#include "Globals.h"
#include "Global_Functions.h"
#include "Constants.h"

class Button {
public:
    Button(int, int, int, int);
    ~Button();
    void handle_event();
    void show();
    void set_text(string);
    string get_text();
private:
    string text;
    SDL_Rect box;
    SDL_Rect* clip;
    SDL_Surface *textSurface;
};

#endif	/* BUTTON_H */

