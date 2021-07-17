#ifndef _GAMECONTEXT_H_
#define _GAMECONTEXT_H_

#include "abstractstate.hpp"

#include <vector>

/*
*/

class GameContext: public Context
{
public:
    GameContext();
    ~GameContext();

    void run() override;

    bool setState(const sf::String& name) override;
    void addState(State* state) override;

    // todo: it can contain global resources like config, settings, etc.

private:
    State* currentState;
    sf::RenderWindow* window;

    std::vector<State*> states;
};

#endif // _GAMECONTEXT_H_
