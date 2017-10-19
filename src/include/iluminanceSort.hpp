#ifndef _LUMINANCESORT_HPP_
#define _LUMINANCESORT_HPP_

//Custom compare used to sort colors
struct luminanceSort
{
    inline bool operator()(const SDL_Color& a, const SDL_Color& b)
    {
        return luminance(a) < luminance(b);
    }
};
