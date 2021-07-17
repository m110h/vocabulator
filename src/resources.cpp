#include "resources.hpp"
#include "log.hpp"

#include <cassert>

Resources::Resources() {}
Resources::~Resources() {}

void Resources::load() {
    try {
        config.readFile("resources/game.cfg");
    }
    catch (const libconfig::FileIOException &fioex) {
        PLOG_DEBUG << "config error: file not found";
        exit(0);
    }
    catch (const libconfig::ParseException &pex) {
        PLOG_DEBUG << "config error: parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError();
        exit(0);
    }

    assert(gamefont.loadFromFile("resources/smw-text-2-nc.ttf"));
    text.setFont(gamefont);

    assert(successbuf.loadFromFile("resources/Powerup11.wav"));
    assert(failbuf.loadFromFile("resources/Blip_Select7.wav"));

    snd.setVolume(20);
}

void Resources::free() {}

sf::Text* Resources::getGameText() {
    return &text;
}

sf::Sound* Resources::getSuccessSound() {
    snd.setBuffer(successbuf);
    return &snd;
}
sf::Sound* Resources::getFailSound() {
    snd.setBuffer(failbuf);
    return &snd;
}

GameStatistics* Resources::getStatistics() {
    return &statistics;
}

GameSettings* Resources::getSettings() {
    return &settings;
}

libconfig::Config* Resources::getConfig() {
    return &config;
}


