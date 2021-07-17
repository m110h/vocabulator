#include "abstractstate.hpp"

State::State(): context(nullptr), name(""), bg(0, 26, 35) {}

State::~State() {}

void State::setContext(Context* context) {
    this->context = context;
}

void State::setName(const sf::String& name) {
    this->name = name;
}

const sf::String& State::getName() {
    return name;
}


Context::Context() {}
Context::~Context() {}
