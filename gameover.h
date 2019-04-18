#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include <string>
#include <sstream>
#include "SDL_ttf.h"

SDL_Surface *screenA;

void set_new_screen(struct SDL_Surface *scr){
    ::screenA=scr;
}

class score{
    int score0=0;
    int fps=0;
    SDL_Surface *message;
    TTF_Font *font;
    SDL_Color textColor;
  public:
    int get_score(){return score0;}
    score();
    SDL_Color return_color() {return textColor;}
    void make_fps(int );
    void update_score();
    void show_score(struct SDL_Surface *);
};

void score::show_score(struct SDL_Surface *screen){
    std::stringstream caption;
    caption << "SCORE: " << score0 ;
    message=TTF_RenderText_Solid( font, caption.str().c_str(), textColor );
    apply_surface(500,40,message,screen);
    SDL_FreeSurface(message);
}

score::score(){
    textColor = { 255,0, 20 };
    font=TTF_OpenFont( "font.ttf", 35 );
}

void score::update_score(){
    score0 += fps;
}

void score::make_fps(int fps){
    this->fps=fps;
}

void game_over(int over_screen,struct yilan_bas **liste_basi,struct SDL_Surface *background,score *score_obje){
    apply_surface(0,0,background,screenA);
    SDL_Surface *message0,*message1;

    std::stringstream caption0,caption1 ;
    caption0 << "SCORE: " << score_obje->get_score() ;
    caption1 << "Buraya kadar.." ;

    message0 = TTF_RenderText_Solid( TTF_OpenFont( "font.ttf", 50 ), caption0.str().c_str(), score_obje->return_color());
    message1 = TTF_RenderText_Solid( TTF_OpenFont( "font.ttf", 50 ), caption1.str().c_str(), score_obje->return_color());

    apply_surface(200,300,message0,screenA);
    apply_surface(200,175,message1,screenA);
    SDL_Flip(screenA);
    SDL_Delay(800);
    SDL_Quit();
}


#endif // GAMEOVER_H_INCLUDED
