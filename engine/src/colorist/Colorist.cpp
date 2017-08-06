#include "../utils/pixelAccess.hpp"
#include "../include/Colorist.hpp"

Colorist::Colorist()
{

}

bool Colorist::addPalette(std::string name, Palette p)
{
    if(palettes.find(name) != palettes.end())
    {
        std::cerr<<"Error: Palette with name '"<<name<<"' already exists"<<std::endl;
        return false;
    }

    palettes.insert(std::pair<std::string,Palette>(name, p));

    return true;
}

bool Colorist::paintSurface(std::string paletteName, SDL_Surface *surface)
{
    SDL_Color pixelColor;
    Palette palette;
    std::map<SDL_Color,SDL_Color> colorMap;

    if(surface == NULL)
    {
        std::cerr<<"Error: Surface is NULL"<<std::endl;
        return false;
    }
    //Make sure our palette exists
    if(palettes.find(paletteName) == palettes.end())
    {
        std::cerr<<"Error: Palette '"<<paletteName<<"' does not exist"<<std::endl;
        return false;
    }
    //Get palette and color map
    palette = palettes.at(paletteName);
    palette.generatePalette(colorKeys);
    colorMap = palette.getColorMap();

    for(int i = 0; i < surface->w * surface->h; i++)
    {
        pixelColor = getPixel(surface, i);
        if(colorMap.find(pixelColor) != colorMap.end())
        {
            SDL_Color newPixelColor = colorMap.at(pixelColor);
            setPixel(surface, i, newPixelColor);
        }
    }

    return true;
}

bool Colorist::pushColorKey(SDL_Color color)
{
    //Make sure alpha is set to 0
    color.a = 0;
    colorKeys.push_back(color);
}

SDL_Texture *Colorist::createTexture(Template temp, std::string paletteName, SDL_Renderer* renderer)
{
    SDL_Texture *ret;
    SDL_Surface *surface = temp.getSurface();
    //Create temp surface to paint
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0, 0, 0, 0);
    if(tempSurface == NULL)
    {
        std::cerr<<"Error: Could not create new surface "<<SDL_GetError()<<std::endl;
        return NULL;
    }
    //Fill for color key
    if(SDL_FillRect(tempSurface, NULL, SDL_MapRGB(tempSurface->format, 255, 0, 255)))
    {
        std::cerr<<"Error: Could not fill surface "<<SDL_GetError()<<std::endl;
    }
    SDL_SetColorKey( tempSurface, SDL_TRUE, SDL_MapRGB( tempSurface->format, 0xFF, 0, 0xFF ) );
    //Copy original surface to new surface
    if(SDL_BlitSurface(surface, NULL, tempSurface, NULL))
    {
        std::cerr<<"Error: Could not blit surface "<<SDL_GetError()<<std::endl;
        SDL_FreeSurface(tempSurface);
        return NULL;
    }
    //Paint new surface
    if(!paintSurface(paletteName, tempSurface))
    {
        SDL_FreeSurface(tempSurface);
        return NULL;
    }
    //Create texture
    ret = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return ret;
}

SDL_Surface *Colorist::createSample(SDL_Surface *surface, unsigned int w, unsigned int h)
{
    SDL_Surface *ret;
    SDL_Surface *temp;
    std::map<SDL_Color,SDL_Color> colorMap;
    SDL_Rect dest;

    ret = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    if(ret == NULL)
    {
        std::cerr<<"Error: Could not create new surface "<<SDL_GetError()<<std::endl;
        return NULL;
    }
    if(SDL_FillRect(ret, NULL, SDL_MapRGB(ret->format, 255, 0, 255)))
    {
        std::cerr<<"Error: Could not fill surface "<<SDL_GetError()<<std::endl;
    }
    dest.w = surface->w;
    dest.h = surface->h;
    dest.x = 0;
    dest.y = 0;

    for(auto& palette : palettes)
    {
        //Create a new surface so we dont ruin the we have
        temp = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0, 0, 0, 0);
        //Copy original surface to new surface
        if(SDL_BlitSurface(surface, NULL, temp, NULL))
        {
            std::cerr<<"Error: Could not blit surface "<<SDL_GetError()<<std::endl;
        }
        //Paint the temp surface
        if(!paintSurface(palette.first, temp))
        {
            std::cerr<<"Error: Could not paint surface "<<SDL_GetError()<<std::endl;
            continue;
        }
        //Copy to the final sample surface
        if(SDL_BlitSurface(temp, NULL, ret, &dest))
        {
            std::cerr<<"Error: Could not blit surface "<<SDL_GetError()<<std::endl;
        }
        //Free the new surface
        SDL_FreeSurface(temp);
        //Move one to the right
        dest.x += dest.w;
        //If we are going off the edge
        if(dest.x + dest.w >= w)
        {
            dest.x = 0;
            dest.y += dest.h;
            //If we are goint off the bottom
            if(dest.y + dest.h >= h)
            {
                break;
            }
        }
    }
    return ret;
}
