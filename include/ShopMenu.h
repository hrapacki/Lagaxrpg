#ifndef SHOPMENU_H
#define SHOPMENU_H
#include "SFML/Graphics.hpp"
#include "choice.h"
#include "shopstate.h"

class ShopMenu
{
    public:
        sf::Text talk;
        sf::Text buy;
        sf::Text exit;
        Choice choice = Choice::first;
        ShopMenu();
        ShopMenu(sf::Font &font);
        virtual ~ShopMenu();

        void setActive();

        void handleKeyPressMenu(shopstate &state);
        void drawAll(sf::RenderWindow &window);

    protected:

    private:
};

#endif // MENU_H
