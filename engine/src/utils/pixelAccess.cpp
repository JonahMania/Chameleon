#include "pixelAccess.hpp"

SDL_Color getPixel(SDL_Surface *surface, int i)
{
    //Return color
    SDL_Color ret;
    //Value to use when finding pixel values
    Uint32 temp;
    //Bytes per pixel
    int bytesPerPixel = surface->format->BytesPerPixel;

    if( SDL_LockSurface(surface) < 0 )
    {
        std::cerr<<"Error: Could not lock surface "<<SDL_GetError()<<std::endl;
        return SDL_Color({r:0,g:0,b:0,a:0});
    }
    //Current pixel
    Uint8 *pixel = (Uint8 *)surface->pixels + i * bytesPerPixel;
    SDL_UnlockSurface(surface);

    switch(bytesPerPixel)
    {
        case 1:
            ret = surface->format->palette->colors[*pixel];
            ret.a = 0;
            return ret;
        case 2:
            std::cerr<<"Error: 16 bit pixel format not implemented"<<std::endl;
            break;
        case 3:
            ret.r = (Uint8)pixel[3];
            ret.g = (Uint8)pixel[1];
            ret.b = (Uint8)pixel[2];
            ret.a = 0;
            return ret;
            break;

        case 4:
            std::cerr<<"Error: 32 bit pixel format not implemented"<<std::endl;
            // temp = *pixel & surface->format->Rmask;
            // temp = temp >> surface->format->Rshift;
            // temp = temp << surface->format->Rloss;
            // ret.r = (Uint8)temp;
            // temp = *pixel & surface->format->Gmask;
            // temp = temp >> surface->format->Gshift;
            // temp = temp << surface->format->Gloss;
            // ret.g = (Uint8)temp;
            // temp = *pixel & surface->format->Bmask;
            // temp = temp >> surface->format->Bshift;
            // temp = temp << surface->format->Bloss;
            // ret.b = (Uint8)temp;
            // temp = *pixel & surface->format->Amask;
            // temp = temp >> surface->format->Ashift;
            // temp = temp << surface->format->Aloss;
            // ret.a = (Uint8)temp;
            //
            // return ret;
            break;
        default:
            std::cerr<<"Error: Unrecognized pixel format"<<std::endl;
            break;

        return SDL_Color({r:0,g:0,b:0,a:0});

    }
}

void setPixel(SDL_Surface *surface, int i, SDL_Color color)
{
    //Bytes per pixel
    int bytesPerPixel = surface->format->BytesPerPixel;

    if( SDL_LockSurface(surface) < 0 )
    {
        std::cerr<<"Error: Could not lock surface "<<SDL_GetError()<<std::endl;
        return;
    }
    //Current pixel
    Uint8 *pixel = (Uint8 *)surface->pixels + i * bytesPerPixel;

    switch(bytesPerPixel)
    {
        case 1:
            std::cerr<<"Error: 8 bit pixel format not implemented"<<std::endl;
            break;
        case 2:
            std::cerr<<"Error: 16 bit pixel format not implemented"<<std::endl;
            break;
        case 3:
            pixel[0] = color.r;
            pixel[1] = color.g;
            pixel[2] = color.b;
            break;
        case 4:
            std::cerr<<"Error: 32 bit pixel format not implemented"<<std::endl;
            break;
    }

    SDL_UnlockSurface(surface);

}
