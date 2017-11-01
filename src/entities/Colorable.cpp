#include "../include/Colorable.hpp"

Colorable::Colorable(std::string p, unsigned int s) : Sprite(p, s)
{
    hue = 0;
    step = 0;
    saturation = 0.5;
    reflectiveness = 0.5;
    brightness = 0.5;
}

Colorable::Colorable(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s) : Sprite(p, w, h, sx, sy, s)
{
    hue = 0;
    step = 0;
    saturation = 0.5;
    reflectiveness = 0.5;
    brightness = 0.5;
}

void Colorable::setHue(double h)
{
    if(h > 360)
    {
        hue = 360;
    }else{
        hue = h;
    }
}

void Colorable::setStep(double s)
{
    if(s > 360)
    {
        step = 360;
    }else{
        step = s;
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

std::string Colorable::getId() const
{
    return Sprite::getId() + "_" +
        std::to_string(hue) + "_" +
        std::to_string(step) + "_" +
        std::to_string(saturation) + "_" +
        std::to_string(reflectiveness) + "_" +
        std::to_string(brightness);
}


double Colorable::getHue() const
{
    return hue;
}

double Colorable::getStep() const
{
    return step;
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
