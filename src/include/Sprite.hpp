#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include "Renderable.hpp"

class Sprite : public Renderable
{
    public:
        //Creates the renderable with a full image
        Sprite(std::string p, unsigned int s = 1);
        Sprite(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s = 1);
        void setImagePath(std::string p);
        void setSheetPosition(unsigned int x, unsigned int y);
        void setScale(unsigned int s);
        std::string getId() const;
        std::string getPath() const;
        unsigned int getSheetPositionX() const;
        unsigned int getSheetPositionY() const;
        unsigned int getScale() const;
        virtual ~Sprite();
    private:
        std::string path;
        //Position of the sprite in the sprite sheet that we want to render
        unsigned int sheetPositionX;
        unsigned int sheetPositionY;
        unsigned int scale;
};

#endif
