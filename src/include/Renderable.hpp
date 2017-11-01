#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include <string>
#include <map>

class Renderable
{
    public:
        Renderable();
        Renderable(unsigned int w, unsigned int h);
        void setDimensions(unsigned int w, unsigned int h);
        void setRenderPosition(int x, int y);
        virtual std::string getId() const;
        unsigned int getRenderWidth() const;
        unsigned int getRenderHeight() const;
        int getRenderPositionX() const;
        int getRenderPositionY() const;
        virtual ~Renderable();
    private:
        unsigned int renderWidth;
        unsigned int renderHeight;
        int renderPositionX;
        int renderPositionY;
};

#endif
