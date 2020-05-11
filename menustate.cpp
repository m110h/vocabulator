#include "menustate.hpp"

#include <cassert>

#include "resources.hpp"

void Control::draw(sf::RenderWindow* window, sf::Vector2f pos) {
    sf::FloatRect box;

    sf::Text* text = Resources::getInstance().getGameText();

    if (isFocused) {
        text->setFillColor(sf::Color(50, 200, 50));
        text->setString('[' + name + ']');
    }
    else {
        text->setFillColor(sf::Color::White);
        text->setString(name);
    }

    text->setCharacterSize(30);
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));
    text->setPosition(pos);

    window->draw(*text);

    text->setCharacterSize(22);
    text->setFillColor(sf::Color::White);
    text->setString(getParam());
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));
    pos.y += box.height + 15.f;
    text->setPosition(pos);

    window->draw(*text);
}


Menu::Menu(): State() {
    setName("menu");

    libconfig::Config* cfg = Resources::getInstance().getConfig();
    const libconfig::Setting& root = cfg->getRoot();

    const libconfig::Setting &options = root["game"];

    for(int i=0; i<options.getLength(); ++i) {
        Control ctrl;

        const libconfig::Setting &option = options[i];
        ctrl.setName(option.getName());

        const libconfig::Setting &params = root["game"][option.getName()];
        for (int j=0; j<params.getLength(); ++j) {
            const libconfig::Setting &param = params[j];

            std::string value;
            if(!(param.lookupValue("name", value)))
                continue;

            ctrl.addParam(value);
        }

        ctrl.reset();
        controls.push_back(ctrl);
    }

    reset();
}

Menu::~Menu() {
    controls.clear();
}

void Menu::reset() {
    if (controls.size() > 0) {
        index = 0;
        controls[index].onFocus();
    }
    else {
        index = -1;
    }
}

void Menu::update(float delta) {}

void Menu::draw(sf::RenderWindow* window) {
    window->clear(sf::Color(0, 0, 0));

    sf::Text* text = Resources::getInstance().getGameText();

    text->setFillColor(sf::Color::White);
    text->setCharacterSize(40);
    text->setString(L"VOCABULATOR");
    sf::FloatRect box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, 70.f));

    window->draw(*text);

    sf::Vector2f pos(window->getSize().x*0.5f, 200.f);
    for (size_t i=0; i<controls.size(); i++) {
        controls[i].draw(window, pos);
        pos.y += 60.f;
    }

    text = Resources::getInstance().getGameText();

    text->setFillColor(sf::Color::White);
    text->setCharacterSize(16);
    text->setString(L"Esc - exit, Enter - begin the game");
    box = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));
    text->setPosition(sf::Vector2f(window->getSize().x*0.5f, window->getSize().y-box.height-30.f));

    window->draw(*text);
}

void Menu::saveSettings() {
    GameSettings* settings = Resources::getInstance().getSettings();

    for (size_t i=0; i<controls.size(); i++) {
        if (controls[i].getName() == "Type")
            settings->setType(controls[i].getParam());
        if (controls[i].getName() == "Mode")
            settings->setMode(controls[i].getParam());
        if (controls[i].getName() == "Sound")
            settings->setSound(controls[i].getParam());
        if (controls[i].getName() == "Dictionary")
            settings->setDictionary(controls[i].getParam());
    }
}

void Menu::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            context->setState("finalscreen");
            break;
        case sf::Keyboard::Enter:
            if (index >= 0) {
                controls[index].offFocus();
            }
            saveSettings();
            context->setState("game");
            break;
        case sf::Keyboard::Up:
            if (index > 0) {
                controls[index].offFocus();
                index--;
                controls[index].onFocus();
            }
            break;
        case sf::Keyboard::Down:
            if (index + 1 < controls.size()) {
                controls[index].offFocus();
                index++;
                controls[index].onFocus();
            }
            break;
        case sf::Keyboard::Left:
            if (index >= 0)
                controls[index].prevParam();
            break;
        case sf::Keyboard::Right:
            if (index >= 0)
                controls[index].nextParam();
            break;
        default:
            break;
        }
    }
}
