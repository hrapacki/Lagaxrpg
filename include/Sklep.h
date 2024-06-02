#ifndef SKLEP_H
#define SKLEP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Animation.h"
#include "DelayedText.h"
#include "shopstate.h"
#include "Battle.h"

class Sklep
{
    public:
        std::vector<sf::Text> produkty;
        size_t ileProd = 0;
        int saldo = 0;
        size_t choice = 1;
        sf::RectangleShape box;
        //Animation clerkA;
        sf::Sprite clerkS;
        sf::Sprite backg;
        sf::Texture texture;
        sf::Texture bgtext;
        Sklep(sf::Font &font, int &cash);
        virtual ~Sklep();

        sf::Text currentS(sf::Font &font);
        void setClerkS(std::string a);
        void changePrice();
        size_t getIle();
        sf::Text getString(size_t const i);
        void setActive();
        bool isBought();
        bool enoughMoney();
        int getSaldo();
        void addToInventory(size_t i);
        void handleKeyPressShop(shopstate &state, PlayerCharacter *&player);

        sf::Text uSure;
        sf::Text tak;
        sf::Text nie;

        bool confirm = false;
        bool takCzyNie = true;

        void toggleChoice();

    protected:

    private:

};

#endif // SKLEP_H
