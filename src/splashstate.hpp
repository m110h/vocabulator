#ifndef _SPLASH_STATE_H_
#define _SPLASH_STATE_H_

#include "abstractstate.hpp"

#include <queue>

class Splash: public State
{
public:
    Splash();
    ~Splash();

    void update(float delta);
    void draw(sf::RenderWindow* window);
    void processEvent(const sf::Event& event);
    void reset();

private:
    float timer;

    std::queue<sf::String> splashes;
};

#endif // _SPLASH_STATE_H_
