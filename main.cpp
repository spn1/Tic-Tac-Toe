/* 
 * File:   main.cpp
 * Author: neckbird
 *
 * Created on 03 October 2013, 17:19
 */

#include <cstdlib>
#include <iostream>
using std::cout;
#include <sstream>
using std::ostringstream;
#include <vector>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "Timer.h"
#include "Button.h"
#include "Square.h"
#include "Scoreboard.h"
#include "Constants.h"

using namespace std;

/* GLOBAL VARIABLES */
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *title = NULL;
SDL_Surface *buttonSheet = NULL;
SDL_Surface *squareSheet = NULL;
SDL_Surface *grid = NULL;
SDL_Surface *winnerMessage = NULL;

//Font
SDL_Color titleColor = {255, 40, 40};
SDL_Color buttonColor = {180, 40, 40};
TTF_Font *titleFont = NULL;
TTF_Font *buttonFont = NULL;

//Event
SDL_Event event;

//Button
SDL_Rect clips[4];
SDL_Rect squareClips[4];

//Game Variables
Square *squares[3][3];
int turn = 0;

//Music
Mix_Music *music = NULL;
Mix_Chunk *click = NULL;

/* GLOBAL FUNCTION DECLARATIONS */
SDL_Surface *load_image(string filename) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;
    
    loadedImage = IMG_Load(filename.c_str());
    if(loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    
    if (optimizedImage != NULL) {
        Uint32 colorKey = SDL_MapRGB(optimizedImage->format, 128, 255, 255);
        SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorKey);
    }
    
    return optimizedImage;
    
}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, 
        SDL_Rect* clip) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}
bool load_files() {
    //Background Image
    background = load_image("background.png"); 
    titleFont = TTF_OpenFont( "Gobold.ttf", 40);
    buttonFont = TTF_OpenFont("Gobold Thin.ttf", 18);
    buttonSheet = load_image("buttonsheet.png");
    squareSheet = load_image("squareSheet.png");
    grid = load_image("grid.png");
    
    //Music
    music = Mix_LoadMUS("06 - Tostada.mp3");    
    click = Mix_LoadWAV("coin.wav");
    
    //Error Checking
    if (background == NULL) return false;
    if (titleFont == NULL) return false;
    if (buttonFont == NULL) return false;
    if (buttonSheet == NULL) return false;
    if (squareSheet == NULL) return false;
    if (grid == NULL) return false;
    if (music == NULL) return false;
    if (click == NULL) return false;
    
    //Sound Processing
    Mix_VolumeChunk(click, 16);
    
    return true;
}
bool init() {
    //Initialise SDL Stuff
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
    
    //Initialise Font Stuff
    if (TTF_Init() == -1) return false;
    
    //Initialise Audio
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
    
    //Generate Random Number Seed
    srand(SDL_GetTicks());
    
    //Set-up Screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen == NULL) return false;
    
    //Set Window Text
    SDL_WM_SetCaption("Tic Tac Toe", NULL);
    
    return true;
}
void clean_up() {    
    SDL_FreeSurface(background);
    SDL_FreeSurface(title);
    SDL_FreeSurface(buttonSheet);
    SDL_FreeSurface(squareSheet);
    SDL_FreeSurface(grid);
    SDL_FreeSurface(winnerMessage);
 
    TTF_CloseFont(titleFont);
    TTF_CloseFont(buttonFont);
 
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            delete squares[x][y];
        }
    }
    
    Mix_FreeChunk(click);
    Mix_FreeMusic(music);
        
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
} 
void set_clips() {
    clips[MOUSEOUT].x = 0;
    clips[MOUSEOUT].y = 0;
    clips[MOUSEOUT].w = 140;
    clips[MOUSEOUT].h = 40;
    
    clips[MOUSEOVER].x = 140;
    clips[MOUSEOVER].y = 0;
    clips[MOUSEOVER].w = 140;
    clips[MOUSEOVER].h = 40;
    
    clips[MOUSEDOWN].x = 0;
    clips[MOUSEDOWN].y = 40;
    clips[MOUSEDOWN].w = 140;
    clips[MOUSEDOWN].h = 40;
    
    clips[MOUSEUP].x = 140;
    clips[MOUSEUP].y = 40;
    clips[MOUSEUP].w = 140;
    clips[MOUSEUP].h = 40;
    
    squareClips[EMPTY].x = 0;
    squareClips[EMPTY].y = 0;
    squareClips[EMPTY].w = SQUARE_WIDTH;
    squareClips[EMPTY].h = SQUARE_HEIGHT;
    
    squareClips[HIGHLIGHTED].x = SQUARE_WIDTH;
    squareClips[HIGHLIGHTED].y = 0;
    squareClips[HIGHLIGHTED].w = SQUARE_WIDTH;
    squareClips[HIGHLIGHTED].h = SQUARE_HEIGHT;
    
    squareClips[CROSS].x = SQUARE_WIDTH * 2;
    squareClips[CROSS].y = 0;
    squareClips[CROSS].w = SQUARE_WIDTH;
    squareClips[CROSS].h = SQUARE_HEIGHT;
    
    squareClips[NOUGHT].x = SQUARE_WIDTH * 3;
    squareClips[NOUGHT].y = 0;
    squareClips[NOUGHT].w = SQUARE_WIDTH;
    squareClips[NOUGHT].h = SQUARE_HEIGHT;
}
void set_squares() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            squares[x][y] = 
                    new Square(GRID_TOPLEFT_X + (x * 8) + (x * SQUARE_WIDTH), 
                                GRID_TOPLEFT_Y + (y * 8) + (y * SQUARE_HEIGHT));
        }
    }
}
void show_squares() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            squares[x][y]->show();
        }
    }
}
void handle_squares() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            squares[x][y]->handle_event();
        }
    }
}
void reset_squares() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            squares[x][y]->set_state(EMPTY);
        }
    }
}
int check_for_winner() {
    //Tally for a winning row. The winner is the opposite of who's turn it is
    int total = 0, state = 0, x, y, winner = 0;
    
    //Check for Vertical Wins
    for (x = 0; x < 3 && winner == 0; x++) {
        //Get the state of the first square in the row
        state = squares[x][0]->get_state();
        total++;
        for (y = 1; y < 3 && state >= CROSS; y++) {
            //If the next square(s) is the same as the square at [0] then increase total
            if (squares[x][y]->get_state() == state) {
                total++;
                if (total >= 3) winner = state - 1;
            } else { break; }
        } 
        total = 0;
    }
    
    //Check for Horizontal Wins
    for (y = 0; y < 3 && winner == 0; y++) {
        //Get the state of the first square in the row
        state = squares[0][y]->get_state();
        total++;
        for (x = 1; x < 3 && state >= CROSS; x++) {
            //If the next square(s) is the same as the square at [0] then increase total
            if (squares[x][y]->get_state() == state) {
                total++;
                if (total >= 3) winner = state - 1;
            } else { break; }
        } 
        total = 0;
    }
    
    //North West to South East Diagonal Win
    state = squares[0][0]->get_state();
    total++;
    for (x = 1; x < 3 && winner == 0 && state != EMPTY; x++) {
        if (squares[x][x]->get_state() == state) {
            total++;
            if (total >= 3) winner = state - 1;
        }
    }
    
    total = 0;
    
    //South West to North East Diagonal Win
    state = squares[0][2]->get_state();
    total++;
    if (winner == 0 && state != EMPTY) {
        if (squares[1][1]->get_state() == state) total++;
        if (squares[2][0]->get_state() == state) total++;
        if (total >= 3) winner = state - 1;   
    }
    
    return winner;
}
/* END GLOBAL FUNCTION DECLARATIONS */

int main(int argc, char** argv) {
    /* PRE-LOOP SETUP */
    if (init() == false) return 1;
    if (load_files() == false) return 1;
    set_clips();
    set_squares();
    
    /* VARIABLES */
    Timer fpsCap;
    bool quit = false;
    int winner = 0;
    
    /* OBJECTS */
    Button newGameButton(50, 45, 140, 40);
    newGameButton.set_text("New Game");
    
    Scoreboard scoreboard(SCOREBOARD_X, SCOREBOARD_Y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT);
    scoreboard.load_scoreboard();
    
    title = TTF_RenderText_Solid(titleFont, "Noughts and Crosses", titleColor);  
    
    turn = PLAYER_1;
    
    /* GAME LOOP */
    while (quit == false) {
        fpsCap.start();
        
        /* EVENTS */
        while (SDL_PollEvent(&event)) {
            newGameButton.handle_event();
            handle_squares();
            
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_p) {
                    if (Mix_PlayingMusic() == 0) {
                        if (Mix_PlayMusic(music, -1) == -1) return 1;
                    } else {
                        if (Mix_PausedMusic() == 1) {
                            Mix_ResumeMusic();
                        } else {
                            Mix_PauseMusic();
                        }
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
//                if (Mix_PlayChannel(1, click, 0) == -1) return 1;
            } else if (event.type == SDL_QUIT) { 
                quit = true;
            }
        }
        
        /* LOGIC */
        winner = check_for_winner();
        
        /* RENDERING */
        apply_surface(0, 0, background, screen);
        apply_surface((SCREEN_WIDTH / 2) - (title->w / 2) + 80, 40, title, screen);
        apply_surface(GRID_X, GRID_Y, grid, screen);
        newGameButton.show();
        show_squares();
        scoreboard.show();
        
        if (winner != 0) { 
            ostringstream winMessage;
            winMessage << "Winner - Player " << winner << "!";
            winnerMessage = TTF_RenderText_Solid(titleFont, winMessage.str().c_str(), buttonColor);
            apply_surface(50, 90, winnerMessage, screen);
        }
        
        //Flip Screen
        if (SDL_Flip(screen) == -1) return 1;
        
        if (winner != 0) {
            SDL_Delay(1500);
            reset_squares();
            
            //Increase Scores
            if (winner == PLAYER_1) scoreboard.increment_player_1_score();
            if (winner == PLAYER_2) scoreboard.increment_player_2_score();
            
            winner = 0;
            turn = PLAYER_1;
        }
        
        //FPS Capping
        if ((fpsCap.get_ticks() < (1000 / FRAMES_PER_SECOND))) {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - fpsCap.get_ticks());
        }
    }  
    
    if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
    
    //Save Scoreboard
    scoreboard.save_scoreboard();
    
    //Clean Up Everything
    clean_up();
    
    return 0;
}

