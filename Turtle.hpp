#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

using namespace Turtle::Context = Term::SDL;

inline void Turtle_Init(Term::SDL::Context term, Term::TTY tty, std::string tileset, SDL_Surface* screen, Uint32 subsystem_mask) {
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

inline void Turtle_Init_Defualt(Term::SDL::Context term, Term::TTY tty, SDL_Surface* screen){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    } else {
        atexit(SDL_Quit);
        atexit(IMG_Quit);
        
        term.Tilemap("tileset.png");
        term.Framebuffer().Clear();
        Term::TTY tty( term.Framebuffer() );
        if((screen = SDL_SetVideoMode(term.Framebuffer().Width()  * term.TileWidth(), term.Framebuffer().Height() * term.TileHeight(), 32, SDL_SWSURFACE )) == NULL){
            std::cerr << "Video initialization failed: " << SDL_GetError() << std::endl;
            exit(1);
        }
        term.RenderTarget( screen );
        Term::Char clearChar('\0');
        clearChar.PriColor( Term::Color::Black );
        clearChar.SecColor( Term::Color::White );
    }
}

inline void termClear(Term::SDL::Context term, Term::TTY tty){
    term.Framebuffer().Clear();
    tty.Place(0, 0);
}

inline void Term_Flip(SDL_Surface* screen, Term::SDL::Context term){
    term.Print();
    SDL_Flip(screen);
}
