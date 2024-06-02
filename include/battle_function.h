#ifndef BATTLE_FUNCTION_H_INCLUDED
#define BATTLE_FUNCTION_H_INCLUDED

#include "to_string.h"
int pointskept = 0;
void initiateBattle(sf::Font &font, sf::RenderWindow &window, Battle* &test, battlestate &state, sf::Music &music_battle, sf::Music &music_title, sf::Sprite &backgroundSprite, sf::Sprite &editorBackgroundSprite){
while (window.isOpen()) {
    if (state == battlestate::battle) {
        if (music_battle.getStatus() != sf::Music::Playing) {
            music_battle.play();
        }
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            test->handleKeyPress(event);
        }
        window.clear();
        sf::Text koniec;
        koniec.setFont(font);
        koniec.setCharacterSize(30);
        koniec.setPosition(sf::Vector2f(1920/2, (1080-1080/2.6) +1*(1920+1080)/75));
        if(test->isBattleOver){
            music_battle.stop();
            if(test->isTutorial){
                koniec.setString("Wygrales, otrzymujesz 0xp!\nAby przejsc dalej, nacisnij Z");
                window.draw(koniec);
            }
            else{
                std::string inKoniec = "Wygrales, otrzymujesz "+patch::to_string(test->enemies.size() * 50)+"xp!\nAby przejsc dalej, nacisnij Z";
                koniec.setString(inKoniec);
                window.draw(koniec);
            }
        }
        else{
            test -> draw(window);
        }


        test->performTurns(window);
        window.draw(backgroundSprite);
        if (test->allEnemiesDefeated()){


            test->player->updateHealth();
            test->enemies.clear();

            if(test->player->getLeveluptime()==true){
                cout << "level up time" << endl;
                state = battlestate::levelup;
                music_battle.stop();
            }
            else{
                cout << "switched to travel" << endl;
                state = battlestate::travel;
                music_battle.stop();
            }

            }

        test->player->draw(window);
        for (auto & enemy: test->enemies) {
            enemy -> draw(window);
        }
            window.display();
        }
        else if (state == battlestate::travel) {
            test->player->returnfullhp();

            return;
        }
        else if(state == battlestate::levelup) {
            if (music_title.getStatus() != sf::Music::Playing) {
                music_title.play();
            }
            LevelUp_Character levelUpCharacter(window, font, test->player->getCharisma(), test->player->getVigor(), test->player->getAgility(), test->player->getStrength(), 2+pointskept);
            while (!levelUpCharacter.isFinished()) {
                window.clear();
                window.draw(editorBackgroundSprite);
                levelUpCharacter.handleEvents();
                levelUpCharacter.draw();
                window.display();
                sf::sleep(sf::milliseconds(100));
            }

            test->player->setVigor(levelUpCharacter.getVigor());
            test->player->setAgility(levelUpCharacter.getAgility());
            test->player->setCharisma(levelUpCharacter.getCharisma());
            test->player->setStrength(levelUpCharacter.getStrength());
            test->player->updateHealth();
            std::fstream stats("data/playerstats.txt", std::ios::out|std::ios::trunc);
            stats<<levelUpCharacter.getCharisma()<<endl<<levelUpCharacter.getStrength()<<endl<<levelUpCharacter.getAgility()<<endl<<levelUpCharacter.getVigor()<<endl;
            stats.close();

            pointskept = levelUpCharacter.getRemainingPoints();
            test->player->returnfullhp();
            test->player->setLeveluptime();
            state = battlestate::travel;
            music_title.stop();
        }
    }
}

#endif // BATTLE_FUNCTION_H_INCLUDED
