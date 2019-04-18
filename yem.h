#ifndef YEM_H_INCLUDED
#define YEM_H_INCLUDED

#include "hebi.h"

struct yem_tmp{
    int x;
    int y;
};

class yemlik{
    int yem_x;
    int yem_y;
  public:
    SDL_Surface *yem;
    yemlik(struct yilan_bas *,struct SDL_Surface *);
    int yem_getx();
    int yem_gety();
};

yemlik::yemlik(struct yilan_bas *head,struct SDL_Surface *yem){
    this->yem=yem;
    bool yer_ayari=false;
    bool yer_ayari_2;
    struct yilan_bas *headers;

    while(yer_ayari==false){
        yer_ayari_2=true;
        headers=head;
        srand(time(NULL));
        yem_x=(rand()%35)+3;
        yem_y=(rand()%31)+3;

        while (headers){
           if (headers->yilan_x==yem_x*20 && headers->yilan_y==yem_y*20) {yer_ayari_2==false; break;}
           headers=headers->sonraki;
        }

        if (yer_ayari_2==true) yer_ayari=true;
    }
}

int yemlik::yem_getx(){
    return yem_x;
}

int yemlik::yem_gety(){
    return yem_y;
}

struct yem_tmp yem(yilan *nesne,struct SDL_Surface *yem,struct SDL_Surface *screen,bool status){
    yemlik yem0(nesne->get_header(),yem);
    apply_surface(yem0.yem_getx()*20,yem0.yem_gety()*20,yem0.yem,screen);

    struct yem_tmp new_tmp;
    new_tmp.x=yem0.yem_getx()*20;
    new_tmp.y=yem0.yem_gety()*20;
    return new_tmp;
}

bool yem_check(yilan *object,struct yem_tmp yeni_yem,struct Mix_Chunk *chunk,score *score_obj){
    struct yilan_bas *kontrol_bas;
    kontrol_bas=object->get_header();
    if (kontrol_bas->yilan_x==yeni_yem.x && kontrol_bas->yilan_y==yeni_yem.y){
        object->yilan_add();
        Mix_PlayChannel( -1, chunk, 0 );
        score_obj->update_score();
        return false;
    }
    return true;
}
#endif // YEM_H_INCLUDED
