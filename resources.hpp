#ifndef _RESOURCES_SINGLETON_H_
#define _RESOURCES_SINGLETON_H_

#include <libconfig.hh>

#include "gamestatistics.hpp"
#include "gamesettings.hpp"

#include <SFML/Audio.hpp>

#include <memory>

class Resources
{
public:
    Resources(const Resources& src) = delete;
    ~Resources();

    void load();
    void free();

    sf::Text* getGameText();

    sf::Sound* getSuccessSound();
    sf::Sound* getFailSound();

    GameStatistics* getStatistics();
    GameSettings* getSettings();

    libconfig::Config* getConfig();

    // Singleton Мэйерса
    static Resources& getInstance() {
        static Resources _instance;
        return _instance;
    }

private:
    Resources();

private:
    sf::Text text;
    sf::Font gamefont;

    sf::Sound snd;
    sf::SoundBuffer successbuf;
    sf::SoundBuffer failbuf;

    GameStatistics statistics;
    GameSettings settings;

    libconfig::Config config;
};

#endif // _RESOURCES_SINGLETON_H_
