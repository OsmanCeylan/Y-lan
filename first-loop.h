#ifndef FIRST-LOOP_H_INCLUDED
#define FIRST-LOOP_H_INCLUDED

#include "button.h"

SDL_Surface *fbg=NULL;

void first_load_files(){
    fbg=load_image("fbg.jpg");
}

bool select_screen(struct SDL_Surface *scr,int *fps,union SDL_Event *s_event,struct SDL_Surface *background){
    bool done=false;
    button seviye1(1);
    button seviye2(2);
    button seviye3(3);
    int konumla=2;
    int bgX=0,bgY=0;

    while (done==false){

        apply_surface( bgX,bgY, background, scr );
        apply_surface( bgX,bgY, background, scr );
        bgX -= konumla;

        if( bgX <= -75 )
            konumla=-2;
        if (bgX >=0)
            konumla=2;

        if ( SDL_PollEvent( s_event ) ){
            if (seviye1.f_handle_events(s_event,scr)==true) {*fps= 25; done=true;}
            if (seviye2.f_handle_events(s_event,scr)==true) {*fps= 50; done=true;}
            if (seviye3.f_handle_events(s_event,scr)==true) {*fps= 100; done=true;}

            if( s_event->type == SDL_QUIT )
                SDL_Quit();
        }

        seviye1.show();
        seviye2.show();
        seviye3.show();

        SDL_Flip(scr);
    }

    return true;
}

int first_screens(struct SDL_Surface *screen0){
    bool quit=false;
    first_load_files();

    bool secondary=false;
    int bgX=0,bgY=0;
    Timer fps;
    int konumla=2;
    button start_button(-1);
    button quit_button(0);
    SDL_Event f_event;
    int FPS_new;

    while (quit==false){
        fps.start();

        apply_surface( bgX,bgY, fbg, screen0 );
        apply_surface( bgX,bgY,fbg, screen0 );
        bgX -= konumla;

        if( bgX <= -75 )
            konumla=-2;
        if (bgX >=0)
            konumla=2;

        if ( SDL_PollEvent( &f_event ) ){

            if(start_button.f_handle_events(&f_event,screen0)==true) secondary=true;
            quit_button.f_handle_events(&f_event,screen0);

            if( f_event.type == SDL_QUIT )
                SDL_Quit();
        }

        start_button.show();
        quit_button.show();

        SDL_Flip(screen0);

        if (secondary==true){
            start_button.yoket();
            quit_button.yoket();
            quit=select_screen(screen0,&FPS_new,&f_event,fbg);
        }
    }
    return FPS_new;
}

#endif // FIRST-LOOP_H_INCLUDED
