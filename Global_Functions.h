/* 
 * File:   Global_Func.h
 * Author: neckbird
 *
 * Created on 03 October 2013, 17:47
 */

#ifndef GLOBAL_FUNC_H
#define	GLOBAL_FUNC_H

#include "SDL/SDL.h"
#include <string>
using std::string;

SDL_Surface *load_image(string);
void apply_surface(int, int, SDL_Surface *, SDL_Surface *, SDL_Rect* = NULL);
bool load_files();
bool init();
void clean_up();
void set_clips();
void reset_squares();

#endif	/* GLOBAL_FUNC_H */

