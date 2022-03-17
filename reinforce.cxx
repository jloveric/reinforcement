module;

#include <iostream>
#include <utility>

export module reinforce;

export void func();

void func()
{
    std::cout << "hello, world!\n";
}

class Action
{
    Action()
    {
    }
};

class State
{
    State()
    {
    }
};

template <class ACTION, class STATE, class REWARD>
class Q
{
    Q(ACTION a, STATE s, REWARD r) : action(std::move(a)), state(std::move(s)), reward(std::move(r))
    {
    }

private:
    ACTION action;
    STATE state;
    REWARD reward;
};