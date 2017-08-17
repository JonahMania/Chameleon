#ifndef _STATEMACHINE_HPP_
#define _STATEMACHINE_HPP_

#include <map>
#include <string>
#include <iostream>

#include "State.hpp"

template<typename T> class StateMachine
{
    public:
        static_assert(std::is_base_of<State, T>::value, "StateMachine type must derive from State");
        void setCurrentState(std::string stateName);
        void addState(T* state);
        void freeState(std::string stateName);
        void freeAllStates();
        T* currentState;
    private:
        std::map<std::string, T*> states;
};

template<typename T>
void StateMachine<T>::setCurrentState(std::string stateName)
{
    typename std::map<std::string,T*>::iterator it;

    it = states.find(stateName);
    if(it != states.end())
    {
        currentState = it->second;
    }
}

template<typename T>
void StateMachine<T>::addState(T* state)
{
    if(!states.insert(std::pair<std::string,T*>(state->getName(),state)).second)
    {
      std::cerr<<"Error: State with name: '"<<state->getName()<<"' already exists in entity"<<std::endl;
    }
}

template<typename T>
void StateMachine<T>::freeState(std::string stateName)
{
    typename std::map<std::string,T*>::iterator it;

    it = states.find(stateName);
    if(it != states.end())
    {
        if(it->second != NULL)
        {
            delete it->second;
        }
        states.erase(it);
    }
}

template<typename T>
void StateMachine<T>::freeAllStates()
{
    for(auto& state : states)
    {
        if(state.second != NULL)
        {
            delete state.second;
        }
    }
    states.clear();
}

#endif