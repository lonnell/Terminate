#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

using namespace Term::SDL;

void Turtle_Init(Term::SDL::Context term, Term::TTY tty, std::string tileset, SDL_Surface* screen, Uint32 subsystem_mask) {
    if (SDL_Init(subsystem_mask) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    } else if (SDL_WasInit(SDL_INIT_VIDEO) != 0){
        SDL_Log("SDL VIDEO NOT INITIALIZED");
        exit(1);
    } else {
        atexit(SDL_Quit);
        atexit(IMG_Quit);
        
        term.Tilemap(tileset);
        term.Framebuffer().Clear();
        Term::TTY tty( term.Framebuffer() );
        if((screen = SDL_SetVideoMode(term.Framebuffer().Width()  * term.TileWidth(), term.Framebuffer().Height() * term.TileHeight(), 32, SDL_SWSURFACE )) == NULL){
            std::cerr << "Video initialization failed: " << SDL_GetError() << std::endl;
            exit(1);
        }
        term.RenderTarget( screen );
    }
}

void termClear(){
    
}
