//
// Created by Hubert on 25.05.2023.
//

#ifndef UNTITLED_BUTTON_H
#define UNTITLED_BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Character.h"
#include "Battle.h"
#include "Button.h"
#include "to_string.h"

class Button {
public:
    Button(float x, float y, const std::string& texturePath): wasPressed(false) {
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    bool isClicked(sf::RenderWindow &window) {
        bool result = false;
        bool isPressed = sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (isPressed) {
            if (!wasPressed) {
                clickClock.restart();
                wasPressed = true;
                result = true;
            } else {
                sf::Time elapsedTime = clickClock.getElapsedTime();
                if (elapsedTime.asMilliseconds() >= holdDelay) {
                    result = true;
                    clickClock.restart();
                }
            }
        } else {
            wasPressed = false;
        }

        return result;
    }

private:
    sf::Clock clickClock;
    bool wasPressed;
    const int holdDelay = 100;
    sf::Texture texture;
    sf::Sprite sprite;
};

class Creating_Character {
public:
    Creating_Character(sf::RenderWindow &window, sf::Font &font, int charisma = 0, int vigor = 0, int agility = 0, int strength = 0, int points = 20)
            : charisma(charisma), vigor(vigor), agility(agility), strength(strength), remainingPoints(points), window(window), font(font),
              plusCharisma(570, 281, "textures/creator/plus.png"), minusCharisma(378, 281, "textures/creator/minus.png"),
              plusVigor(570, 331, "textures/creator/plus.png"), minusVigor(378, 331, "textures/creator/minus.png"),
              plusAgility(570, 381, "textures/creator/plus.png"), minusAgility(378, 381, "textures/creator/minus.png"),
              plusStrength(570, 431, "textures/creator/plus.png"), minusStrength(378, 431, "textures/creator/minus.png"),
              finishButton(659, 461, "textures/creator/finish.png") {
        initStatsText();
    }

    // Gettery
    int getCharisma() const {
        return charisma;
    }

    int getVigor() const {
        return vigor;
    }

    int getAgility() const {
        return agility;
    }

    int getStrength() const {
        return strength;
    }

    int getRemainingPoints() const {
        return remainingPoints;
    }

    // Settery
    void increaseCharisma() {
        if (remainingPoints > 0) {
            charisma++;
            remainingPoints--;
        }
    }

    void decreaseCharisma() {
        if (charisma > 0) {
            charisma--;
            remainingPoints++;
        }
    }

    void increaseVigor() {
        if (remainingPoints > 0) {
            vigor++;
            remainingPoints--;
        }
    }

    void decreaseVigor() {
        if (vigor > 0) {
            vigor--;
            remainingPoints++;
        }
    }

    void increaseAgility() {
        if (remainingPoints > 0) {
            agility++;
            remainingPoints--;
        }
    }

    void decreaseAgility() {
        if (agility > 0) {
            agility--;
            remainingPoints++;
        }
    }

    void increaseStrength() {
        if (remainingPoints > 0) {
            strength++;
            remainingPoints--;
        }
    }

    void decreaseStrength() {
        if (strength > 0) {
            strength--;
            remainingPoints++;
        }
    }
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (plusCharisma.isClicked(window)) increaseCharisma();
            if (minusCharisma.isClicked(window)) decreaseCharisma();

            if (plusVigor.isClicked(window)) increaseVigor();
            if (minusVigor.isClicked(window)) decreaseVigor();

            if (plusAgility.isClicked(window)) increaseAgility();
            if (minusAgility.isClicked(window)) decreaseAgility();

            if (plusStrength.isClicked(window)) increaseStrength();
            if (minusStrength.isClicked(window)) decreaseStrength();
        }
    }

    bool isFinished() {
        return finishButton.isClicked(window);
    }

    void draw() {
        updateStatsText();
        window.draw(statsText);

        plusCharisma.draw(window);
        minusCharisma.draw(window);
        plusVigor.draw(window);
        minusVigor.draw(window);
        plusAgility.draw(window);
        minusAgility.draw(window);
        plusStrength.draw(window);
        minusStrength.draw(window);
        finishButton.draw(window);
    }
    void addPoints(int points) {
        remainingPoints += points;
    }
private:
    int charisma;
    int vigor;
    int agility;
    int strength;
    int remainingPoints;

    sf::RenderWindow &window;
    sf::Font &font;
    sf::Text statsText;
    sf::Text opis;
    Button plusCharisma;
    Button minusCharisma;
    Button plusVigor;
    Button minusVigor;
    Button plusAgility;
    Button minusAgility;
    Button plusStrength;
    Button minusStrength;
    Button finishButton;



    void initStatsText() {
        statsText.setFont(font);
        statsText.setCharacterSize(20);
        statsText.setFillColor(sf::Color::White);
        opis.setFont(font);
        opis.setCharacterSize(20);
        statsText.setFillColor(sf::Color::White);
    }

    void updateStatsText() {
        statsText.setPosition(430, 285);
        statsText.setString("Charisma: " + patch::to_string(getCharisma()));
        window.draw(statsText);
        opis.setPosition(785, 270);
        opis.setString("Charyzma zwieksza twoja szanse na przekonanie wrogow do ucieczki");
        window.draw(opis);

        statsText.setPosition(430, 335);
        statsText.setString("Vigor: " + patch::to_string(getVigor()));
        window.draw(statsText);
        opis.setPosition(785, 330);
        opis.setString("Vigor zwieksza twoje zdrowie");
        window.draw(opis);

        statsText.setPosition(430, 385);
        statsText.setString("Agility: " + patch::to_string(getAgility()));
        window.draw(statsText);
        opis.setPosition(785, 385);
        opis.setString("Agility zwieksza twoja szanse na unik oraz zadania ciosu krytycznego ");
        window.draw(opis);

        statsText.setPosition(430, 435);
        statsText.setString("Strength: " + patch::to_string(getStrength()));
        window.draw(statsText);
        opis.setPosition(785, 445);
        opis.setString("Strength zwieksza moc twoich atakow");
        window.draw(opis);

        statsText.setPosition(388, 490);
        statsText.setString("Pozostale punkty: " + patch::to_string(getRemainingPoints()));
        window.draw(statsText);
    }
};


class LevelUp_Character {
public:
    LevelUp_Character(sf::RenderWindow &window, sf::Font &font, int charisma, int vigor, int agility, int strength, int points)
            : charisma(charisma), vigor(vigor), agility(agility), strength(strength), remainingPoints(points), window(window), font(font),
              plusCharisma(570, 281, "textures/creator/plus.png"),
              plusVigor(570, 331, "textures/creator/plus.png"),
              plusAgility(570, 381, "textures/creator/plus.png"),
              plusStrength(570, 431, "textures/creator/plus.png"),
              finishButton(659, 461,  "textures/creator/finish.png") {
        initStatsText();
    }

    // Gettery
    int getCharisma() const {
        return charisma;
    }

    int getVigor() const {
        return vigor;
    }

    int getAgility() const {
        return agility;
    }

    int getStrength() const {
        return strength;
    }

    int getRemainingPoints() const {
        return remainingPoints;
    }

    // Settery
    void increaseCharisma() {
        if (remainingPoints > 0) {
            charisma++;
            remainingPoints--;
        }
    }


    void increaseVigor() {
        if (remainingPoints > 0) {
            vigor++;
            remainingPoints--;
        }
    }


    void increaseAgility() {
        if (remainingPoints > 0) {
            agility++;
            remainingPoints--;
        }
    }



    void increaseStrength() {
        if (remainingPoints > 0) {
            strength++;
            remainingPoints--;
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (plusCharisma.isClicked(window)) increaseCharisma();

            if (plusVigor.isClicked(window)) increaseVigor();

            if (plusAgility.isClicked(window)) increaseAgility();

            if (plusStrength.isClicked(window)) increaseStrength();
        }
    }

    bool isFinished() {
        return finishButton.isClicked(window);
    }

    void draw() {
        updateStatsText();
        window.draw(statsText);

        plusCharisma.draw(window);

        plusVigor.draw(window);

        plusAgility.draw(window);

        plusStrength.draw(window);

        finishButton.draw(window);
    }
    void addPoints(int points) {
        remainingPoints += points;
    }
private:
    int charisma;
    int vigor;
    int agility;
    int strength;
    int remainingPoints;

    sf::RenderWindow &window;
    sf::Font &font;
    sf::Text statsText;
    sf::Text opis;
    Button plusCharisma;

    Button plusVigor;

    Button plusAgility;

    Button plusStrength;

    Button finishButton;



    void initStatsText() {
        statsText.setFont(font);
        statsText.setCharacterSize(20);
        statsText.setFillColor(sf::Color::White);
        opis.setFont(font);
        opis.setCharacterSize(20);
        statsText.setFillColor(sf::Color::White);
    }

    void updateStatsText() {
        statsText.setPosition(430, 285);
        statsText.setString("Charisma: " + patch::to_string(getCharisma()));
        window.draw(statsText);
        opis.setPosition(785, 270);
        opis.setString("Charyzma zwieksza twoja szanse na przekonanie wrogow do ucieczki");
        window.draw(opis);


        statsText.setPosition(430, 335);
        statsText.setString("Vigor: " + patch::to_string(getVigor()));
        window.draw(statsText);
        opis.setPosition(785, 330);
        opis.setString("Vigor zwieksza twoje zdrowie");
        window.draw(opis);

        statsText.setPosition(430, 385);
        statsText.setString("Agility: " + patch::to_string(getAgility()));
        window.draw(statsText);

        opis.setPosition(785, 385);
        opis.setString("Agility zwieksza twoja szanse na unik oraz zadania ciosu krytycznego ");
        window.draw(opis);

        statsText.setPosition(430, 435);
        statsText.setString("Strength: " + patch::to_string(getStrength()));
        window.draw(statsText);
        opis.setPosition(785, 445);
        opis.setString("Strength zwieksza moc twoich atakow");
        window.draw(opis);


        statsText.setPosition(388, 490);
        statsText.setString("Pozostale punkty: " + patch::to_string(getRemainingPoints()));
        window.draw(statsText);


    }
};
#endif //UNTITLED_BUTTON_H
