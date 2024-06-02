#include "files_to_include.h"
#include "initialize_global_variables.h"

void setBGS(sf::Texture &editorBackgroundTexture, sf::Sprite &editorBackgroundSprite, sf::Texture &backgroundTexture, sf::Sprite &backgroundSprite, std::string a, std::string b){
        backgroundTexture.loadFromFile(a);
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(1920/2, 1080*1/3);
        backgroundSprite.setOrigin(backgroundTexture.getSize().x/2,backgroundTexture.getSize().y/2);

        editorBackgroundTexture.loadFromFile(b);
        editorBackgroundSprite.setTexture(editorBackgroundTexture);
        editorBackgroundSprite.setPosition(1920/2, 1080*1/3);
        editorBackgroundSprite.setOrigin(editorBackgroundTexture.getSize().x/2,editorBackgroundTexture.getSize().y/2);
    }

int main()
{
    sf::Texture editorBackgroundTexture;
    sf::Sprite editorBackgroundSprite;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;


    sf::Music music_battle;
    sf::Music music_title;
    sf::Music music_dialog;

    music_battle.setLoop(true);
    music_title.setLoop(true);
    music_dialog.setLoop(true);

    if (!music_battle.openFromFile("music/walka.wav")) {}
    if (!music_title.openFromFile("music/title.wav")) {}
    if (!music_dialog.openFromFile("music/tutorial.wav")) {}

    music_battle.setVolume(25);
    music_dialog.setVolume(25);
    music_title.setVolume(25);

// Statystyki i przyciski
    sf::Text statsText;
    statsText.setFont(font);
    statsText.setCharacterSize(24);
    statsText.setFillColor(sf::Color::White);

    try{
        if(!font.loadFromFile("font/font.ttf")){
            throw new GameException("Bład 000: Blad wczytywania czcionki");
        }
    }
    catch(GameException &e){
        e.what();
    }

    while(window.isOpen()){
        switch(state){
            case gamestate::menu:{

                /// tu bedzie menu
                music_title.play();
                Menu *menu = new Menu();
                menu->whileActive(window, state);
                delete menu;
                music_title.stop();
                break;
            }
            case gamestate::tutorial:{
                music_dialog.play();
                /// dialog wprowadzajacy
                source = "tutorial";
                kind = "tutorial_p1";
                Textbox *tutorial = new Textbox(font, kind, source);
                tutorial->whileActive(window);
                delete tutorial;

                /// kreator postaci
                music_dialog.stop();
                walka = battlestate::creator;
                Creating_Character* creator = new Creating_Character(window, font);
                handleCreation(window, player, creator, music_title, walka);
                delete creator;

                /// dialog przed walka
                music_dialog.play();
                kind = "tutorial_p2";
                tutorial = new Textbox(font, kind, source);
                tutorial->whileActive(window);
                delete tutorial;

                /// walka tutorialowa
                music_dialog.stop();

                setBGS(editorBackgroundTexture, editorBackgroundSprite, backgroundTexture, backgroundSprite, "textures/backgrounds/tutorial.png", "textures/backgrounds/edytor.png");

                walka = battlestate::battle;
                std::string source = "tutorial";
                std::string kind = "tutorial_battle";
                Battle* tutorialBattle = new Battle(player, font, kind, source, whichOne);
                initiateBattle(font, window, tutorialBattle, walka, music_battle, music_title, backgroundSprite, editorBackgroundSprite);
                delete tutorialBattle;

                /// dialog konczacy
                if (!music_dialog.openFromFile("music/tutorial_end.wav")) {}
                music_dialog.play();
                kind = "tutorial_p3";
                tutorial = new Textbox(font, kind, source);
                tutorial->whileActive(window);
                delete tutorial;
                state = gamestate::play;
                music_dialog.stop();
                break;
            }
            case gamestate::play:{
                /// dialog - 85%
                /// walka - 15%
                /// zwieksza sie o 10% z kazdym przejsciem poziomu
                std::cout << "steps = " << steps << std::endl;
                bool dialogUsed=false;
                if(steps != 5 and steps != 10){
                    if(rand()%100 <= procentWalka){ /// -------------------- walka
                        /// dzieje sie dialog
                        walka = battlestate::battle;
                        kind = "battle";
                        /*
                        while(dialogUsed){
                            isItHere(dialogUsed, battles, source, kind);
                        }
                        */
                        int which = rand()%3+1;
                        source = kind+patch::to_string(which);     /// tu zmienimy numerek w zaleznosci od tego ile dialogow bedzie
                        std::cout << source << std::endl;
                        for(int i=0;i<battles.size();i++){
                            if(battles[i] == source){
                                dialogUsed = true;
                                break;
                            }
                        }
                        if(!dialogUsed){
                            battles.push_back(source);


                            /// a potem dzieje sie walka

                            if(which == 3){
                                Textbox *dialog = new Textbox(font, source, kind);
                                dialog->whileActive(window);
                                delete dialog;
                                setBGS(editorBackgroundTexture, editorBackgroundSprite, backgroundTexture, backgroundSprite, "textures/backgrounds/backgroundkrokodyl.png", "textures/backgrounds/edytor.png");
                                std::string sciezka = "dialog/"+kind+"/"+source+"/"+kind+"/"+source+".txt";
                                Battle* battle = new Battle(player, sciezka, font, whichOne);
                                initiateBattle(font, window, battle, walka, music_battle, music_title, backgroundSprite, editorBackgroundSprite);
                                delete battle;
                            }
                            else{
                            Textbox *dialog = new Textbox(font, source, kind);
                            dialog->whileActive(window);
                            delete dialog;
                                setBGS(editorBackgroundTexture, editorBackgroundSprite, backgroundTexture, backgroundSprite, "textures/backgrounds/background.png", "textures/backgrounds/edytor.png");
                                Battle* battle = new Battle(player, font, source, kind, whichOne);
                                initiateBattle(font, window, battle, walka, music_battle, music_title, backgroundSprite, editorBackgroundSprite);
                                delete battle;
                            }
                            procentWalka = 15;
                        }
                    }
                    else{   ///--------------------------------------------- dialog
                        /// dzieje sie dialog
                        kind = "regular";
                        /*                                                          /// same dialogi chyba bez sensu
                        while(dialogUsed){                                          /// trzeba bedzie dodac specjalne eventy
                            isItHere(dialogUsed, dialogs, source, kind);            /// typu dostanie kasy, albo znalezienie itemu
                        }
                        */
                        int which = rand()%2+1;
                        source = kind+patch::to_string(which);     /// tu zmienimy numerek w zaleznosci od tego ile dialogow bedzie
                        std::cout << source << std::endl;
                        for(int i=0;i<dialogs.size();i++){
                            if(dialogs[i] == source){
                                dialogUsed = true;
                                break;
                            }
                        }
                        if(!dialogUsed){
                            dialogs.push_back(source);
                            Textbox *dialog = new Textbox(font, source, kind);
                            dialog->whileActive(window);
                            delete dialog;
                            procentWalka+=10;
                        }
                        if(which%2!=0){
                            saldo+=50;
                        }
                        procentWalka = 30;
                    }
                }

                switch(steps){
                    case 5:{
                        state = gamestate::specialFight;
                        break;
                    }
                    case 10:{
                        state = gamestate::shop;
                        break;
                    }
                    default:{
                        steps++;
                        break;
                    }
                }
                break;
            }
            case gamestate::specialFight:{
                int random = rand()%1+1;
                kind = "special_battle";
                Textbox *dialog;
                Battle *battle;
                walka = battlestate::battle;
                switch(random){
                    case 1:{        /// Pilski - agility
                        if (!music_battle.openFromFile("music/pilski_theme.wav")) {
                        }
                        music_battle.play();
                        /// dialog wprowadzajacy
                        source = "pilski";
                        Textbox *dialog = new Textbox(font, source, kind);
                        dialog->whileActive(window);
                        delete dialog;
                        /// walka
                        std::string zrodlo = "dialog/"+kind+"/"+source+"/"+kind+"/background/backg.png";
                        setBGS(editorBackgroundTexture, editorBackgroundSprite, backgroundTexture, backgroundSprite, zrodlo, "textures/backgrounds/edytor.png");

                        music_battle.stop();
                        battle = new Battle(player, font, source, kind, whichOne);
                        initiateBattle(font, window, battle, walka, music_battle, music_title, backgroundSprite, editorBackgroundSprite);

                        /// werbowanie sojusznika (dialog po walce jezeli przezyl)
                        if(battle->canBeRecruited){
                            whichOne = Sidekick::Pilski;
                            source = "pilski_after";
                            Textbox *dialog = new Textbox(font, source, kind);
                            dialog->whileActive(window);
                            delete dialog;
                        }
                        delete battle;
                        steps++;
                        state = gamestate::play;


                        if (!music_battle.openFromFile("music/walka.wav")) {}
                        procentWalka+=15;
                        break;
                    }
                    case 2:{        /// Rathki - atak
                        /// dialog wprowadzajacy
                        source = "rathki";
                        Textbox *dialog = new Textbox(font, source, kind);
                        dialog->whileActive(window);
                        delete dialog;
                        /// walka

                        /// werbowanie sojusznika (dialog po walce jezeli przezyl)
                        /*
                        if ( przeciwnik przegadany ){
                            whichOne = Sidekick::Rathki

                            source = "rathki_after";
                            dialog = new Textbox(font, source, kind);
                            dialog->whileActive(window);
                            delete dialog;
                        }
                        */
                        break;
                    }
                    case 3:{        /// Palace - charyzma
                        /// dialog wprowadzajacy
                        source = "palace";
                        Textbox *dialog = new Textbox(font, source, kind);
                        dialog->whileActive(window);
                        delete dialog;
                        /// walka

                        /// werbowanie sojusznika (dialog po walce jezeli przezyl)
                        /*
                        if ( przeciwnik przegadany ){
                            whichOne = Sidekick::Palace

                            source = "palace_after";
                            dialog = new Textbox(font, source, kind);
                            dialog->whileActive(window);
                            delete dialog;
                        }
                        */
                        break;
                    }
                    case 4:{        ///Size - hp
                        /// dialog wprowadzajacy
                        source = "size";
                        Textbox *dialog = new Textbox(font, source, kind);
                        dialog->whileActive(window);
                        delete dialog;
                        /// walka

                        /// werbowanie sojusznika (dialog po walce jezeli przezyl)
                        /*
                        if ( przeciwnik przegadany ){
                            whichOne = Sidekick::Size

                            source = "size_after";
                            dialog = new Textbox(font, source, kind);
                            dialog->whileActive(window);
                            delete dialog;
                        }
                        */
                        break;
                    }
                }
                /// mozemy zrobic if / switch w walce zalezny od Sidekick
                /// zeby w zaleznosci od tego kogo odblokowales, pozwalal
                /// ci na jakas akcje np. atak albo boost do jakiegos statu

                break;
            }
            case gamestate::shop:{
                std::cout << saldo << std::endl;
                shopstate stanSklepu = shopstate::limbo;

                Sklep* shop = new Sklep(font, saldo);
                ShopMenu* menuSklepu = new ShopMenu(font);
                ClerkDialog* cDial = new ClerkDialog(font);

                HandleShop(player, window, font, shop, menuSklepu, cDial, stanSklepu);

                delete shop;
                delete menuSklepu;
                delete cDial;
                state = gamestate::finalBoss;

                break;
            }

            case gamestate::finalBoss:{
                walka = battlestate::battle;
                /// dialog z bossem
                kind = "boss_battle";
                source = "boss";
                //Textbox *dialog = new Textbox(font, source, kind);
                //dialog->whileActive(window);
                //delete dialog;

                /// walka
                Battle* boss = new Battle(player, "dialog/boss_battle/boss/boss.txt", font, true, whichOne);
                setBGS(editorBackgroundTexture, editorBackgroundSprite, backgroundTexture, backgroundSprite,"textures/backgrounds/background.png" , "textures/backgrounds/edytor.png");
                initiateBattle(font, window, boss, walka, music_battle, music_title, backgroundSprite, editorBackgroundSprite);
                delete boss;

                /*
                /// cutscenka po walce
                source = "boss_after";
                dialog = new Textbox(font, source, kind);
                dialog->whileActive(window);
                delete dialog;
                */
                state = gamestate::menu;
                break;
            }
            case gamestate::ending:{
                /// ending i creditsy
                sf::Text ending("Wygrales!", font, 50);
                ending.setPosition(1920.f/2, 1080.f/3);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    state = gamestate::menu;
                    break;
                }
                else{
                    window.draw(ending);
                }
            }
        }
    }

    return 0;
}
