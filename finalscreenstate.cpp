#include "finalscreenstate.hpp"
#include "resources.hpp"

#include <cmath>

FinalScreen::FinalScreen(): State() {
    setName("finalscreen");
}
FinalScreen::~FinalScreen() {}

void FinalScreen::reset() {
    timer = 0.f;

    messages.push(sf::String(L"Have a nice day"));
    messages.push(sf::String(L"Bye!"));
}

void FinalScreen::update(float delta) {
    timer += delta;
    if (timer > 3.14f * 0.5f) {
        timer = 0.f;
        messages.pop();
        if (messages.empty()) {
            context->setState("exit");
        }
    }
}

void FinalScreen::draw(sf::RenderWindow* window) {
    sf::Text* text = Resources::getInstance().getGameText();

    text->setCharacterSize(26);
    text->setString(messages.front());

    sf::FloatRect box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));

    text->setPosition(sf::Vector2f(window->getSize().x/2, window->getSize().y/2 - 100));

    window->clear(sf::Color(0, 0, 0));
    window->draw(*text);
}

void FinalScreen::processEvent(const sf::Event& event) {
    return;
}
