#include "../utils/colorUtils.hpp"
#include "../utils/pixelAccess.hpp"
#include "../include/RenderableState.hpp"

//Compare operator for SDL_Color so that std::map will work
bool operator<(const SDL_Color& a, const SDL_Color& b)
{
    return luminance(a) < luminance(b);
}
//Custom compare used to sort colors
struct luminanceSort
{
    inline bool operator()(const SDL_Color& a, const SDL_Color& b)
    {
        return luminance(a) < luminance(b);
    }
};

RenderableState::RenderableState(int n, std::vector<SDL_Color> c) : State(n)
{
    //Set color keys
    colorKeys = c;
    hue = 0;
    ambientColor = 0;
    saturation = 0;
    reflectiveness = 0.5;
    brightness = 0.5;
}

void RenderableState::setHue(unsigned int h)
{
    if(h > 360)
    {
        hue = 360;
    }else{
        hue = h;
    }
}

void RenderableState::setAmbientColor(unsigned int ac)
{
    if(ac > 360)
    {
        ambientColor = 360;
    }else{
        ambientColor = ac;
    }
}

void RenderableState::setSaturation(double s)
{
    if(s > 1)
    {
        saturation = 1;
    }else{
        saturation = s;
    }
}

void RenderableState::setReflectiveness(double r)
{
    if(r < 0)
    {
        reflectiveness = 0;
    }else if(r > 1){
        reflectiveness = 1;
    }else{
        reflectiveness = r;
    }
}

void RenderableState::setBrightness(double b)
{
    if(b > 1)
    {
        brightness = 1;
    }else if(b < 0){
        brightness = 0;
    }else{
        brightness = b;
    }
}

bool RenderableState::generatePalette()
{
    unsigned int numColors = colorKeys.size();
    std::vector<SDL_Color> newPalette;
    unsigned int newColor;

    if(numColors <= 0)
    {
        return false;
    }
    colorMap.clear();

    for(unsigned int i = 0; i < numColors; i++)
    {
        newColor = getColor(hue, ambientColor, reflectiveness, i, numColors);
        newPalette.push_back(hsvToRgb(HSV(newColor, getOffset(1 - saturation, 1, i, numColors), getOffset(1 - brightness, brightness * 2, i, numColors))));
    }

    //Sort colr keys by brightness before creating map
    std::sort(colorKeys.begin(), colorKeys.end(), luminanceSort());

    //Create mapping
    for(int i = 0; i < numColors; i++)
    {
        colorMap.insert(std::pair<SDL_Color,SDL_Color>(colorKeys.at(i), newPalette.at(i)));
    }

    return true;
}

SDL_Texture* RenderableState::getTexture(SDL_Renderer* renderer, TemplateState* temp)
{
    SDL_Color pixelColor;
    SDL_Surface* paintedSurface;
    SDL_Texture* ret;

    //Check if we already created this texture
    std::map<int, SDL_Texture*>::iterator it;
    it = textures.find(temp->getName());
    //If we do return it
    if(it != textures.end())
    {
        return it->second;
    }

    //Create a new texture
    if(temp->getTemplate() == NULL)
    {
        std::cerr<<"Error: Surface is NULL"<<std::endl;
        return NULL;
    }
    paintedSurface = SDL_CreateRGBSurface(0, temp->getTemplate()->w, temp->getTemplate()->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(temp->getTemplate(), NULL, paintedSurface, NULL);
    //Make sure we have generated a color map
    if(colorKeys.size() != colorMap.size())
    {
        generatePalette();
    }

    for(int i = 0; i < paintedSurface->w * paintedSurface->h; i++)
    {
        pixelColor = getPixel(paintedSurface, i);
        if(colorMap.find(pixelColor) != colorMap.end())
        {
            SDL_Color newPixelColor = colorMap.at(pixelColor);
            setPixel(paintedSurface, i, newPixelColor);
        }
    }
    ret = SDL_CreateTextureFromSurface(renderer, paintedSurface);
    SDL_FreeSurface(paintedSurface);

    textures.insert(std::pair<int, SDL_Texture*>(temp->getName(), ret));
    return ret;
}

RenderableState::~RenderableState()
{
    for(auto& texture : textures)
    {
        if(texture.second != NULL)
        {
            SDL_DestroyTexture(texture.second);
        }
    }
    textures.clear();
}
