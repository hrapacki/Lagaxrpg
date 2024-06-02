#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "game_exception.h"
Menu::Menu()
{
    try{
        if(!font.loadFromFile("font/font.ttf")){
            throw new GameException("B³ad 000: Blad wczytywania czcionki ");
        }

        if(!bgTexture.loadFromFile("textures/menu/lagaxx.png")){
            throw new GameException("Blad 001: Blad wczytywania tekstury ");
        }
    }
    catch(GameException &e){
        e.what();
    }

    play.setString("PLAY");
    exit.setString("EXIT");
    play.setFont(font);
    exit.setFont(font);
    play.setColor(sf::Color::Yellow);
    exit.setColor(sf::Color::White);
    play.setPosition(810.f, 810.f);
    exit.setPosition(play.getPosition().x+250, 810.f);
    whichOption=true;

    credits.setString("stworzone przez: Huberta Rapackiego i Bartka Rakowskiego");
    credits.setFont(font);
    credits.setCharacterSize(15);


    bgSprite.setTexture(bgTexture);
    bgSprite.setOrigin(bgTexture.getSize().x/2, bgTexture.getSize().y/2);
    bgSprite.setPosition(1920/2, 1080/3);
}

Menu::~Menu()
{
}

sf::Text Menu::getPlay(){
    return play;
}

sf::Text Menu::getExit(){
    return exit;
}

void Menu::setChoice(){
    whichOption = !whichOption;
}

void Menu::setColors(){
    if(whichOption){
        play.setColor(sf::Color::Yellow);
        exit.setColor(sf::Color::White);
    }
    else{
        play.setColor(sf::Color::White);
        exit.setColor(sf::Color::Yellow);
    }
}

bool Menu::getChoice(){
    return whichOption;
}

void Menu::handleKeyPress(sf::RenderWindow &window, gamestate &state){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
    }
    if(state == gamestate::menu){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            setChoice();
            ///std::cout << menu.getChoice() << std::endl;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            switch(getChoice()){
                case 0:{
                    window.close();
                    break;
                }
                case 1:{
                    state = gamestate::tutorial;
                    break;
                }
            }
        }
    }
}

void Menu::whileActive(sf::RenderWindow &window, gamestate &state){
    while (window.isOpen())
    {
        setColors();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:{
                    window.close();
                    break;
                }
                case sf::Event::TextEntered:{   ///tu chodzi o to ze jak piszesz cos na klawiaturze, to zapisze ci sie to w konsoli a nie w oknie gry
                    if(event.text.unicode<128){
                        printf("%c", event.text.unicode);
                    }
                    break;
                }
                case sf::Event::KeyPressed:{
                    handleKeyPress(window, state);
                    break;
                }
            }
        }

        window.clear();
        switch(state){
            case gamestate::menu:{
                window.draw(bgSprite);
                window.draw(getPlay());
                window.draw(getExit());
                window.draw(credits);
                break;
            }
            default:{
                return;
            }
        }

        window.display();
    }
}
