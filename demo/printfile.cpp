#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

const Term::Color BGCOLOR( 255,200,0,1 );
const Term::Color FONTCOLOR( 0,0,0,1 );

int main( int argc, char* argv[] )
{
    SDL_Init( SDL_INIT_VIDEO );
    atexit( SDL_Quit );
    atexit( IMG_Quit );

    /* Term::SDL::Context term( Width-In-Collems, Height-In-Rows ); */
    Term::SDL::Context term( 60, 30 );
    
    /* Tileset of ASCII characters */
    term.Tilemap( "tileset.png" );
    
    SDL_Window* window = NULL;
    SDL_Surface* screenSurf = NULL;
    
    window = SDL_CreateWindow(
        "Printfile", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        term.Framebuffer().Width()  * term.TileWidth(), 
        term.Framebuffer().Height() * term.TileHeight(),
        SDL_WINDOW_SHOWN
    );
    
    screenSurf = SDL_GetWindowSurface( window );
    
    /* Take a SDL_Surface to draw to */
    term.RenderTarget( screenSurf );
    
    term.Framebuffer().ClearChar( Term::Char('\0').PriColor(BGCOLOR).SecColor(Term::Color::Black) );
    term.Framebuffer().Clear();


    using Term::TTY;
    TTY tty(term.Framebuffer());
    tty.Set( TTY::VScroll ).PriColor( BGCOLOR ).SecColor( FONTCOLOR );

    if( argc != 2 )
    {
        tty.Place( 4, term.Framebuffer().Height()/2 );
        tty.Put( "Usage: Specify a textfile as a command line argument." );
    }

    std::ifstream file( argv[1] );

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while( SDL_PollEvent(&event) ) switch(event.type)
        {
            case SDL_QUIT:
            case SDL_KEYDOWN:
                running = false; break;
        }

        if( file.good() )
        {
            char c;
            file.get(c);
            tty.Put(c);
        }

        term.Print();
        SDL_UpdateWindowSurface(window);
        SDL_Delay(5);
    }
}
