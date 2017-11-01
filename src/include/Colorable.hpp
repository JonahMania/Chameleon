#ifndef _COLORABLE_HPP_
#define _COLORABLE_HPP_

#include "Sprite.hpp"

class Colorable : public Sprite
{
    public:
        Colorable(std::string p, unsigned int s = 1);
        Colorable(std::string p, unsigned int w, unsigned int h, unsigned int sx, unsigned int sy, unsigned int s = 1);
        void setHue(double h);
        void setStep(double s);
        void setSaturation(double s);
        void setReflectiveness(double r);
        void setBrightness(double b);
        std::string getId() const;
        double getHue() const;
        double getStep() const;
        double getSaturation() const;
        double getReflectiveness() const;
        double getBrightness() const;
        virtual ~Colorable();
    private:
        double hue;
        double step;
        double saturation;
        double reflectiveness;
        double brightness;
};

#endif
