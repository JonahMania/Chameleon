#include "Renderable.hpp"

class Object : public Renderable
{
    public:
        bool checkCollision(Object object);
        void setWidth(unsigned int w);
        void setHeight(unsigned int h);
    private:
        SDL_Rect boundingBox;
};
