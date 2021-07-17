#ifndef _ABSTRACT_STATE_H_
#define _ABSTRACT_STATE_H_

#include <SFML/Graphics.hpp>

class Context;

class State
{
public:
    State();
    virtual ~State();

    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void processEvent(const sf::Event& event) = 0;
    virtual void reset() = 0;

    void setContext(Context* context);

    const sf::String& getName();

protected:
    void setName(const sf::String& name);

protected:
    Context* context;
    sf::String name;
    sf::Color bg;
};

class Context
{
public:
    Context();
    virtual ~Context();

    virtual void run() = 0;
    virtual bool setState(const sf::String& name) = 0;
    virtual void addState(State* state) = 0;
};

#endif // _ABSTRACT_STATE_H_
