/* 
 * File:   Scoreboard.cpp
 * Author: neckbird
 * 
 * Created on 06 October 2013, 19:48
 */

#include "Scoreboard.h"

const int DIVIDER_WIDTH = 6;

Scoreboard::Scoreboard(int x, int y, int w, int h) {
    score_player_1 = 0;
    score_player_2 = 0;
    
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    
    player_1_text = TTF_RenderText_Solid(buttonFont, "Player 1", buttonColor);
    player_2_text = TTF_RenderText_Solid(buttonFont, "Player 2", buttonColor);
    
    vertical_divider.x = (box.x + (box.w / 2) - 3);
    vertical_divider.y = box.y;
    vertical_divider.w = DIVIDER_WIDTH;
    vertical_divider.h = box.h;
    
    horizontal_divider.x = box.x;
    horizontal_divider.y = box.y + 40;
    horizontal_divider.w = box.w;
    horizontal_divider.h = DIVIDER_WIDTH;
    
    s1 << score_player_1;
    player_1_score = TTF_RenderText_Solid(buttonFont, s1.str().c_str(), buttonColor);
    
    s2 << score_player_2;
    player_2_score = TTF_RenderText_Solid(buttonFont, s2.str().c_str(), buttonColor);
}

Scoreboard::~Scoreboard() {
    SDL_FreeSurface(player_1_text);
    SDL_FreeSurface(player_2_text);
    SDL_FreeSurface(player_1_score);
    SDL_FreeSurface(player_2_score);
}

void Scoreboard::show() {
    SDL_FillRect(screen, &horizontal_divider, SDL_MapRGB(screen->format, 0x32, 0x9F, 0x32));
    SDL_FillRect(screen, &vertical_divider, SDL_MapRGB(screen->format, 0x32, 0x9F, 0x32));
    
    apply_surface(box.x + (box.w / 2) - (player_1_text->w) - 13, box.y + 10, player_1_text, screen);
    apply_surface(box.x + (box.w / 2) + 13, box.y + 10, player_2_text, screen);
    
    apply_surface(box.x + (box.w / 2) - (player_1_score->w) - 13, box.y + 50, player_1_score, screen);
    apply_surface(box.x + (box.w / 2) + 13, box.y + 50, player_2_score, screen);
}

void Scoreboard::load_scoreboard() {
    ifstream load("scores.sav");
    
    if (load != NULL) {
        int score;
        
        load >> score;
        set_player_1_score(score);
        
        load >> score;
        set_player_2_score(score);
        
        load.close();
    }
}

void Scoreboard::save_scoreboard() {
    ofstream save("scores.sav");
    
    save << score_player_1;
    save << " ";
    save << score_player_2;
    
    save.close();
}
    
//Accessor Functions
SDL_Rect Scoreboard::get_box() {
    return box;
}

void Scoreboard::set_box(SDL_Rect newBox) {
    box = newBox;
}

string Scoreboard::get_player_1() {
    return player_1;
}

void Scoreboard::set_player_1(string name) {
    player_1 = name;
    player_1_text = TTF_RenderText_Solid(buttonFont, player_1.c_str(), buttonColor);
}

string Scoreboard::get_player_2() {
    return player_2;
}

void Scoreboard::set_player_2(string name) {
    player_2 = name;
    player_2_text = TTF_RenderText_Solid(buttonFont, player_2.c_str(), buttonColor);
}

int Scoreboard::get_player_1_score() {
    return score_player_1;
}

void Scoreboard::set_player_1_score(int score) {
    if (score >= 0) {
        score_player_1 = score;
        s1.str("");
        s1 << score_player_1;
        player_1_score = TTF_RenderText_Solid(buttonFont, s1.str().c_str(), buttonColor);
    }
}

int Scoreboard::get_player_2_Score() {
    return score_player_2;
}

void Scoreboard::set_player_2_score(int score) {
    if (score >= 0) {
         score_player_2 = score;
        s2.str("");
        s2 << score_player_2;
        player_2_score = TTF_RenderText_Solid(buttonFont, s2.str().c_str(), buttonColor);
    }
}

void Scoreboard::increment_player_1_score() {
    score_player_1++;
    s1.str("");
    s1 << score_player_1;
    player_1_score = TTF_RenderText_Solid(buttonFont, s1.str().c_str(), buttonColor);
}

void Scoreboard::increment_player_2_score() {
    score_player_2++;
    s2.str("");
    s2 << score_player_2;
    player_2_score = TTF_RenderText_Solid(buttonFont, s2.str().c_str(), buttonColor);
}

