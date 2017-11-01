#include "../include/Sprite.hpp"

Sprite::Sprite(std::string p, unsigned int s) : Renderable()
{
    path = p;
    scale = s;
    sheetPositionX = 0;
    sheetPositionY = 0;
}

Sprite::Sprite(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s) : Renderable(w, h)
{
    path = p;
    scale = s;
    sheetPositionX = sx;
    sheetPositionY = sy;
}

void Sprite::setImagePath(std::string p)
{
    path = p;
}

void Sprite::setSheetPosition(unsigned int x, unsigned int y)
{
    sheetPositionX = x;
    sheetPositionY = y;
}

void Sprite::setScale(unsigned int s)
{
    scale = s;
}

std::string Sprite::getId() const
{
    return path + ":" +
        std::to_string(sheetPositionX) + ":" +
        std::to_string(sheetPositionY) + ":" +
        Renderable::getId() + ":" +
        std::to_string(scale);
}

std::string Sprite::getPath() const
{
    return path;
}

unsigned int Sprite::getSheetPositionX() const
{
    return sheetPositionX;
}

unsigned int Sprite::getSheetPositionY() const
{
    return sheetPositionY;
}

unsigned int Sprite::getScale() const
{
    return scale;
}

Sprite::~Sprite()
{

}
