#include <iostream>
#include <fstream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

const Term::Color BGCOLOR( 255,200,0,1);
const Term::Color FONTCOLOR(0,0,0,1);


int main( int argc, char* argv[] )
    {
    SDL_Init( SDL_INIT_VIDEO );
    atexit( SDL_Quit );
    atexit( IMG_Quit );

    Term::SDL::Context term( 60, 30 );
    term.Tilemap( "tileset.png" );
    
    term.WinInit( "Maze", term.Framebuffer().Width()  * term.TileWidth(), term.Framebuffer().Height() * term.TileHeight());
    term.Framebuffer().ClearChar( Term::Char('\0', 0, BGCOLOR, FONTCOLOR));
    term.Framebuffer().Clear();


    Term::TTY tty(term.Framebuffer());
    tty.Set( Term::TTY::VScroll );
    tty.Set( Term::TTY::Wrap );
    tty.PriColor( BGCOLOR );
    tty.SecColor( FONTCOLOR );

    bool running = true;
    srand (time(NULL));
    while(running)
        {
        SDL_Event event;
        while( SDL_PollEvent(&event) ) switch(event.type)
            {
            case SDL_QUIT:
            case SDL_KEYDOWN:
                running = false; break;
            }

        tty.Put(0x2F + (0x2D * (rand() % 2)));
        term.Print();
        term.Term_Present();
        SDL_Delay(1);
        }
    }
