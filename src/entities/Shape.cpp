#include "../include/Shape.hpp"

Shape::Shape() : Renderable()
{
    points = std::vector<SDL_Point>();
    color = SDL_Color();
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
}

Shape::Shape(unsigned int w, unsigned int h) : Renderable(w, h)
{
    points = std::vector<SDL_Point>();
    color = SDL_Color();
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
}

void Shape::addPoint(unsigned int x, unsigned int y)
{
    SDL_Point point;
    point.x = x;
    point.y = y;

    if(point.x > getRenderWidth())
    {
        setDimensions(point.x, getRenderHeight());
    }
    if(point.y > getRenderHeight())
    {
        setDimensions(getRenderHeight(), point.y);
    }

    points.push_back(point);
}

void Shape::setColor(SDL_Color c)
{
    color = c;
}

std::string Shape::getId() const
{
    std::string id = Renderable::getId();
    for(auto &point : points)
    {
        id += ":" + std::to_string(point.x) + "," + std::to_string(point.y);
    }
    return id;
}

std::vector<SDL_Point> Shape::getPoints()
{
    return points;
}

unsigned int Shape::getNumPoints()
{
    return points.size();
}

SDL_Color Shape::getColor()
{
    return color;
}
