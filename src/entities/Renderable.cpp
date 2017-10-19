#include "../include/Renderable.hpp"

Renderable::Renderable(std::string p, unsigned int s)
{
    path = p;
    scale = s;
    //If width and height are set to 0 then the
    //renderer will use the whole sheet
    renderWidth = 0;
    renderHeight = 0;
    renderPositionX = 0;
    renderPositionY = 0;
    sheetPositionX = 0;
    sheetPositionY = 0;
}

Renderable::Renderable(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s)
{
    path = p;
    scale = s;
    renderWidth = w;
    renderHeight = h;
    renderPositionX = 0;
    renderPositionY = 0;
    sheetPositionX = sx;
    sheetPositionY = sy;
}

void Renderable::setImagePath(std::string p)
{
    path = p;
}

void Renderable::setDimensions(unsigned int w, unsigned int h)
{
    renderWidth = w;
    renderHeight = h;
}

void Renderable::setRenderPosition(int x, int y)
{
    renderPositionX = x;
    renderPositionY = y;
}

void Renderable::setSheetPosition(unsigned int x, unsigned int y)
{
    sheetPositionX = x;
    sheetPositionY = y;
}

void Renderable::setScale(unsigned int s)
{
    scale = s;
}

std::string Renderable::getPath() const
{
    return path;
}

unsigned int Renderable::getRenderWidth() const
{
    return renderWidth;
}

unsigned int Renderable::getRenderHeight() const
{
    return renderHeight;
}

int Renderable::getRenderPositionX() const
{
    return renderPositionX;
}

int Renderable::getRenderPositionY() const
{
    return renderPositionY;
}

unsigned int Renderable::getSheetPositionX() const
{
    return sheetPositionX;
}

unsigned int Renderable::getSheetPositionY() const
{
    return sheetPositionY;
}

unsigned int Renderable::getScale() const
{
    return scale;
}

Renderable::~Renderable()
{

}

bool Renderable::operator==(const Renderable &other) const
{
    return path == other.path && scale == other.scale &&
           renderWidth == other.renderWidth && renderHeight == other.renderHeight &&
           scale == other.scale;
}


std::size_t std::hash<Renderable>::operator()(const Renderable& r) const
{
    //Hash each field and combine with each other
    size_t hash = 17;
    hash = hash * 31 + std::hash<std::string>{}(r.getPath());
    hash = hash * 31 + std::hash<unsigned int>{}(r.getRenderWidth());
    hash = hash * 31 + std::hash<unsigned int>{}(r.getRenderHeight());
    hash = hash * 31 + std::hash<unsigned int>{}(r.getSheetPositionX());
    hash = hash * 31 + std::hash<unsigned int>{}(r.getSheetPositionY());
    hash = hash * 31 + std::hash<unsigned int>{}(r.getScale());
    return hash;
}
