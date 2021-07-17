#include "splashstate.hpp"

#include <cassert>
#include <cmath>

#include "resources.hpp"

Splash::Splash(): State() {
    setName("splash");
}

Splash::~Splash() {}

void Splash::reset() {
    timer = 0.f;

    splashes.push(sf::String(L"CRAZY MIDNIGHT DISPLAY"));
    splashes.push(sf::String(L"presents"));
}

void Splash::update(float delta) {
    timer += delta;
    if (timer > 3.14f) {
        timer = 0.f;
        splashes.pop();
        if (splashes.empty()) {
            context->setState("menu");
        }
    }
}

void Splash::draw(sf::RenderWindow* window) {
    sf::Text* text = Resources::getInstance().getGameText();

    text->setCharacterSize(26);
    text->setString(splashes.front());

    sf::FloatRect box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));

    text->setPosition(sf::Vector2f(window->getSize().x/2, window->getSize().y/2 - 100));

    sf::Color c = text->getFillColor();
    c.a = sf::Uint8(255.f * std::abs(std::sin(timer)));
    text->setFillColor(c);

    window->clear(bg);
    window->draw(*text);
}

void Splash::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Enter:
            context->setState("menu");
            break;
        default:
            break;
        }
    }
}
