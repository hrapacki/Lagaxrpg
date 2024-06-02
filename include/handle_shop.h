#ifndef HANDLE_SHOP_H_INCLUDED
#define HANDLE_SHOP_H_INCLUDED

#include "Character.h"
#include "Battle.h"

void HandleShop(PlayerCharacter *&player, sf::RenderWindow & window, sf::Font &font, Sklep* &a, ShopMenu* &menu, ClerkDialog* &cDial, shopstate &state){
    while (window.isOpen())
    {
        a->setActive();
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
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                        window.close();
                    }
                    switch(state){
                        case shopstate::limbo:{
                            menu->handleKeyPressMenu(state);
                            break;
                        }
                        case shopstate::talk:{
                            cDial->handleKeyPressClerk(state);
                            break;
                        }
                        case shopstate::shop:{
                            a->handleKeyPressShop(state, player);
                            break;
                        }
                        default:{
                            break;
                        }
                    }

                    //std::cout << "choice = " << choice << std::endl;
                    std::cout << "obecne saldo: " << a->getSaldo() << std::endl;
                    std::cout << "isBought =  " << a->isBought() << std::endl;
                    std::cout << "enoughMoney = " << a->enoughMoney() << std::endl;
                    std::cout << "saldo po zakupie: " << a->getSaldo()-50 << std::endl;
                    std::cout << "----------------------------------------------" << std::endl;
                    break;
                }
            }

        }
        //animation.update(0, deltaTime);                                     ///to koniecznie poza while(window.pollEvent(event)), bo nie bedzie sie wykonywac
        //player.setTextureRect(animation.uvRect);

        window.clear();

        window.draw(a->box);
        window.draw(a->backg);
        window.draw(a->clerkS);

        switch(state){
            case shopstate::shop:{
                window.draw(a->currentS(font));
                for(size_t i=0;i<a->getIle();i++){
                    window.draw(a->getString(i));
                }
                if(a->confirm){
                    std::string app = a->getString(a->choice-1).getString();
                    a->uSure.setString("Chcesz kupic "+app+"?");
                    /*
                    ///opcjonalne ----------------------------------------------
                    switch(a->choice){
                        case 1:{
                            a->setClerkS("textures/shop/clerkChoice1.png");
                            break;
                        }
                        case 2:{
                            a->setClerkS("textures/shop/clerkChoice2.png");
                            break;
                        }
                        case 3:{
                            a->setClerkS("textures/shop/clerkChoice3.png");
                            break;
                        }
                    }
                    ///---------------------------------------------------------
                    */
                    a->toggleChoice();

                    window.draw(a->uSure);
                    window.draw(a->tak);
                    window.draw(a->nie);
                }
                else{
                    if(!a->enoughMoney()){
                        a->uSure.setString("nie masz wystaczajaco\npieniedzy");
                        window.draw(a->uSure);
                        a->setClerkS("textures/shop/clerkNoCash.png");
                    }
                    else{
                        a->setClerkS("textures/shop/clerkIdle.png");
                    }
                }
                break;
            }
            case shopstate::limbo:{
                a->setClerkS("textures/shop/clerkIdle.png");
                menu->setActive();
                menu->drawAll(window);
                break;
            }
            case shopstate::talk:{
                window.draw(cDial->txt.update());
                break;
            }
            case shopstate::exit:{
                std::cout << player->getCharisma() << std::endl;        ///po to zeby sprawdzic czy dziala zmiana statystyk
                return;
            }
        }
        window.display();
    }
}

#endif // HANDLE_SHOP_H_INCLUDED
