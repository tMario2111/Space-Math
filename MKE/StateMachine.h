#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stack>
#include <memory>
#include <string>

#include "State.h"

namespace mke
{
class StateMachine
{
public:
    void push(std::unique_ptr<mke::State> state);
    void pop();
    void popStatesUntil(std::string name);
    State& top();
    bool states_just_changed = 0;
    unsigned int size();
private:
    std::stack<std::unique_ptr<mke::State>> states;
};
}

#endif
