#include "../include/TemplateSheetState.hpp"

TemplateSheetState::TemplateSheetState(int n, std::string p, unsigned int w, unsigned int h, unsigned int scale) : TemplateState(n, p, scale)
{
    spriteWidth = w * scale;
    spriteHeight = h * scale;
    if(surface == NULL)
    {
        return;
    }

    numXSprites = floor((double)surface->w / (double)spriteWidth);
    numYSprites = floor((double)surface->h / (double)spriteHeight);
    numSprites =  numXSprites * numYSprites;

    bounds.x = 0;
    bounds.y = 0;
    bounds.w = spriteWidth;
    bounds.h = spriteHeight;
}

unsigned int TemplateSheetState::getNumSprites()
{
    return numSprites;
}

void TemplateSheetState::setCurrentSprite(unsigned int i)
{
    unsigned int y = floor(i / numXSprites);
    unsigned int x = i - (y * numXSprites);
    bounds.x = x * spriteWidth;
    bounds.y = y * spriteHeight;
}
