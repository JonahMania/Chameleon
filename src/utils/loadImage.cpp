#include "loadImage.hpp"
/*
Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16 *)p;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
    }
}
*/

Fragment loadImage(std::string path)
{
    SDL_Surface * loadedSurface = IMG_Load(path);


    if( loadedSurface == NULL )
    {
        std::cerr << "ERROR: Image was not loaded " << url << " " << IMG_GetError() << std::endl;
    }
       //Get rid of loaded surface
        SDL_FreeSurface( loadedSurface );

    return ret;
}
