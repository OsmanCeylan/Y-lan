#ifndef STARTER_H_INCLUDED
#define STARTER_H_INCLUDED

#include "hebi.h"

void game_start(yilan *obj,struct SDL_Surface *dot,SDL_Surface *screen,Timer *fps,struct SDL_Surface *bg){
    struct yilan_bas *new_one;

    new_one=(obj->get_header());
    obj->yilan_konumlar();
    apply_surface(0,0,bg,screen);

    apply_surface(new_one->yilan_x,new_one->yilan_y,dot,screen);
    while (new_one->sonraki){
        new_one=new_one->sonraki;
        apply_surface(new_one->yilan_x,new_one->yilan_y,dot,screen);
    }

}

#endif // STARTER_H_INCLUDED
