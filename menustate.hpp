#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "abstractstate.hpp"
#include <vector>

class Control
{
public:
    Control(): isFocused(false), index(-1) {
        name = "";
    }
    ~Control() {}

    void update(float delta) {}

    void draw(sf::RenderWindow* window, sf::Vector2f pos);

    void reset() {
        if (params.size()>0)
            index = 0;
        else
            index = -1;
    }

    void onFocus() {
        isFocused = true;
    }
    void offFocus() {
        isFocused = false;
    }

    void setName(const sf::String& name) {
        this->name = name;
    }
    const sf::String& getName() {
        return name;
    }

    void addParam(const sf::String& param) {
        params.push_back(param);
    }

    void prevParam() {
        if (index > 0)
            index--;
    }
    void nextParam() {
        if (index+1 < params.size())
            index++;
    }

    const sf::String& getParam() {
        return params[index];
    }

private:
    bool isFocused;

    sf::String name;
    std::vector<sf::String> params;

    size_t index;
};

class Menu: public State
{
public:
    Menu();
    ~Menu();

    void update(float delta);
    void draw(sf::RenderWindow* window);
    void processEvent(const sf::Event& event);
    void reset();

private:
    void saveSettings();

private:
    std::vector<Control> controls;
    size_t index;
};

#endif // _MENU_STATE_H_

