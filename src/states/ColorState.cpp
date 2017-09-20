#include "../utils/colorUtils.hpp"
#include "../include/ColorState.hpp"

ColorState::ColorState(int n) : State(n)
{
    hue = 0;
    ambientColor = 0;
    saturation = 0;
    reflectiveness = 0.5;
    brightness = 0.5;
}

void ColorState::setHue(unsigned int h)
{
    if(h > 360)
    {
        hue = 360;
    }else{
        hue = h;
    }
}


void ColorState::setAmbientColor(unsigned int ac)
{
    if(ac > 360)
    {
        ambientColor = 360;
    }else{
        ambientColor = ac;
    }
}

void ColorState::setSaturation(double s)
{
    if(s > 1)
    {
        saturation = 1;
    }else{
        saturation = s;
    }
}

void ColorState::setReflectiveness(double r)
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

void ColorState::setBrightness(double b)
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

std::map<SDL_Color, SDL_Color> ColorState::generatePalette(std::vector<SDL_Color> colorKeys)
{
    unsigned int numColors = colorKeys.size();
    std::vector<SDL_Color> palette;
    std::map<SDL_Color, SDL_Color> colorMap = std::map<SDL_Color, SDL_Color>();
    unsigned int newColor;

    if(numColors <= 0)
    {
        return colorMap;
    }

    for(unsigned int i = 0; i < numColors; i++)
    {
        newColor = getColor(hue, ambientColor, reflectiveness, i, numColors);
        palette.push_back(hsvToRgb(HSV(newColor, getOffset(1 - saturation, 1, i, numColors), getOffset(1 - brightness, brightness * 2, i, numColors))));
    }

    //Sort colr keys by brightness before creating map
    std::sort(colorKeys.begin(), colorKeys.end(), luminanceSort());

    //Create mapping
    for(int i = 0; i < numColors; i++)
    {
        colorMap.insert(std::pair<SDL_Color,SDL_Color>(colorKeys.at(i), palette.at(i)));
    }

    return colorMap;
}

ColorState::~ColorState()
{

}
