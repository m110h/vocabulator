#ifndef _STATISTICS_STATE_H_
#define _STATISTICS_STATE_H_

#include "abstractstate.hpp"

class StatisticsState: public State {
public:
    StatisticsState();
    ~StatisticsState();

    void update(float delta);
    void draw(sf::RenderWindow* window);
    void processEvent(const sf::Event& event);

    void reset();
};

#endif // _STATISTICS_STATE_H_
