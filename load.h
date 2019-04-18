#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include "SDL/SDL.h"
#include <string>

SDL_Surface *screenB;
void set_old_screen(struct SDL_Surface *scr){
    ::screenB=scr;
}

SDL_Surface *load_image(std::string filename ){
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){

        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );

        Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0, 0 );
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );

    }
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination = screenB, SDL_Rect* clip = NULL ){
    if (source==NULL)
        return;

    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

struct SDL_Surface *memory_load(){
    SDL_Surface *yeni;
    yeni=load_image("dot.png");
    return yeni;
}

#endif // LOAD_H_INCLUDED
