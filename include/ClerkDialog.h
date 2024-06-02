#ifndef CLERKDIALOG_H
#define CLERKDIALOG_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Animation.h"
#include "DelayedText.h"
#include "Sklep.h"
#include "shopstate.h"



class ClerkDialog
{
    public:
        ClerkDialog(sf::Font &font);
        virtual ~ClerkDialog();
        std::vector<std::string> dialog;
        size_t i = 0;
        DelayedText txt;

        void loadNew(std::string a);
        bool setDialog();
        void resetI();
        void handleKeyPressClerk(shopstate &state);

    protected:

    private:
};

#endif // CLERKDIALOG_H
