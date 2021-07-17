#include "statisticsstate.hpp"
#include "gamestatistics.hpp"

#include "resources.hpp"

StatisticsState::StatisticsState() {
    setName("statistics");
}

void StatisticsState::reset() {
}

StatisticsState::~StatisticsState() {
}

void StatisticsState::update(float delta) {
}

void StatisticsState::draw(sf::RenderWindow* window) {
    GameStatistics* statistics = Resources::getInstance().getStatistics();
    sf::Text* text = Resources::getInstance().getGameText();

    sf::FloatRect box;

    window->clear(sf::Color(0, 26, 35));

    text->setCharacterSize(28);

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Your statistics"));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, 30.f));
    window->draw(*text);

    float pos = 180.f;
    float delta = 30.f;

    text->setCharacterSize(22);

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Mode :"));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, pos));
    window->draw(*text);

    text->setFillColor(sf::Color(171, 64, 19));
    text->setString(Resources::getInstance().getSettings()->getMode());
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(0.f, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f + 20.f, pos));
    window->draw(*text);

    pos += delta;

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Scores :"));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, pos));
    window->draw(*text);

    text->setFillColor(sf::Color(50, 200, 50));
    text->setString(sf::String( std::to_string(statistics->getScores()) ));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(0.f, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f + 20.f, pos));
    window->draw(*text);

    pos += delta;

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Fails :"));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, pos));
    window->draw(*text);

    text->setFillColor(sf::Color(200, 20, 20));
    text->setString( sf::String( std::to_string(statistics->getFails()) ));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(0.f, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f + 20.f, pos));
    window->draw(*text);

    pos += delta;

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Skips :"));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, pos));
    window->draw(*text);

    text->setFillColor(sf::Color(204, 183, 22));
    text->setString(sf::String(std::to_string(statistics->getSkips())));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(0.f, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f + 20.f, pos));
    window->draw(*text);

    pos += delta;

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Accuracy :"));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, pos));
    window->draw(*text);

    text->setFillColor(sf::Color(37, 136, 239));
    text->setString(sf::String(std::to_string(statistics->getAccuracy())));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(0.f, 0.f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f + 20.f, pos));
    window->draw(*text);

    text->setCharacterSize(16);

    text->setFillColor(sf::Color::White);
    text->setString(sf::String(L"Enter - replay, Esc - back to menu"));
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, window->getSize().y - 30.f));
    window->draw(*text);
}

void StatisticsState::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            context->setState("menu");
            break;
        case sf::Keyboard::Enter:
            context->setState("game");
            break;
        default:
            break;
        }
    }
}

