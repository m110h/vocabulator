#include "gamecontext.hpp"
#include "resources.hpp"
#include "log.hpp"

#include <cassert>

GameContext::GameContext(): Context(), currentState(nullptr), window(nullptr) {
    PLOG_DEBUG << "GameContext constructor";

    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "VOCABULATOR", sf::Style::Titlebar | sf::Style::Close);
    window->setVerticalSyncEnabled(true);

    Resources::getInstance().load();
}

GameContext::~GameContext() {
    PLOG_DEBUG << "GameContext destructor";

    currentState = nullptr;

    for (State* x: states)
    {
        if (x)
            delete x;
    }
    states.clear();

    Resources::getInstance().free();

    if (window) {
        delete window;
    }
}

void GameContext::run()
{
    sf::Clock clock;
    assert(window && "runtime error: pointer to window is null");

    PLOG_DEBUG << "start main loop";

    float deltaTime = 0.f;
    float fps = 30.f;

    while (window->isOpen()) {
        assert(currentState && "logical error: current state is null");

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                break;
            }

            currentState->processEvent(event);
        }

        deltaTime += clock.restart().asSeconds();
        if (deltaTime < (1.f/fps)) {
            continue;
        }

        currentState->update(deltaTime);
        deltaTime = 0.f;

        if (!window->isOpen()) {
            break;
        }

        currentState->draw(window);

        window->display();
    }

    PLOG_DEBUG << "stop main loop";
}

bool GameContext::setState(const sf::String& name) {
    assert(window && "runtime error: pointer to window is null");

    PLOG_DEBUG << "change state to " << name.toAnsiString();

    if (name == "exit") {
        window->close();
        return true;
    }

    for (size_t i=0; i<states.size(); i++)
        if (states[i]->getName() == name) {
            currentState = states[i];
            currentState->reset();
            return true;
        }

    PLOG_DEBUG << "logical error: try to set unknown state!";

    return false;
}

void GameContext::addState(State* state) {
    assert(state && "runtime error: try to add nullptr state");

    PLOG_DEBUG << "add state " << state->getName().toAnsiString();

    state->setContext(this);
    states.push_back(state);
}
