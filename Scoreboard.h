/* 
 * File:   Scoreboard.h
 * Author: neckbird
 *
 * Created on 06 October 2013, 19:48
 */

#ifndef SCOREBOARD_H
#define	SCOREBOARD_H

#include "SDL/SDL.h"
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include "Globals.h"
#include "Global_Functions.h"
#include "Constants.h"

class Scoreboard {
public:
    Scoreboard(int, int, int, int);
    ~Scoreboard();
    void show();
    void load_scoreboard();
    void save_scoreboard();
    
    //Accessor Functions
    SDL_Rect get_box();
    void set_box(SDL_Rect );
    string get_player_1();
    void set_player_1(string name);
    string get_player_2();
    void set_player_2(string name);
    int get_player_1_score();
    void set_player_1_score(int);
    int get_player_2_Score();
    void set_player_2_score(int);
    void increment_player_1_score();
    void increment_player_2_score();
        
private:
    SDL_Surface *player_1_text, *player_2_text;
    SDL_Surface *player_1_score, *player_2_score;
    SDL_Rect box, horizontal_divider, vertical_divider;
    SDL_Color dividerColor;
    
    string player_1, player_2;
    stringstream s1, s2;
    int score_player_1, score_player_2;
};

#endif	/* SCOREBOARD_H */

