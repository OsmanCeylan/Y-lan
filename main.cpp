#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "load.h"
#include <string>
#include "yem.h"
#include "time.h"
#include "starter.h"
#include "hebi.h"
#include "gameover.h"
#include "first-loop.h"

const int SCREEN_WIDTH = 780;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *load = NULL;
SDL_Surface *yem_pic=NULL;
TTF_Font *font=NULL;
Mix_Chunk *scratch = NULL;
SDL_Event event;

bool init(){
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    set_new_screen(screen);
    set_old_screen(screen);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    SDL_WM_SetCaption( "Yılan", NULL );
    return true;
}

bool load_files(){

    background = load_image( "bg.png" );
    load=memory_load();
    yem_pic=load_image("yem.png");
    font = TTF_OpenFont("font.ttf",20);
    scratch = Mix_LoadWAV( "scratch.wav" );
    return true;
}

int main( int argc, char* args[] )
{
    bool quit = false;
    init();  load_files();
    const int FRAMES_PER_SECOND=first_screens(screen);

    Timer fps;
    yilan new_yilan;
    bool status = false;
    new_yilan.yilan_add();
    new_yilan.yilan_add();
    struct yem_tmp new_yem;
    score my_score;
    my_score.make_fps(FRAMES_PER_SECOND);

    apply_surface(0,0,background,screen);
    while( quit == false ){
        fps.start();

        if( SDL_PollEvent( &event ) ){
            new_yilan.handle_events(&event);
            new_yilan.quit_event(&event);

        }
        game_start(&new_yilan,load,screen,&fps,background);

        my_score.show_score(screen);
        new_yilan.yilan_animate(background,&my_score);

        if (status==false){
            new_yem=yem(&new_yilan,yem_pic,screen,status);
            status=true;
        }
        else apply_surface(new_yem.x,new_yem.y,yem_pic,screen);

        status=yem_check(&new_yilan,new_yem,scratch,&my_score);

        SDL_Flip(screen);

        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        SDL_Delay(( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );

    }
    return 0;
}
