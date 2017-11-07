#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>
#include <cstdlib>

using namespace Term;

void Turtle_Init(Uint32 subsystem_mask) {
    if (SDL_Init(subsystem_mask) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
}
