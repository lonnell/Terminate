/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source
// for more information.
/////////////////////////////////////////////

#include "sdl/context.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <stdexcept>


namespace Term
    {
namespace SDL
    {


    Context::Context( size_t width, size_t height) :
        twidth(0), theight(0),
        tilemap(nullptr),
        drawSurf(nullptr),
        buffer( width, height )
        {
        }


    Context::~Context()
    {
        if(tilemap != nullptr )
        {
            SDL_DestroyTexture(tilemap);
            tilemap = NULL;
        }
        if(trenderer != nullptr)
        {
            SDL_DestroyRenderer( trenderer );
            trenderer = NULL;
        }
        if(twindow != nullptr)
        {
            SDL_DestroyWindow(twindow);
            twindow = NULL;
        }
    }


    void
    Context::TermWindow(SDL_Window* win)
    {
        twindow = win;
    }
    
    //Context::RenderTarget(SDL_Surface* surf)
    void
    Context::TermRenderer( SDL_Renderer* ren )
    {
        trenderer = ren;
    }


    void
    Context::Tilemap( std::string path )
        {
        SDL_Surface* newTilemap = IMG_Load( path.c_str() );
        if( newTilemap == nullptr )
            throw std::runtime_error( "Error opening file: " + path );
        if( newTilemap->format->BitsPerPixel != 8 )
            throw std::runtime_error( "Image must be color indexed: "+path );

        if( tilemap != nullptr )
            SDL_DestroyTexture(tilemap);
        tilemap = newTilemap;
        twidthpx = tilemap->w;
        theightpx = tilemap->h;
        twidth = tilemap->w / 16;
        theight = tilemap->h / 16;
        }

    //SDL_Surface* Context::Tilemap()
    SDL_Texture*
    Context::Tilemap()
        {
        return tilemap;
        }


    PixDim
    Context::TileWidth() const
        {
        return twidth;
        }


    PixDim
    Context::TileHeight() const
        {
        return theight;
        }


    void
    Context::Print( Char ch, size_t x, size_t y ) const
        {
        SDL_Color colors[2] = {
            toSDLColor( ch.PriColor() ),
            toSDLColor( ch.SecColor() ) };
        if( SDL_SetColors( tilemap, colors, 0, 2 ) == 0 )
            throw std::runtime_error(
                "Tilemap missing palette." );

        // Convert the ASCII value to tilemap coordinates.
        Sint16 tilex = (ch.ASCII() % 16) * TileWidth();
        Sint16 tiley = (ch.ASCII() / 16) * TileHeight();
        SDL_Rect tile = {
            tilex, tiley,
            static_cast<Uint16>(TileWidth()),
            static_cast<Uint16>(TileHeight())};
        SDL_Rect dst = {
            static_cast<Sint16>(x * TileWidth()),
            static_cast<Sint16>(y * TileHeight()),
            0,0 };

        //SDL_BlitSurface( tilemap, &tile, drawSurf, &dst );
        SDL_RenderCopy( trenderer, tilemap, 
        }


    void
    Context::Print() const
        {
        for( size_t y=0; y<buffer.Height(); ++y )
        for( size_t x=0; x<buffer.Width(); ++x )
            Print( buffer.Get(x,y), x, y );
        }


    Buffer&
    Context::Framebuffer()
        {
        return buffer;
        }


    } // namespace SDL
    } // namespace Term
