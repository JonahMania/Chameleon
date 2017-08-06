#include "../lib/engine/engine.hpp"

class SimpleTile : public Object
{
    public:
        SimpleTile(SDL_Renderer *renderer);
        void switchColor();
        void close();
    private:
        int currentColorState;
};
