#include "gamesettings.hpp"

GameSettings::GameSettings() {
    type = "";
    mode = "";
    sound = "";
    dictionary = "";
}

GameSettings::~GameSettings() {}

void GameSettings::setType(const sf::String& type) {
    this->type = type;
}

void GameSettings::setMode(const sf::String& mode) {
    this->mode = mode;
}

void GameSettings::setSound(const sf::String& sound) {
    this->sound = sound;
}

void GameSettings::setDictionary(const sf::String& dictionary) {
    this->dictionary = dictionary;
}

const sf::String& GameSettings::getType() {
    return type;
}

const sf::String& GameSettings::getMode() {
    return mode;
}

const sf::String& GameSettings::getSound() {
    return sound;
}

const sf::String& GameSettings::getDictionary() {
    return dictionary;
}
