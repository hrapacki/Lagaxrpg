#include "Sklep.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Animation.h"
#include "DelayedText.h"
#include "to_string.h"


Sklep::Sklep(sf::Font &font, int &cash): saldo(cash){
        std::cout << "sklep otwarty :D" << std::endl;

        std::string in;
        std::fstream input("data/sklepInput.txt");
        do{
            getline(input, in);
            if(in!=""){
                sf::Text nowy(in, font, (1920+1080)/100);
                nowy.setPosition(sf::Vector2f((1920-1920/1.6)/2, (1080-1080/2.6) +ileProd*(1920+1080)/75));
                if((ileProd++)==0){
                    nowy.setColor(sf::Color::Yellow);
                }
                produkty.push_back(nowy);
            }
        }
        while(!input.eof());
        input.close();

        box.setFillColor(sf::Color::Black);
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(5);
        box.setPosition(1920/6, 1080*6/10);
        box.setSize(sf::Vector2f(1920/1.5, 1080/3));


        texture.loadFromFile("textures/shop/clerkIdle.png");
        clerkS.setTexture(texture);
        clerkS.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
        clerkS.setPosition(1920/2, 1080*1/3);
        bgtext.loadFromFile("textures/shop/background.png");
        backg.setTexture(bgtext);
        backg.setOrigin(bgtext.getSize().x/2, bgtext.getSize().y/2);
        backg.setPosition(1920/2, 1080*1/3);

        uSure.setString("");
        uSure.setFont(font);
        uSure.setCharacterSize(30);
        uSure.setPosition(sf::Vector2f(1920-2*(1920-1920/1.6)/2, (1080-1080/2.6)));

        tak.setString("Tak");
        tak.setFont(font);
        tak.setCharacterSize(30);
        tak.setPosition(sf::Vector2f(1920-2*(1920-1920/1.6)/2, (1920+1080)/75+(1080-1080/2.6)));

        nie.setString("Nie");
        nie.setFont(font);
        nie.setCharacterSize(30);
        nie.setPosition(sf::Vector2f(1920-1.5*(1920-1920/1.6)/2, (1920+1080)/75+(1080-1080/2.6)));
}

Sklep::~Sklep()
{
    produkty.clear();
    std::cout << "sklep sie zniszczyl :(" << std::endl;
}

sf::Text Sklep::currentS(sf::Font &font){
    std::string ret = "Obecny stan konta: "+patch::to_string(saldo);
    sf::Text wynik(ret, font, (1920+1080)/100);
    wynik.setPosition(0.f, 40.f);
    return wynik;
}

void Sklep::setClerkS(std::string a){
    texture.loadFromFile(a);
    clerkS.setTexture(texture);
}

void Sklep::changePrice(){
    std::string s;
    saldo-=50;
}

size_t Sklep::getIle(){
    return ileProd;
}

sf::Text Sklep::getString(size_t const i){
    return produkty[i];
}

void Sklep::setActive(){
    switch(choice){
        case 1:{
            produkty[choice-1].setColor(sf::Color::Yellow);
            produkty[choice].setColor(sf::Color::White);
            produkty[ileProd-1].setColor(sf::Color::White);
            break;
        }
        case 3:{
            produkty[choice-1].setColor(sf::Color::Yellow);
            produkty[choice-2].setColor(sf::Color::White);
            produkty[0].setColor(sf::Color::White);
            break;
        }
        default:{
            produkty[choice-1].setColor(sf::Color::Yellow);
            produkty[choice-2].setColor(sf::Color::White);
            produkty[choice].setColor(sf::Color::White);
            break;
        }
    }
}

bool Sklep::isBought(){
    std::string condition = produkty[choice-1].getString();
    return (condition == "<-SOLD OUT->");
}

bool Sklep::enoughMoney(){
    return (saldo!=0 and (saldo-50)>=0);
}

int Sklep::getSaldo(){
    return saldo;
}

void Sklep::addToInventory(size_t i){
    if(!isBought() and enoughMoney()){
        std::fstream inv("data/inventory.txt", std::ios::out|std::ios::app);    ///ta flaga jest do dopisywania
        std::string a = produkty[i-1].getString();
        inv << a << std::endl;
        inv.close();
        produkty[i-1].setString("<-SOLD OUT->");

        std::fstream shop("data/sklepInput.txt", std::ios::out|std::ios::trunc);     ///ta flaga jest do nadpisywania
        for(auto it = produkty.begin();it!=produkty.end();it++){
            std::string out = it->getString();
            if(it==produkty.end()){
                shop << out;
            }
            else{
                shop << out << std::endl;
            }
        }
        shop.close();
        saldo-=50;
    }
    else{
        std::cout << "niewystarczajaca ilosc pieniedzy" << std::endl;
    }
}

void Sklep::handleKeyPressShop(shopstate &state, PlayerCharacter *&player){
    if(confirm){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
            if(!takCzyNie){
                confirm = false;
                takCzyNie = true;
            }
            else{
                addToInventory(choice);
                switch(choice){
                    case 1:{
                        player->setAgility(player->getAgility()+10);
                        break;
                    }
                    case 2:{
                        player->setCharisma(player->getCharisma()+10);
                        break;
                    }
                    case 3:{
                        player->setStrength(player->getStrength()+10);
                        break;
                    }
                }
                std::fstream saldo("data/saldo.txt", std::ios::out|std::ios::trunc);         ///dodajemy to zeby czyscil nam sie plik
                saldo << getSaldo();
                saldo.close();
                confirm = false;
                takCzyNie = true;
                setClerkS("textures/shop/clerkIdle.png");
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            takCzyNie = !takCzyNie;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)){
            confirm = false;
        }
    }
    else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            if(choice == 1){
                choice = getIle();
            }
            else{
                choice--;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            if(choice == getIle()){
                choice = 1;
            }
            else{
                choice++;
            }
        }
        if(enoughMoney() and !isBought() and sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
            confirm = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)){
            state = shopstate::limbo;
        }
    }
}

void Sklep::toggleChoice()
{

    switch(takCzyNie){
        case true:{
            nie.setColor(sf::Color::White);
            tak.setColor(sf::Color::Yellow);
            break;
        }
        case false:{
            nie.setColor(sf::Color::Yellow);
            tak.setColor(sf::Color::White);
            break;
        }
    }



}
