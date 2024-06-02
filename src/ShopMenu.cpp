#include "ShopMenu.h"
#include "SFML/Graphics.hpp"
#include "choice.h"
#include "shopstate.h"
#include <iostream>

ShopMenu::ShopMenu(sf::Font &font)
{
    std::cout << "menu sie zbudowalo :D" << std::endl;

    talk.setString("* Porozmawiaj");
    talk.setFont(font);
    talk.setCharacterSize(30);

    buy.setString("* Kupuj");
    buy.setFont(font);
    buy.setCharacterSize(30);

    exit.setString("* Wyjdz");
    exit.setFont(font);
    exit.setCharacterSize(30);

    talk.setPosition(sf::Vector2f((1920-1920/1.6)/2, (1080-1080/2.6)));
    buy.setPosition((1920-1920/1.6)/2, (1920+1080)/75+(1080-1080/2.6));
    exit.setPosition((1920-1920/1.6)/2, (1920+1080)/37.5+(1080-1080/2.6));
}

ShopMenu::~ShopMenu()
{
    std::cout << "menu sie zniszczylo :(" << std::endl;
}

void ShopMenu::handleKeyPressMenu(shopstate &state){
    {
        switch(choice){
            case Choice::first:{
                if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ){
                    choice = Choice::third;
                }
                else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ){
                    choice = Choice::second;
                }
                break;
            }
            case Choice::second:{
                if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ){
                    choice = Choice::first;
                }
                else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ){
                    choice = Choice::third;
                }
                break;
            }
            case Choice::third:{
                if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ){
                    choice = Choice::second;
                }
                else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ){
                    choice = Choice::first;
                }
                break;
            }
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
        switch(choice){
            case Choice::first:{
                state = shopstate::talk;
                break;
            }
            case Choice::second:{
                state = shopstate::shop;
                break;
            }
            case Choice::third:{
                state = shopstate::exit;
                break;
            }
        }
    }
}

void ShopMenu::setActive()
{
    switch(choice){
        case Choice::first:{
            talk.setColor(sf::Color::Yellow);
            buy.setColor(sf::Color::White);
            exit.setColor(sf::Color::White);
            break;
        }
        case Choice::second:{
            talk.setColor(sf::Color::White);
            buy.setColor(sf::Color::Yellow);
            exit.setColor(sf::Color::White);
            break;
        }
        case Choice::third:{
            talk.setColor(sf::Color::White);
            buy.setColor(sf::Color::White);
            exit.setColor(sf::Color::Yellow);
            break;
        }
    }
}

void ShopMenu::drawAll(sf::RenderWindow &window)
{
    window.draw(talk);
    window.draw(buy);
    window.draw(exit);
}
