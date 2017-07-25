#include "colorUtils.hpp"

double luminance(SDL_Color color)
{
    //Digital weight
    return 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
}
