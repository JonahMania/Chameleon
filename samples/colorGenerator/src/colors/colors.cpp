#include "colors.hpp"

Colorist getColorist()
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

    Palette color = Palette();
    color.setBaseColor(SDL_Color({r:100,g:60,b:200}));
    color.setHighlightColor(SDL_Color({r:100,g:250,b:250}));
    color.setAmbientColor(SDL_Color({r:10,g:0,b:200}));
    color.setReflectivity(0.5);
    color.setIllumination(0.5);
    color.setHighlightMultiplyer(1);
    ret.addPalette("color0", color);
    color.setIllumination(0.75);
    ret.addPalette("color1", color);
    color.setIllumination(1);
    ret.addPalette("color2", color);
    color.setIllumination(1.25);
    ret.addPalette("color3", color);
    color.setIllumination(1.5);
    ret.addPalette("color4", color);
    color.setIllumination(1.75);
    ret.addPalette("color5", color);
    color.setIllumination(2);
    ret.addPalette("color6", color);
    color.setIllumination(2.25);
    ret.addPalette("color7", color);
    color.setIllumination(2.50);
    ret.addPalette("color8", color);
    color.setIllumination(2.75);
    ret.addPalette("color9", color);
    color.setIllumination(3);
    ret.addPalette("color10", color);
    color.setIllumination(3.25);
    ret.addPalette("color11", color);

    return ret;
}
