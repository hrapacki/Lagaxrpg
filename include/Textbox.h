#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "DelayedText.h"

class Textbox
{
    public:
        sf::RectangleShape box;
        std::vector<std::string> dialog;
        std::vector<sf::Texture> tekstury;          ///added
        size_t i = 0;
        size_t whichTexture = 0;          ///added
        sf::Font font;
        sf::Sprite sprite;          ///added
        DelayedText txt,
        q1,
        q2;
        Textbox(sf::Font &inFont, std::string &a, std::string &b);
        virtual ~Textbox();

        void displayInConsole();
        bool isQuestion();
        bool isEnd();
        void setDialog();
        bool findChoice(size_t c);
        void setImage();

        bool handleKeyPress(size_t &choice);
        void whileActive(sf::RenderWindow &window);
};

#endif // TEXTBOX_H
