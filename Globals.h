/* 
 * File:   Globals.h
 * Author: neckbird
 *
 * Created on 03 October 2013, 17:47
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

//Externs
extern SDL_Surface *screen;
extern SDL_Surface *background;
extern SDL_Surface *buttonSheet;
extern SDL_Surface *squareSheet;
extern SDL_Surface *title;
extern SDL_Event event;

extern TTF_Font *titleFont;
extern TTF_Font *buttonFont;
extern SDL_Color titleColor;
extern SDL_Color buttonColor;

extern SDL_Rect clips[4];
extern SDL_Rect squareClips[4];

extern int turn;

#endif	/* GLOBALS_H */

