/* 
 * File:   Button.cpp
 * Author: neckbird
 * 
 * Created on 03 October 2013, 18:01
 */

#include "Button.h"

Button::Button(int x, int y, int w, int h) {
    text = "New Button";
    
    textSurface = TTF_RenderText_Solid(buttonFont, text.c_str(), buttonColor);
    
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    
    clip = &clips[MOUSEOUT];
}

Button::~Button() {
    SDL_FreeSurface(textSurface);
}

void Button::set_text(string text) {
    this->text = text;
    textSurface = TTF_RenderText_Solid(buttonFont, text.c_str(), buttonColor);
}

string Button::get_text() {
    return text;
}

void Button::handle_event() {
    int x = 0, y = 0;
    
    //If Event is of type Mouse Motion
    if (event.type == SDL_MOUSEMOTION) {
        //Get Mouse Offsets
        x = event.motion.x;
        y = event.motion.y;
        
        //If the mouse is over the button
        if ((x > box.x) && (x < box.x + box.w) && (y > 0) && (y < box.y + box.h)) {
            clip = &clips[MOUSEOVER];
        } else {
            clip = &clips[MOUSEOUT];
        }
    }
    
    //If Event is of type Mouse Button Down
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        //If the button pressed is the Left Mouse Button
        if (event.button.button == SDL_BUTTON_LEFT) {
            //Get Mouse Offsets
            x = event.motion.x;
            y = event.motion.y;
        
            //If the mouse is over the button
            if ((x > box.x) && (x < box.x + box.w) && (y > 0) && (y < box.y + box.h)) {
                clip = &clips[MOUSEDOWN];
                
                reset_squares();
            }
                        
        }
    }
    
    //If Event is of type Mouse Button Up
    if (event.type == SDL_MOUSEBUTTONUP) {
        //If the button pressed is the Left Mouse Button
        if (event.button.button == SDL_BUTTON_LEFT) {
            //Get Mouse Offsets
            x = event.motion.x;
            y = event.motion.y;
        
            //If the mouse is over the button
            if ((x > box.x) && (x < box.x + box.w) && (y > 0) && (y < box.y + box.h)) {
                clip = &clips[MOUSEUP];
            }
        }
    }
}

void Button::show() {
    apply_surface(box.x, box.y, buttonSheet, screen, clip);
    apply_surface((box.x + (box.w / 2) - (textSurface->w / 2)), 
            (box.y + (box.h / 2) - (textSurface->h / 2)), textSurface, screen);
}



