#include "StateMachine.h"

namespace mke
{
void StateMachine::push(std::unique_ptr<mke::State> state)
{
    states.push(std::move(state));
}
void StateMachine::pop()
{
    states.pop();
}
void StateMachine::popStatesUntil(std::string name)
{
    while (states.size() && name.compare(states.top().get()->name) != 0)
        states.pop();
}
void StateMachine::popStatesUntilAndPush(std::string name, std::unique_ptr<mke::State> state)
{
    popStatesUntil(name);
    push(std::move(state));
}
State& StateMachine::top()
{
    return *states.top().get();
}
unsigned int StateMachine::size()
{
    return states.size();
}
}
