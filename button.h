#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

struct nokta{
  int x;
  int y;
} ;

class button{
    int x;
    int y;
    TTF_Font *font;
    SDL_Color textColor = { 255,0, 20 };
    int actions;
    SDL_Surface *message;
    SDL_Surface *over_anim;
  public:
    bool mouse_over;
    SDL_Surface *image=NULL;
    std::stringstream caption;
    bool f_handle_events(union SDL_Event *,struct SDL_Surface *);
    void over_button_animation();
    void click_button_animation();
    button(int );
    int get_x(){return x;}
    int get_y(){return y;}
    void show();
    void yoket();
};

button::button(int act){
    font = TTF_OpenFont( "font.ttf", 35 );
    image=load_image("button.png");
    over_anim=load_image("over_anim.png");

    if (act==-1){
        x=300; y=200;
        caption << "BASLA" ;
    }

    if (act==0){
        x=300; y=500;
        caption << "  CIK" ;
    }

    if (act==1){
        x=300; y=150;
        caption << "LVL 1" ;
    }

    if (act==2){
        x=300; y=320;
        caption << "LVL 2" ;
    }

    if (act==3){
        x=300; y=500;
        caption << "LVL 3" ;
    }

    actions=act;
    message = TTF_RenderText_Solid( font, caption.str().c_str(), textColor );
}

void button::show(){
    if (mouse_over==true)
     over_button_animation();

    if (image==NULL) return;

    apply_surface(x-40,y,image);
    apply_surface(x-4,y+4,message);
}

void button::over_button_animation(){
    struct nokta anim;
    int i;

    if (image==NULL) return;

    for (i=0;i<2;i++){
        anim.x=x-47;
        if (i==0) anim.y=y-1;
        if (i==1) anim.y=image->h+y-4;
        while(anim.x<image->w+x-50){
            apply_surface(anim.x,anim.y,over_anim);
            anim.x+=2;
        }
    }

    for (i=0;i<2;i++){
        anim.y=y;
        if (i==0) anim.x=x-47;
        if (i==1) anim.x=image->w+x-48;
        while (anim.y<image->h+y-2){
            apply_surface(anim.x,anim.y,over_anim);
            anim.y+=2;
        }
    }

}

void button::yoket(){
    image=NULL;
    x=0;y=0;
}

void button::click_button_animation(){
    x+=20; y+=6;
    font=TTF_OpenFont("font.ttf",27);
    textColor={0,255,0};
    image = load_image("button2.png");

}

bool button::f_handle_events(union SDL_Event *f_event,struct SDL_Surface *screen){
    int x = 0, y = 0;

    if (image!=NULL){
        if ( f_event->type == SDL_MOUSEMOTION ){

            x = f_event->motion.x;
            y = f_event->motion.y;

            if( ( x > this->x-40 ) && ( x < this->x -40 + image->w ) && ( y > this->y ) && ( y < this->y + 60 ) )
                mouse_over=true;
            else
                mouse_over=false;
        }

        if( f_event->type == SDL_MOUSEBUTTONDOWN ){
            if( f_event->button.button == SDL_BUTTON_LEFT ){

                x = f_event->button.x;
                y = f_event->button.y;

            if( ( x > this->x-40 ) && ( x < this->x -40 + image->w ) && ( y > this->y ) && ( y < this->y + 60 ) )
                 click_button_animation();
            }
        }

        if(f_event->type == SDL_MOUSEBUTTONUP ){
            if( f_event->button.button == SDL_BUTTON_LEFT ){

                x = f_event->button.x;
                y = f_event->button.y;

                if( ( x > this->x ) && ( x < this->x + 200 ) && ( y > this->y ) && ( y < this->y + 60 ) ){
                    if (actions==-1 || actions==1 || actions==2 || actions==3 )
                        return true;
                    if (actions==0){
                        SDL_Delay(500);
                        SDL_Quit();
                    }
                }
            }
        }
        return false;
    }
}

#endif // BUTTON_H_INCLUDED
