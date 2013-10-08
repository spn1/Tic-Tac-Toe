/* 
 * File:   Square.cpp
 * Author: neckbird
 * 
 * Created on 04 October 2013, 11:18
 */

#include "Square.h"

Square::Square(int x, int y) {
    state = EMPTY;
 
    box.x = x;
    box.y = y;
    box.w = 80;
    box.h = 80;
    
    clip = &squareClips[EMPTY];
}

Square::~Square() {
    
}

void Square::set_state(int state) {
    this->state = state;
}

int Square::get_state() {
    return state;
}

void Square::handle_event() {
    int x = 0, y = 0;
    
    //If Event is of type Mouse Motion
    if (event.type == SDL_MOUSEMOTION) {
        //Get Mouse Offsets
        x = event.motion.x;
        y = event.motion.y;
        
        //If the mouse is over the button
        if ((x > box.x) && (x < box.x + box.w) && 
                (y > box.y) && (y < box.y + box.h) && (state < CROSS)) {
            state = HIGHLIGHTED;
            clip = &squareClips[HIGHLIGHTED];
        } else if (state != CROSS && state != NOUGHT) {
            state = EMPTY;
            clip = &squareClips[EMPTY];
        }
    }
    
    //If Event is of type Mouse Button Down
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        x = event.motion.x;
        y = event.motion.y;
        
        //If the button pressed is the Left Mouse Button
        if (event.button.button == SDL_BUTTON_LEFT) {
            if ((x > box.x) && (x < box.x + box.w) && 
                (y > box.y) && (y < box.y + box.h)) {
                if (turn == PLAYER_1 && state != NOUGHT) {
                    //Set state and clip for image
                    state = CROSS;
                    clip = &squareClips[CROSS];
                    
                    //Change Player Turn
                    turn = PLAYER_2;
                } else if (turn == PLAYER_2 && state != CROSS) {
                    //Set state and clip for image
                    state = NOUGHT;
                    clip = &squareClips[NOUGHT];
                    
                    //Change Player Turn
                    turn = PLAYER_1;
                }
            }
        }
    }
}

void Square::show() {
    apply_surface(box.x, box.y, squareSheet, screen, clip);
}

