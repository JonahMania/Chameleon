#ifndef _STATE_HPP_
#define _STATE_HPP_

#include <string>

class State
{
    public:
        State(std::string n);
        std::string getName();
    private:
        std::string name;
};

#endif
