#include "ClerkDialog.h"
#include "shopstate.h"
ClerkDialog::ClerkDialog(sf::Font &font)
{
    std::cout << "sklepikarz przyszedl :D" << std::endl;

    loadNew("dialog/shop/shop.txt");
    txt.setString(dialog[i++]);
    txt.setCharacterSize(30);
    txt.setFont(font);
    txt.setDelay(sf::seconds(1.f/40.f));
    txt.setPosition(sf::Vector2f((1920-1920/1.6)/2, (1080-1080/2.6)));
}

ClerkDialog::~ClerkDialog()
{
    dialog.clear();
    std::cout << "sklepikarz wyszedl :(" << std::endl;
}

void ClerkDialog::loadNew(std::string a){
    std::fstream test(a);
    std::string b;
    dialog.clear();
    do{
        getline(test, b);
        dialog.push_back(b);
    }while(!test.eof());
    test.close();
}

bool ClerkDialog::setDialog(){
    if(i<dialog.size()){
        txt.setString(dialog[i++]);
        return true;
    }
    else{
        i=0;
        txt.setString(dialog[i++]);
        return false;
    }
}

void ClerkDialog::resetI(){
    i = 0;
    txt.setString(dialog[i++]);
}

void ClerkDialog::handleKeyPressClerk(shopstate &state){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        if(!setDialog()){
            state = shopstate::limbo;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
        state = shopstate::limbo;
        i=0;
        txt.setString(dialog[i++]);
    }
}
