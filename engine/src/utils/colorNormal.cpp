#include "colorNormal.hpp"

ColorNormal::ColorNormal()
{
    r = 0;
    g = 0;
    b = 0;
}

ColorNormal::ColorNormal(SDL_Color color)
{
    r = (double)color.r / 255;
    g = (double)color.g / 255;
    b = (double)color.b / 255;
}

SDL_Color ColorNormal::toSDL_Color()
{
    SDL_Color ret;
    ret.r = (Uint8)(this->r * 255);
    ret.g = (Uint8)(this->g * 255);
    ret.b = (Uint8)(this->b * 255);
    ret.a = 0;
    return ret;
}

ColorNormal ColorNormal::operator*(ColorNormal color)
{
    ColorNormal ret;
    ret.r = this->r * color.r;
    ret.g = this->g * color.g;
    ret.b = this->b * color.b;
    return ret;
}

ColorNormal ColorNormal::operator*(double scale)
{
    ColorNormal ret;
    ret.r = this->r * scale;
    ret.g = this->g * scale;
    ret.b = this->b * scale;
    return ret;
}

ColorNormal ColorNormal::operator+(ColorNormal color)
{
    ColorNormal ret;
    ret.r = this->r + color.r;
    ret.g = this->g + color.g;
    ret.b = this->b + color.b;
    return ret;
}
