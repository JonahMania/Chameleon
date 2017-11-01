#include "../include/Renderable.hpp"

Renderable::Renderable()
{
    renderWidth = 0;
    renderHeight = 0;
    renderPositionX = 0;
    renderPositionY = 0;
}

Renderable::Renderable(unsigned int w, unsigned int h)
{
    renderWidth = w;
    renderHeight = h;
    renderPositionX = 0;
    renderPositionY = 0;
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

std::string Renderable::getId() const
{
    return std::to_string(renderWidth) + "_" +
        std::to_string(renderHeight) + "_";
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

Renderable::~Renderable()
{

}
