#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "abstractstate.hpp"
#include "gameobjects.hpp"

#include <memory>

// Strategy pattern
class AbstractGame
{
public:
    AbstractGame() {}
    virtual ~AbstractGame() {}

    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void processEvent(const sf::Event& event) = 0;

    virtual void reset() = 0;

    virtual bool isOver() = 0;
};


//
class VariantGame: public AbstractGame
{
public:
    VariantGame(const sf::String& dictionary, float time);
    virtual ~VariantGame();

    void update(float delta) override;
    void draw(sf::RenderWindow* window) override;
    void processEvent(const sf::Event& event) override;

    void reset() override;

    bool isOver() override;

private:
    void loadDescriptions(const sf::String& dictionary);
    bool checkAnswer(WordDescription* w, WordDescription* a);
    void nextWord();
    void drawStatistics(sf::RenderWindow* window);

private:
    std::vector<WordDescription> descriptions;

    CountdownTimer timer;

protected:
    std::unique_ptr<Word> word;
    std::unique_ptr<AnswersPanel> answers;
};


class SimpleGame: public VariantGame
{
public:
    SimpleGame(const sf::String& dictionary, float time);
    ~SimpleGame();
};

class ReverseGame: public VariantGame
{
public:
    ReverseGame(const sf::String& dictionary, float time);
    ~ReverseGame();
};


// Strategy Context and Concrete State
class Game: public State
{
public:
    Game();
    ~Game();

    void update(float delta);
    void draw(sf::RenderWindow* window);
    void processEvent(const sf::Event& event);

    void reset();

private:
    float getTimeByMode(const sf::String& mode);

private:
    AbstractGame* game;
};

#endif // _GAME_STATE_H_
