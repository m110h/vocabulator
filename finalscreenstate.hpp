#ifndef _FINALSCREEN_STATE_H_
#define _FINALSCREEN_STATE_H_

#include "abstractstate.hpp"

#include <queue>

class FinalScreen: public State
{
public:
    FinalScreen();
    ~FinalScreen();

    void update(float delta);
    void draw(sf::RenderWindow* window);
    void processEvent(const sf::Event& event);
    void reset();

private:
    float timer;

    std::queue<sf::String> messages;
};

#endif // _FINALSCREEN_STATE_H_
