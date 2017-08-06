#include "SimpleTile.hpp"

enum TileColor
{
    RED,
    GREEN,
    BLUE
};

Colorist getSimpleTileColorist()
{
    Colorist ret = Colorist();

    //Add the color key for our fragment
    SDL_Color colorKey;
    colorKey.r = 155;
    colorKey.g = 173;
    colorKey.b = 183;
    ret.pushColorKey(colorKey);
    colorKey.r = 132;
    colorKey.g = 126;
    colorKey.b = 135;
    ret.pushColorKey(colorKey);
    colorKey.r = 105;
    colorKey.g = 106;
    colorKey.b = 106;
    ret.pushColorKey(colorKey);
    colorKey.r = 63;
    colorKey.g = 63;
    colorKey.b = 116;
    ret.pushColorKey(colorKey);
    colorKey.r = 34;
    colorKey.g = 32;
    colorKey.b = 52;
    ret.pushColorKey(colorKey);

    //The sample will make these in alphabetical order of key name
    Palette color = Palette();
    color.setHue(0);
    color.setAmbientColor(45);
    color.setSaturation(0.2);
    color.setReflectiveness(0.0);
    color.setBrightness(0.4);
    ret.addPalette("brickRed", color);

    color.setHue(135);
    color.setAmbientColor(218);
    ret.addPalette("brickGreen", color);

    color.setHue(260);
    color.setAmbientColor(218);
    ret.addPalette("brickBlue", color);

    return ret;
}

SimpleTile::SimpleTile(SDL_Renderer *renderer)
{
    //Call parent constructor
    Renderable();
    //Load fragment
    Fragment tileFragment = Fragment("resources/fragments/simpleTile.png");
    Template tileTemplate = Template(16, 16);
    tileTemplate.addFragment(tileFragment, 0, 0);
    tileTemplate.scaleTemplate(3);
    //Get colors
    Colorist colorist = getSimpleTileColorist();
    //Create textures
    SDL_Texture *texture = colorist.createTexture(tileTemplate, "brickBlue", renderer);
    addTexture(TileColor::BLUE, texture);
    texture = colorist.createTexture(tileTemplate, "brickRed", renderer);
    addTexture(TileColor::RED, texture);
    texture = colorist.createTexture(tileTemplate, "brickGreen", renderer);
    addTexture(TileColor::GREEN, texture);
    //Clean up
    tileFragment.close();
    tileTemplate.close();
    //Set initial color state
    currentColorState = TileColor::BLUE;
    setCurrentTexture(currentColorState);
}

void SimpleTile::switchColor()
{
    switch(currentColorState)
    {
        case TileColor::RED:
            currentColorState = TileColor::GREEN;
            break;
        case TileColor::GREEN:
            currentColorState = TileColor::BLUE;
            break;
        case TileColor::BLUE:
            currentColorState = TileColor::RED;
            break;
    }
    setCurrentTexture(currentColorState);
}

void SimpleTile::close()
{
    freeAllTextures();
}
