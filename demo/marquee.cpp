#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>


Term::Color RandomColor()
{
    return Term::Color (
        static_cast<Uint8>(rand()%255),
        static_cast<Uint8>(rand()%255),
        static_cast<Uint8>(rand()%255),
        static_cast<Uint8>1
    );
}


void RandomColors( Term::String& str )
{
    for( Term::Char& ch : str )
    {
        ch.PriColor( Term::Color::Black ).SecColor( RandomColor() );
    }
}


int main( int argc, char* argv[] )
{
    // Setup SDL and our terminal buffer.
    SDL_Init( SDL_INIT_VIDEO );

    atexit( SDL_Quit );
    atexit( IMG_Quit );
    
    /* Term::SDL::Context term( Width-In-Collems, Height-In-Rows ); */
    Term::SDL::Context term( 20, 3 );
    
    /* Tileset of ASCII characters */
    term.Tilemap( "tileset.png" );
    
    SDL_Window* window = NULL;
    SDL_Surface* screenSurf = NULL;
    
    window = SDL_CreateWindow(
        "Marquee", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        term.Framebuffer().Width()  * term.TileWidth(), 
        term.Framebuffer().Height() * term.TileHeight(),
        SDL_WINDOW_SHOWN
    );
    
    screenSurf = SDL_GetWindowSurface( window );
    
    /* Take a SDL_Surface to draw to */
    term.RenderTarget( screenSurf );

    // Prepare the marquee!
    Term::String bannerText = Term::MakeString( "Terminate Terminal emulator running SDL" );
    Term::StaticBuffer banner( bannerText.length(), 1 );
    Term::TTY tty(banner);

    // Offset used to make the text move.
    int offset = term.Framebuffer().Width();
    bool running=true;
    while(running)
    {
        SDL_Event event;
        while( SDL_PollEvent(&event) ) switch( event.type )
        {
            case SDL_QUIT:
            case SDL_KEYDOWN:
                running = false; break;
        }

        // Print some utterly unreadable randomly colored text.
        tty.Place( 0, 0 );
        RandomColors(bannerText);
        tty.Put( bannerText );
        term.Framebuffer().Clear();
        term.Framebuffer().Copy( 
            banner, 
            offset, 
            1,
            0,
            0, 
            banner.Width(), 
            banner.Height()
        );
        term.Print();
        SDL_UpdateWindowSurface(window);
        SDL_Delay(50);
        // Move text and wrap around screen.
        if( --offset < -(int)banner.Width() )
            offset = term.Framebuffer().Width();
     }
}
