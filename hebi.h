#ifndef HEBI_H_INCLUDED
#define HEBI_H_INCLUDED

#include "gameover.h"

struct yilan_bas{
    int yilan_x;
    int yilan_y;
    struct yilan_bas *sonraki;
};

struct yilan_bas *add(int x,int y){
    struct yilan_bas *gecici;
    gecici=(struct yilan_bas *)malloc(sizeof(struct yilan_bas));
    gecici->yilan_x=x;
    gecici->yilan_y=y;
    gecici->sonraki=NULL;
    return gecici;

}

void dugume_ekle(int x,int y,struct yilan_bas **liste_basi){
    struct yilan_bas *a=add(x,y);

    if(*liste_basi==NULL){
        a->sonraki=*liste_basi;
        *liste_basi=a;
    }
    else{
        struct yilan_bas *x=*liste_basi;
        while(x->sonraki!=NULL)
            x=x->sonraki;
        x->sonraki=a;
        a->sonraki=NULL;
    }
}

class yilan{
    struct yilan_bas *header;
    int uzunluk;
  public:
    int yon;
    struct yilan_bas *get_header();
    yilan();
    int get_uzunluk(struct yilan_bas *);
    void yilan_add();
    void yilan_animate(struct SDL_Surface *,score *);
    void yilan_konumlar();
    int handle_events(union SDL_Event *);
    void quit_event(union SDL_Event *);
    void stop_animation(){ yon=0; }

};

yilan::yilan(){
    yon=1;
    header=(struct yilan_bas *)malloc(sizeof(struct yilan_bas));
    uzunluk=1;
    header->yilan_x=200;
    header->yilan_y=400;
    header->sonraki=NULL;
    yon=1;
}

struct yilan_bas *yilan::get_header(){
    return header;
}

void yilan::quit_event(union SDL_Event *ev){
    if( ev->type == SDL_QUIT )
        SDL_Quit();
}

void yilan::yilan_animate(struct SDL_Surface *BackG,score *temp){
    struct yilan_bas *head=header;
    struct yilan_bas *tmp=NULL;

    if (head==NULL) (tmp)=NULL;
    else{
        while (head){
            dugume_ekle(head->yilan_x,head->yilan_y,&tmp);
            head=head->sonraki;
        }
    }

    head=header;
    if (yon==1)
        header->yilan_x+=20;
    if (yon==2)
        header->yilan_y-=20;
    if (yon==3)
        header->yilan_y+=20;
    if (yon==4)
        header->yilan_x-=20;

    if (header->yilan_x<0 || header->yilan_x>780 || header->yilan_y<0 || header->yilan_y>700){
        stop_animation();
        game_over(1,&header,BackG,temp);
    }

    head=header;
    head=head->sonraki;
    while (head){
       if (header->yilan_x==head->yilan_x && header->yilan_y==head->yilan_y ){
            stop_animation();
            game_over(2,&header,BackG,temp);
       }
       head=head->sonraki;
    }

    struct yilan_bas *tmp0=tmp;
    head=header;
    tmp0=tmp;
    head=head->sonraki;
    while (head){
        head->yilan_x=tmp0->yilan_x;
        head->yilan_y=tmp0->yilan_y;
        head=head->sonraki; tmp0=tmp0->sonraki;
    }

    head=header;
    tmp0=tmp;
    while (head){
        head=head->sonraki; tmp0=tmp0->sonraki;
    }
}

void yilan::yilan_add(){
    struct yilan_bas *bas=header;
    struct yilan_bas *new_one=add(0,0);

    while(bas->sonraki)
       bas=bas->sonraki;
    bas->sonraki=new_one;

    new_one->sonraki=NULL;
    new_one->yilan_x =bas->yilan_x-20;
    new_one->yilan_y =bas->yilan_y;
}

void yilan::yilan_konumlar(){
    struct yilan_bas *head=header;
    while(head){
        //printf("%d-%d\t",head->yilan_x,head->yilan_y);
        head=head->sonraki;
    }
}

int yilan::handle_events(union SDL_Event *ev){
    if( ev->type == SDL_KEYDOWN ){
        if (yon==4 || yon==1){
            if ( ev->key.keysym.sym ==SDLK_UP){
                yon=2;
             }
            else if ( ev->key.keysym.sym ==SDLK_DOWN){
                yon=3;
             }
        }

        if (yon==2 || yon==3){
            if ( ev->key.keysym.sym ==SDLK_LEFT){
                yon=4;
            }
            else if ( ev->key.keysym.sym ==SDLK_RIGHT){
                yon=1;
            }
        }
    }
}

#endif // HEBI_H_INCLUDED
