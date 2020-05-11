#include "gamestate.hpp"
#include "gamestatistics.hpp"

#include <cstdlib>
#include <ctime>

#include <locale>
#include <codecvt>

#include "resources.hpp"
#include "log.hpp"
#include "random.hpp"

VariantGame::VariantGame(const sf::String& dictionary, float time):
    timer(), word(nullptr), answers(nullptr)
{
    loadDescriptions(dictionary);
    timer.setTimer(time);
}

VariantGame::~VariantGame()
{
    descriptions.clear();
}

void VariantGame::loadDescriptions(const sf::String& dictionary) {
    descriptions.clear();

    libconfig::Config* cfg = Resources::getInstance().getConfig();

    const libconfig::Setting& root = cfg->getRoot();

    const libconfig::Setting &words = root["dictionaries"][dictionary.toAnsiString()];
    int count = words.getLength();

    for(int i = 0; i<count; i++) {
        const libconfig::Setting &word = words[i];
        std::string w, t, tr;

        if(!(word.lookupValue("word", w) && word.lookupValue("type", t) && word.lookupValue("translate", tr)))
           continue;

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        std::wstring ww = converter.from_bytes(w);
        std::wstring wt = converter.from_bytes(t);
        std::wstring wtr = converter.from_bytes(tr);

        descriptions.push_back(WordDescription(ww.c_str(), wt.c_str(), wtr.c_str()));
    }
}

void VariantGame::reset() {
    nextWord();
}

bool VariantGame::isOver() {
    return !timer.isAlive();
}

void VariantGame::update(float delta) {
    timer.update(delta);

    word->update(delta);
    answers->update(delta);
}

void VariantGame::draw(sf::RenderWindow* window) {
    sf::Text* text = Resources::getInstance().getGameText();

    timer.setPosition(sf::Vector2f(window->getSize().x*0.5f, 20.f));
    timer.draw(window, text);

    word->setPosition(sf::Vector2f(window->getSize().x*0.5f, 150.f));
    word->draw(window, text);

    answers->setPosition(sf::Vector2f(window->getSize().x*0.5f, window->getSize().y*0.5f));
    answers->draw(window, text);

    drawStatistics(window);
}

void VariantGame::drawStatistics(sf::RenderWindow* window) {
    GameStatistics* statistics = Resources::getInstance().getStatistics();

    sf::Text* text = Resources::getInstance().getGameText();
    sf::FloatRect box;

    text->setCharacterSize(18);
    text->setOrigin(sf::Vector2f(0.f, 0.f));

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Scores "));
    box = text->getLocalBounds();
    text->setPosition(sf::Vector2f(20.f, window->getSize().y - box.height - 20.f));
    window->draw(*text);

    text->move(sf::Vector2f(box.width + 3.f, 0.f));

    text->setFillColor(sf::Color(50, 200, 50));
    text->setString(sf::String(std::to_string(statistics->getScores())));
    box = text->getLocalBounds();
    window->draw(*text);

    text->setPosition(sf::Vector2f(175.f, window->getSize().y - box.height - 20.f));

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Fails "));
    box = text->getLocalBounds();
    window->draw(*text);

    text->move(sf::Vector2f(box.width + 3.f, 0.f));

    text->setFillColor(sf::Color(200, 20, 20));
    text->setString(sf::String(std::to_string(statistics->getFails())));
    box = text->getLocalBounds();
    window->draw(*text);

    text->setPosition(sf::Vector2f(300.f, window->getSize().y - box.height - 20.f));

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Skips "));
    box = text->getLocalBounds();
    window->draw(*text);

    text->move(sf::Vector2f(box.width + 3.f, 0.f));

    text->setFillColor(sf::Color(204, 183, 22));
    text->setString(sf::String(std::to_string(statistics->getSkips())));
    window->draw(*text);

    text->setPosition(sf::Vector2f(window->getSize().x - 220.f, window->getSize().y - box.height - 20.f));

    text->setFillColor(sf::Color::White);
    text->setString(sf::String("Accuracy(%) "));
    box = text->getLocalBounds();
    window->draw(*text);

    text->move(sf::Vector2f(box.width + 3.f, 0.f));

    text->setFillColor(sf::Color(37, 136, 239));
    text->setString(sf::String(std::to_string(statistics->getAccuracy())));
    window->draw(*text);
}

void VariantGame::processEvent(const sf::Event& event) {
    if (timer.isAlive()) {
        GameStatistics* statistics = Resources::getInstance().getStatistics();

        if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
            case sf::Keyboard::Left:
                if ( checkAnswer(word->getDescription(), answers->getLeftAnswer()) ) {
                    statistics->incScores();
                    //Resources::getInstance().getSuccessSound()->play();
                }
                else {
                    statistics->incFails();
                    Resources::getInstance().getFailSound()->play();
                }
                nextWord();
                break;
            case sf::Keyboard::Right:
                if ( checkAnswer(word->getDescription(), answers->getRightAnswer()) ) {
                    statistics->incScores();
                    //Resources::getInstance().getSuccessSound()->play();
                }
                else {
                    statistics->incFails();
                    Resources::getInstance().getFailSound()->play();
                }
                nextWord();
                break;
            case sf::Keyboard::Down:
                statistics->incSkips();
                nextWord();
                break;
            default:
                break;
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Left:
                answers->leftSetFocus();
                break;
            case sf::Keyboard::Right:
                answers->rightSetFocus();
                break;
            default:
                break;
            }
        }
    }
}

bool VariantGame::checkAnswer(WordDescription* w, WordDescription* a) {
    return w->getWord() == a->getWord();
}

void VariantGame::nextWord()
{
    int count = static_cast<int>(descriptions.size()-1);

    // todo: handle a variant if size equal 0

    word->setDescription(&descriptions[ effolkronium::random_static::get(0,count) ]);
    word->reset();

    WordDescription* tmp;

    if (descriptions.size() == 1)
    {
        tmp = &descriptions[0];
    }
    else {
        do {
            tmp = &descriptions[ effolkronium::random_static::get(0,count) ];
        } while (tmp->getWord() == word->getDescription()->getWord());
    }

    answers->setAnswers(word->getDescription(), tmp);
}

SimpleGame::SimpleGame(const sf::String& dictionary, float time):
    VariantGame(dictionary, time)
{
    word = std::make_unique<SimpleWord>();
    answers = std::make_unique<SimpleAnswersPanel>();
}
SimpleGame::~SimpleGame() {}

ReverseGame::ReverseGame(const sf::String& dictionary, float time):
    VariantGame(dictionary, time)
{
    word = std::make_unique<ReverseWord>();
    answers = std::make_unique<ReverseAnswersPanel>();
}
ReverseGame::~ReverseGame() {}

/**/

Game::Game(): State(), game {nullptr} {
    PLOG_DEBUG << "Game constructor";
    setName("game");
}

Game::~Game() {
    PLOG_DEBUG << "Game destructor";
    if (game) {
        delete game;
    }
}

void Game::update(float delta) {
    if (game) {
        if (game->isOver()) {
            context->setState("statistics");
        }
        else {
            game->update(delta);
        }
    }
}

void Game::draw(sf::RenderWindow* window) {
    window->clear(sf::Color(0, 0, 0));

    if (game) {
        game->draw(window);
    }
}

void Game::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        context->setState("menu");
    }
    else if (game) {
        game->processEvent(event);
    }
}

void Game::reset() {
    if (game) {
        delete game;
    }

    GameSettings* settings = Resources::getInstance().getSettings();

    VariantGame* tmp = nullptr;

    std::string type = settings->getType().toAnsiString();
    if (type == "reverse") {
        tmp = new ReverseGame(settings->getDictionary(), getTimeByMode(settings->getMode()));
    }
    else {
        tmp = new SimpleGame(settings->getDictionary(), getTimeByMode(settings->getMode()));
    }

    //assert(tmp && "logical error: unknown type of game");

    tmp->reset();
    game = tmp;

    Resources::getInstance().getStatistics()->reset();
}

float Game::getTimeByMode(const sf::String& mode)
{
    const libconfig::Setting& root = Resources::getInstance().getConfig()->getRoot();
    const libconfig::Setting &params = root["game"]["Mode"];

    float time = 0;

    for (int j=0; j<params.getLength(); j++) {
        const libconfig::Setting &param = params[j];

        std::string name;
        if(!(param.lookupValue("name", name) && param.lookupValue("timer", time)))
            assert("config error: bad Mode configuration has detected");

        if (name == mode.toAnsiString()) {
            break;
        }
    }

    return time;
}
