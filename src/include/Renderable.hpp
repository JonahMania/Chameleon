#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include <string>
#include <map>

class Renderable
{
    public:
        //Creates the renderable with a full image
        Renderable(std::string p, unsigned int s = 1);
        /********************************************************
        * Creates the renderable with a specific tile           *
        * |--------------| Assumes all tiles are of the same    *
        * |  0 |  1 |  2 | width and height                     *
        * |--------------|                                      *
        * |  3 |  4 |  5 | i indicates the position of the tile *
        * |--------------| in the sprite sheet                  *
        ********************************************************/
        Renderable(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s = 1);
        void setImagePath(std::string p);
        void setDimensions(unsigned int w, unsigned int h);
        void setRenderPosition(int x, int y);
        void setSheetPosition(unsigned int x, unsigned int y);
        void setScale(unsigned int s);
        std::string getPath() const;
        unsigned int getRenderWidth() const;
        unsigned int getRenderHeight() const;
        int getRenderPositionX() const;
        int getRenderPositionY() const;
        unsigned int getSheetPositionX() const;
        unsigned int getSheetPositionY() const;
        unsigned int getScale() const;
        bool operator==(const Renderable &other) const;
        virtual ~Renderable();
    private:
        std::string path;
        unsigned int renderWidth;
        unsigned int renderHeight;
        int renderPositionX;
        int renderPositionY;
        //Position of the sprite in the sprite sheet that we want to render
        unsigned int sheetPositionX;
        unsigned int sheetPositionY;
        unsigned int scale;
};

//Specialized hash function for Renderable
namespace std
{
    template <>
    struct hash<Renderable>
    {
        std::size_t operator()(const Renderable& rederable) const;
    };
}


#endif
