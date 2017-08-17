#include "../include/State.hpp"

State::State(std::string n)
{
    name = n;
}

std::string State::getName()
{
    return name;
}
