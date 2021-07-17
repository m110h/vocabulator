#ifndef _GAME_OBJECTS_H_
#define _GAME_OBJECTS_H_

#include <SFML/Graphics.hpp>

#include <cmath>
#include <string>

#include "log.hpp"
#include "random.hpp"

class WordDescription
{
public:
    WordDescription(): word {}, type {}, translate {} {}

    WordDescription(const sf::String& _word, const sf::String& _type, const sf::String& _translate):
        word {_word}, type {_type}, translate {_translate}
    {}

    ~WordDescription() {}

    WordDescription& operator=(const WordDescription& r) {
        if (this == &r) {
            return *this;
        }
        word = r.word;
        type = r.type;
        translate = r.translate;

        return *this;
    }

    void setWord(const sf::String& word) {
        this->word = word;
    }
    void setType(const sf::String& type) {
        this->type = type;
    }
    void setTranslate(const sf::String& translate) {
        this->translate = translate;
    }

    const sf::String& getWord() {
        return word;
    }
    const sf::String& getType() {
        return type;
    }
    const sf::String& getTranslate() {
        return translate;
    }

private:
    sf::String word;
    sf::String type;
    sf::String translate;
};

class MovableObject
{
public:
    MovableObject(): position {0.f, 0.f} {}

    virtual ~MovableObject() {
        PLOG_DEBUG << "MovableObject destructor";
    }

    void setPosition(const sf::Vector2f& position) {
        this->position = position;
    }

protected:
    sf::Vector2f position;
};

class CountdownTimer: public MovableObject
{
public:
    CountdownTimer(): time {}, animation_time {} {}

    ~CountdownTimer() {
        PLOG_DEBUG << "CountdownTimer destructor";
    }

    void setTimer(float time) {
        this->time = time;
        animation_time = 0.f;
    }

    bool isAlive() {
        return time > 0.f;
    }

    void update(float delta) {
        if (time > 0.f)
            time -= delta;
        if (time < 0.f)
            time = 0.f;

        animation_time += delta;
        if (animation_time > 3.14f)
            animation_time = 0.f;
    }

    void draw(sf::RenderWindow* window, sf::Text* text) {
        text->setCharacterSize(30);

        if (time < 10.f) {
            text->setFillColor(sf::Color(200, 20, 20));
            sf::Color c = text->getFillColor();
            c.a = sf::Uint8(255.f * std::abs(std::cos(animation_time*5.f)));
            text->setFillColor(c);
        }
        else if (time < 20.f) {
            text->setFillColor(sf::Color(50, 200, 50));
            sf::Color c = text->getFillColor();
            c.a = sf::Uint8(255.f * std::abs(std::cos(animation_time*5.f)));
            text->setFillColor(c);
        }
        else {
            text->setFillColor(sf::Color::White);
        }

        //
        text->setString( sf::String("Timer: " + std::to_string(int(time))) );

        sf::FloatRect box = text->getLocalBounds();
        text->setOrigin(sf::Vector2f(box.left+box.width*0.5f, box.top));

        text->setPosition(position);

        window->draw(*text);
    }

private:
    float time;
    float animation_time;
};

class Word: public MovableObject
{
public:
    Word(): desc {}, animation_time {} {}

    virtual ~Word() {
        PLOG_DEBUG << "Word destructor";
    }

    void setDescription(WordDescription* desc) {
        this->desc = desc;
    }

    WordDescription* getDescription() {
        return desc;
    }

    void reset() {
        animation_time = 0.f;
    }

    void update(float delta) {
        animation_time += delta;
        if (animation_time > 1.f)
            animation_time = 1.f;
    }

    void draw(sf::RenderWindow* window, sf::Text* text) {
        sf::Color c = sf::Color::White;
        c.a = sf::Uint8(255.f * animation_time);
        text->setFillColor(c);

        templateMethodPrepare(text);

        sf::FloatRect box = text->getLocalBounds();
        text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));

        text->setPosition(position);

        window->draw(*text);

        text->setCharacterSize(24);

        c = sf::Color(37, 136, 239);
        c.a = sf::Uint8(255.f * animation_time);
        text->setFillColor(c);

        text->setString(desc->getType());

        box = text->getLocalBounds();
        text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));
        text->move(sf::Vector2f(0.f, box.height + 20.f));

        window->draw(*text);
    }

protected:
    virtual void templateMethodPrepare(sf::Text* text) = 0;

protected:
    WordDescription* desc;
    float animation_time;
};

class SimpleWord: public Word
{
public:
    SimpleWord(): Word() {}
    ~SimpleWord() {
        PLOG_DEBUG << "SimpleWord destructor";
    }

protected:
    void templateMethodPrepare(sf::Text* text) override {
        text->setCharacterSize(30);
        text->setString(desc->getWord());
    }
};

class ReverseWord: public Word
{
public:
    ReverseWord(): Word() {}
    ~ReverseWord() {
        PLOG_DEBUG << "ReverseWord destructor";
    }

protected:
    void templateMethodPrepare(sf::Text* text) override {
        text->setCharacterSize(28);
        text->setString(desc->getTranslate());
    }
};

class AnswersPanel: public MovableObject
{
public:
    AnswersPanel(): leftAnswer {}, rightAnswer {}, leftOnFocus {false}, rightOnFocus {false} {}

    virtual ~AnswersPanel() {
        PLOG_DEBUG << "AnswersPanel destructor";
    }

    void setAnswers(WordDescription* answer1, WordDescription* answer2)
    {
        if (effolkronium::random_static::get<bool>()) {
            leftAnswer = answer1;
            rightAnswer = answer2;
        }
        else {
            leftAnswer = answer2;
            rightAnswer = answer1;
        }

        leftOnFocus = false;
        rightOnFocus = false;
    }

    void leftSetFocus() {
        leftOnFocus = true;
    }

    void rightSetFocus() {
        rightOnFocus = true;
    }

    WordDescription* getLeftAnswer() {
        return leftAnswer;
    }
    WordDescription* getRightAnswer() {
        return rightAnswer;
    }

    void update(float delta) {}

    void draw(sf::RenderWindow* window, sf::Text* text) {
        sf::String left = "";
        sf::String right = "";

        templateMethodPrepare(text, left, right);

        sf::String out = left + " | " + right;

        text->setString(out);

        sf::FloatRect box = text->getLocalBounds();
        text->setOrigin(sf::Vector2f(box.width*0.5f, box.height*0.5f));

        text->setPosition(position);

        box = text->getGlobalBounds();

        text->setFillColor(sf::Color::White);
        text->setOrigin(sf::Vector2f(0.f, 0.f));
        if (leftOnFocus) {
            text->setFillColor(sf::Color(50, 200, 50));
        }
        text->setString(left);
        text->setPosition(sf::Vector2f(box.left, box.top));
        window->draw(*text);
        box = text->getLocalBounds();

        text->setFillColor(sf::Color::White);
        text->move(sf::Vector2f(box.width, 0.f));
        text->setString(" | ");
        window->draw(*text);
        box = text->getLocalBounds();

        if (rightOnFocus) {
            text->setFillColor(sf::Color(50, 200, 50));
        }
        text->setString(right);
        text->move(sf::Vector2f(box.width, 0.f));
        window->draw(*text);
    }

protected:
    virtual void templateMethodPrepare(sf::Text* text, sf::String& left, sf::String& right) = 0;

protected:
    WordDescription* leftAnswer;
    WordDescription* rightAnswer;

private:
    bool leftOnFocus;
    bool rightOnFocus;
};

class SimpleAnswersPanel: public AnswersPanel
{
public:
    SimpleAnswersPanel(): AnswersPanel() {}
    ~SimpleAnswersPanel() {
        PLOG_DEBUG << "SimpleAnswersPanel destructor";
    }

    void templateMethodPrepare(sf::Text* text, sf::String& left, sf::String& right) override {
        text->setCharacterSize(24);
        left = leftAnswer->getTranslate();
        right = rightAnswer->getTranslate();
    }
};

class ReverseAnswersPanel: public AnswersPanel
{
public:
    ReverseAnswersPanel(): AnswersPanel() {}
    ~ReverseAnswersPanel() {
        PLOG_DEBUG << "ReverseAnswersPanel destructor";
    }

    void templateMethodPrepare(sf::Text* text, sf::String& left, sf::String& right) override {
        text->setCharacterSize(26);
        left = leftAnswer->getWord();
        right = rightAnswer->getWord();
    }
};

#endif // _GAME_OBJECTS_H_
