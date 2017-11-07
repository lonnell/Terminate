#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

void CheckSDLInit(signed short int& sdlReturnVal) {
    if (sdlReturnVal < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
}
