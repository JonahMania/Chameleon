#ifndef _MASK_HPP_
#define _MASK_HPP_

#include "Renderable.hpp"

class Mask : public Renderable
{
    public:
        //Will create a mask from a image where all non transparent pixels are 1
        Mask(std::string path);
        // Mask(points*, int numPoints);
        std::string getId() const;
    private:
};

#endif
