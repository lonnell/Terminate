/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_SDLCONTEXT_HPP
#define TERMINATE_SDLCONTEXT_HPP

#include "../terminate.hpp"
#include <SDL/SDL.h>


namespace Term
    {
namespace SDL
    {

    inline SDL_Color
    toSDLColor( const Color& c )
        {
        SDL_Color sdl;
        sdl.r = c.r;
        sdl.g = c.g;
        sdl.b = c.b;
        sdl.a = c.a;
        return sdl;
        }


    class
    Context :
        public Term::Context
        {
        public:
            Context( size_t width, size_t height );

            ~Context();

            void
            WinInit( SDL_Surface* );

            void
            Tilemap(std::string winName, int widthx, int heighty);

            SDL_Surface*
            Tilemap();

            PixDim
            TileWidth() const;

            PixDim
            TileHeight() const;

            virtual void
            Print( Char ch, size_t x, size_t y ) const override;

            virtual void
            Print() const override;

            virtual Buffer&
            Framebuffer();

        private:
            //SDL_Window*   twindow;
            //SDL_Renderer* trenderer;
            //SDL_Texture*  drawSurf;
            PixDim          twidth, theight;
            SDL_Surface*    tilemap;
            SDL_Surface*    drawSurf;
            StaticBuffer    buffer;
        };


    } // namespace SDL
    } // namespace Term
#endif //TERMINATE_SDLCONTEXT_HPP
