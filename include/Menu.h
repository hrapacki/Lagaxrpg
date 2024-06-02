#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "gamestate.h"

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        sf::Text getPlay();
        sf::Text getExit();
        void setChoice();
        void setColors();
        bool getChoice();
        void handleKeyPress(sf::RenderWindow &window, gamestate &state);
        void whileActive(sf::RenderWindow &window, gamestate &state);
    private:
        sf::Text play, exit, credits;
        sf::Font font;
        bool whichOption;       ///jezeli jest 1, to PLAY jest podswietlone
        sf::Texture bgTexture;
        sf::Sprite bgSprite;
};

#endif // MENU_H
