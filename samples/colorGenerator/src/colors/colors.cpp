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

    //The sample will make these in alphabetical order of key name
    Palette color = Palette();
    color.setHue(0);
    color.setAmbientColor(45);
    color.setSaturation(0.8);
    color.setReflectiveness(0);

    color.setBrightness(0.00);
    ret.addPalette("bcolor0", color);
    color.setBrightness(0.10);
    ret.addPalette("bcolor1", color);
    color.setBrightness(0.20);
    ret.addPalette("bcolor2", color);
    color.setBrightness(0.30);
    ret.addPalette("bcolor3", color);
    color.setBrightness(0.40);
    ret.addPalette("bcolor4", color);
    color.setBrightness(0.50);
    ret.addPalette("bcolor5", color);
    color.setBrightness(0.60);
    ret.addPalette("bcolor6", color);
    color.setBrightness(0.70);
    ret.addPalette("bcolor7", color);
    color.setBrightness(0.80);
    ret.addPalette("bcolor8", color);
    color.setBrightness(0.90);
    ret.addPalette("bcolor9", color);
    color.setBrightness(0.6);

    color.setReflectiveness(0.10);
    ret.addPalette("rcolor0", color);
    color.setReflectiveness(0.20);
    ret.addPalette("rcolor1", color);
    color.setReflectiveness(0.30);
    ret.addPalette("rcolor2", color);
    color.setReflectiveness(0.40);
    ret.addPalette("rcolor3", color);
    color.setReflectiveness(0.50);
    ret.addPalette("rcolor4", color);
    color.setReflectiveness(0.60);
    ret.addPalette("rcolor5", color);
    color.setReflectiveness(0.70);
    ret.addPalette("rcolor6", color);
    color.setReflectiveness(0.80);
    ret.addPalette("rcolor7", color);
    color.setReflectiveness(0.90);
    ret.addPalette("rcolor8", color);
    color.setReflectiveness(1.0);
    ret.addPalette("rcolor9", color);
    color.setReflectiveness(0.5);
    color.setBrightness(0.4);

    color.setSaturation(0.1);
    ret.addPalette("scolor0", color);
    color.setSaturation(0.2);
    ret.addPalette("scolor1", color);
    color.setSaturation(0.3);
    ret.addPalette("scolor2", color);
    color.setSaturation(0.4);
    ret.addPalette("scolor3", color);
    color.setSaturation(0.5);
    ret.addPalette("scolor4", color);
    color.setSaturation(0.6);
    ret.addPalette("scolor5", color);
    color.setSaturation(0.7);
    ret.addPalette("scolor6", color);
    color.setSaturation(0.8);
    ret.addPalette("scolor7", color);
    color.setSaturation(0.9);
    ret.addPalette("scolor8", color);
    color.setSaturation(1);
    ret.addPalette("scolor9", color);

    return ret;
}
