#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

using namespace Turtle::Context = Term::SDL;

inline void Turtle_Init(std::string WinName, int posy, int posx, Term::SDL::Context term, Term::TTY tty, std::string tileset, SDL_Window* win, SDL_Surface* winSurf, Uint32 subsystem_mask, Uint32 WinFlags, Unit32 RenFlags) {
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
        if((win = SDL_CreateWindow(WinName.c_str(), posy, posx, term.Framebuffer().Width()  * term.TileWidth(), term.Framebuffer().Height() * term.TileHeight(), WinFlags)) == NULL){
            std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
            exit(1);
        } 
        else if ((WinSurf = SDL_GetWindowSurface( win )) == NULL){
            std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
            exit(1);
        }
        term.RenderTarget( WinSurf );
    }
}

inline void Turtle_Init_Defualt(std::string WinName, Term::SDL::Context term, Term::TTY tty, SDL_Window* win, SDL_Surface* winSurf, Uint32 WinFlags){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    } else {
        atexit(SDL_Quit);
        atexit(IMG_Quit);
        
        term.Tilemap("tileset.png");
        term.Framebuffer().Clear();
        Term::TTY tty( term.Framebuffer() );
        if((win = SDL_CreateWindow(WinName.c_str, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, term.Framebuffer().Width()  * term.TileWidth(), term.Framebuffer().Height() * term.TileHeight(), WinFlags)) == NULL){
            std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
            exit(1);
        }
        else if ((WinSurf = SDL_GetWindowSurface( win )) == NULL){
            std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
            exit(1);
        }
        term.RenderTarget( WinSurf );
        Term::Char clearChar('\0');
        clearChar.PriColor( Term::Color::Black );
        clearChar.SecColor( Term::Color::White );
    }
}

inline void termClear(Term::SDL::Context term, Term::TTY tty){
    term.Framebuffer().Clear();
    tty.Place(0, 0);
}

inline void Term_Flip(SDL_Window* win, Term::SDL::Context term){
    term.Print();
    SDL_UpdateWindowSurface( win );
}
