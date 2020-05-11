#ifndef _GAME_SETTINGS_H_
#define _GAME_SETTINGS_H_

#include <SFML/Graphics.hpp>

class GameSettings
{
public:
    GameSettings();
    ~GameSettings();

    void setType(const sf::String& type);
    void setMode(const sf::String& mode);
    void setSound(const sf::String& sound);
    void setDictionary(const sf::String& dictionary);

    const sf::String& getType();
    const sf::String& getMode();
    const sf::String& getSound();
    const sf::String& getDictionary();

private:
    sf::String type;
    sf::String mode;
    sf::String sound;
    sf::String dictionary;
};

#endif // _GAME_SETTINGS_H_
