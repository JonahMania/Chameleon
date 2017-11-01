#ifndef _MASK_HPP_
#define _MASK_HPP_

#include <SDL.h>
#include <vector>

#include "Renderable.hpp"

class Shape : public Renderable
{
    public:
        //Will create a mask between all points in the mask
        Shape();
        Shape(unsigned int w, unsigned int h);
        void addPoint(unsigned int x, unsigned int y);
        void setColor(SDL_Color c);
        std::string getId() const;
        std::vector<SDL_Point> getPoints();
        unsigned int getNumPoints();
        SDL_Color getColor();
    private:
        std::vector<SDL_Point> points;
        SDL_Color color;
};

#endif
