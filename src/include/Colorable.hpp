#ifndef _COLORABLE_HPP_
#define _COLORABLE_HPP_

#include "Renderable.hpp"

class Colorable : public Renderable
{
public:
    Colorable(std::string p, unsigned int s = 1);
    Colorable(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s = 1);
    void setHue(unsigned int h);
    void setAmbientColor(unsigned int ac);
    void setSaturation(double s);
    void setReflectiveness(double r);
    void setBrightness(double b);
    unsigned int getHue() const;
    unsigned int getAmbientColor() const;
    double getSaturation() const;
    double getReflectiveness() const;
    double getBrightness() const;
    virtual ~Colorable();
private:
    unsigned int hue;
    unsigned int ambientColor;
    double saturation;
    double reflectiveness;
    double brightness;
};

//Specialized hash function for Colorable
namespace std
{
    template <>
    struct hash<Colorable>
    {
        std::size_t operator()(const Colorable& colorable) const;
    };
}

#endif
