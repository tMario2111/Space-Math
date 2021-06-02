#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <string>

namespace mke
{
class State
{
public:
    std::string name;
    virtual void update() = 0;
    virtual void render() = 0;
};
}

#endif
