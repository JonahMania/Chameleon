#include "../include/Colorable.hpp"

Colorable::Colorable(std::string p, unsigned int s) : Renderable(p, s)
{
    hue = 0;
    ambientColor = 0;
    saturation = 0;
    reflectiveness = 0.5;
    brightness = 0.5;
}

Colorable::Colorable(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s) : Renderable(p, w, h, sx, sy, s)
{
    hue = 0;
    ambientColor = 0;
    saturation = 0;
    reflectiveness = 0.5;
    brightness = 0.5;
}

void Colorable::setHue(unsigned int h)
{
    if(h > 360)
    {
        hue = 360;
    }else{
        hue = h;
    }
}

void Colorable::setAmbientColor(unsigned int ac)
{
    if(ac > 360)
    {
        ambientColor = 360;
    }else{
        ambientColor = ac;
    }
}

void Colorable::setSaturation(double s)
{
    if(s > 1)
    {
        saturation = 1;
    }else{
        saturation = s;
    }
}

void Colorable::setReflectiveness(double r)
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

void Colorable::setBrightness(double b)
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

unsigned int Colorable::getHue() const
{
    return hue;
}

unsigned int Colorable::getAmbientColor() const
{
    return ambientColor;
}

double Colorable::getSaturation() const
{
    return saturation;
}

double Colorable::getReflectiveness() const
{
    return reflectiveness;
}

double Colorable::getBrightness() const
{
    return brightness;
}

Colorable::~Colorable()
{

}

std::size_t std::hash<Colorable>::operator()(const Colorable& c) const
{
    //Hash each field and combine with each other
    size_t hash = 17;
    hash = hash * 31 + std::hash<std::string>{}(c.getPath());
    hash = hash * 31 + std::hash<unsigned int>{}(c.getRenderWidth());
    hash = hash * 31 + std::hash<unsigned int>{}(c.getRenderHeight());
    hash = hash * 31 + std::hash<unsigned int>{}(c.getSheetPositionX());
    hash = hash * 31 + std::hash<unsigned int>{}(c.getSheetPositionY());
    hash = hash * 31 + std::hash<unsigned int>{}(c.getScale());
    hash = hash * 31 + std::hash<unsigned int>{}(c.getHue());
    hash = hash * 31 + std::hash<unsigned int>{}(c.getAmbientColor());
    hash = hash * 31 + std::hash<double>{}(c.getSaturation());
    hash = hash * 31 + std::hash<double>{}(c.getReflectiveness());
    hash = hash * 31 + std::hash<double>{}(c.getBrightness());
    return hash;
}
