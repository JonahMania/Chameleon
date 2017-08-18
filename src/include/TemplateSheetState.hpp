#ifndef _TEMPLATESHEETSTATE_HPP_
#define _TEMPLATESHEETSTATE_HPP_

#include <string>
#include <math.h>

#include "TemplateState.hpp"

class TemplateSheetState : public TemplateState
{
    public:
        TemplateSheetState(std::string n, std::string p, unsigned int w, unsigned int h, unsigned int scale = 1);
        unsigned int getNumSprites();
        void setCurrentSprite(unsigned int i);
    private:
        unsigned int numSprites;
        unsigned int numXSprites;
        unsigned int numYSprites;
        unsigned int spriteWidth;
        unsigned int spriteHeight;
};

#endif
