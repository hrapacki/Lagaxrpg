//
// Created by Hubert on 25.05.2023.
//

#ifndef UNTITLED_BATTLE_H
#define UNTITLED_BATTLE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include "Character.h"
#include "to_string.h"
#include "sidekick.h"

class PlayerCharacter : public Character {
public:

    PlayerCharacter(float x, float y,
                    const std::string &texturePath,
                    const std::string &defenseTexturePath,
                    const std::string &deadTexturePath,
                    int health, int charisma,
                    int strength, int agility, int vigor)
            : Character(x, y, texturePath, defenseTexturePath, deadTexturePath, health, charisma, strength, agility, vigor),
              level(1), exp(0) {
        // Konstruktor
    }

    void gainExp(int amount) {
        exp += amount;
        if (exp >= (level+3)*50) {
            levelUp();
        }
    }

    int getLevel() const {
        return level;
    }

    int getExp() const {
        return exp;
    }
    bool getLeveluptime(){
        return leveluptime;
    }
    void setLeveluptime(){
        leveluptime = false;
    }
private:
    void levelUp() {
        leveluptime=true;
        cout << "Level up!" << endl;
        exp = exp - (level+3)*50;
        level++;
    }
    bool leveluptime=false;
    int level;
    int exp;
};

class Battle{
public:
    bool canBeRecruited = false;
    int random() {
        int ran = rand() % 20 + 1;

        return ran;
    }
    void draw(sf::RenderWindow & window) {
        window.draw(opcja1);
        window.draw(opcja2);
    }
    PlayerCharacter *player;
    vector<std::shared_ptr<Character>> enemies;
    bool playerActed=false;
    std::vector < Character * > characters;
    sf::Font font;
    sf::Text opcja1;
    sf::Text opcja2;
    Sidekick whichOne;
    std::string currentBattleState;
    bool allyUsed = false;
    Battle(){}
    Battle(PlayerCharacter* currentplayer, sf::Font &font, std::string &a, std::string &b, Sidekick &c):player(currentplayer),font(font), currentBattleState(b), whichOne(c){
        opcja1.setFont(font);
        opcja1.setCharacterSize(30);
        if(whichOne == Sidekick::none){
            opcja1.setString("1. Zaatakuj\n2. Obrona\n3. Przekonaj wroga do ucieczki");
        }
        else{
            opcja1.setString("1. Zaatakuj\n2. Obrona\n3. Przekonaj wroga do ucieczki\n4. Umiejetnosc sojusznika");
        }



        opcja2.setFont(font);
        opcja2.setCharacterSize(30);
        opcja2.setString(" ");

        opcja1.setPosition(sf::Vector2f((1920-1920/1.6)/2, (1080-1080/2.6) +1*(1920+1080)/75));
        opcja2.setPosition(sf::Vector2f((1920-1920/1.6)/2 + 800, (1080-1080/2.6) +1*(1920+1080)/75));

        int PlayerCharisma;
        int PlayerStrength;
        int PlayerVigor;
        int PlayerAgility;
        ifstream statsload("data/playerstats.txt");
        statsload.close();
        statsload.clear();
        string plik = "dialog/"+b+"/"+a+"/"+b+"/"+a+".txt";
        statsload.open(plik);
        int howManyLines = 0;
        std::string dummy;
        while(getline(statsload, dummy)){
            howManyLines++;
        }
        statsload.close();
        statsload.open(plik);
        for(int i=0; i<howManyLines; i++){
            int cordX;
            int cordY;
            int hp;
            string texture;
            string defence;
            string death;
            statsload >> cordX >> cordY >> texture >> defence >> death >> hp >> PlayerCharisma >> PlayerStrength >> PlayerAgility >> PlayerVigor;
            enemies.push_back(make_shared<Character>(cordX, cordY, texture, defence, death, hp, PlayerCharisma, PlayerStrength, PlayerAgility, PlayerVigor));
            if(hp == 1){
                isTutorial = true;
            }
        }
        characters=prepareCharacters();
        isabossfight=false;
    }
    Battle(PlayerCharacter *currentplayer, const std::string &bossFile, sf::Font &font, Sidekick &c) : player(currentplayer),font(font) {
        opcja1.setFont(font);
        opcja1.setCharacterSize(30);
        opcja1.setString("1. Zaatakuj\n2. Obrona\n3. Przekonaj wroga do ucieczki");

        opcja2.setFont(font);
        opcja2.setCharacterSize(30);
        opcja2.setString(" ");

        opcja1.setPosition(sf::Vector2f((1920-1920/1.6)/2, (1080-1080/2.6) +1*(1920+1080)/75));
        opcja2.setPosition(sf::Vector2f((1920-1920/1.6)/2 + 800, (1080-1080/2.6) +1*(1920+1080)/75));
        int PlayerCharisma;
        int PlayerStrength;
        int PlayerVigor;
        int PlayerAgility;
        ifstream statsload("stats/playerstats.txt");
        statsload.close();
        statsload.clear();

        statsload.open(bossFile);
        int cordX;
        int cordY;
        int hp;
        string texture;
        string defence;
        string death;
        string secondphase;
        statsload >> cordX >> cordY >> texture >> defence >> secondphase >>death >> hp >> PlayerCharisma >> PlayerStrength >> PlayerAgility >> PlayerVigor;
        enemies.push_back(make_shared<BossCharacter>(cordX, cordY, texture, secondphase, defence, death, hp, PlayerCharisma, PlayerStrength, PlayerAgility, PlayerVigor));

        characters=prepareCharacters();
        isabossfight=true;

    }
    Battle(PlayerCharacter *currentplayer, const std::string &bossFile,sf::Font &font,bool ending, Sidekick &c) : player(currentplayer),font(font) {
        opcja1.setFont(font);
        opcja1.setCharacterSize(30);
        opcja1.setString("1. Zaatakuj\n2. Obrona\n3. Przekonaj wroga do ucieczki");

        opcja2.setFont(font);
        opcja2.setCharacterSize(30);
        opcja2.setString(" ");

        opcja1.setPosition(sf::Vector2f((1920-1920/1.6)/2, (1080-1080/2.6) +1*(1920+1080)/75));
        opcja2.setPosition(sf::Vector2f((1920-1920/1.6)/2 + 800, (1080-1080/2.6) +1*(1920+1080)/75));
        int PlayerCharisma;
        int PlayerStrength;
        int PlayerVigor;
        int PlayerAgility;
        ifstream statsload("stats/playerstats.txt");
        statsload.close();
        statsload.clear();

        statsload.open(bossFile);
        int cordX;
        int cordY;
        int hp;
        string texture;
        string defence;
        string death;
        string secondphase;
        string card1,card2,card3,card4;
        statsload >> cordX >> cordY >> texture >> defence >> secondphase >>card1>>card2>>card3>>card4>>death >> hp >> PlayerCharisma >> PlayerStrength >> PlayerAgility >> PlayerVigor;
        enemies.push_back(make_shared<TarotBoss>(cordX, cordY, texture, defence,death,card1,card2,card3,card4,secondphase,hp, PlayerCharisma, PlayerStrength, PlayerAgility, PlayerVigor));
        characters=prepareCharacters();
        isabossfight=true;
    }
    void handleKeyPress(const sf::Event & event) {
        static bool attackSelected = false;
        static bool cancelSelected = false;
        int i = 0;
        if (event.type == sf::Event::KeyPressed) {
            for (const auto& enemy : enemies) {
                if (enemy->isAlive()) {
                    i++;
                    cout << i << endl;
                }
            }
            if(i == 0 && !isBattleOver){
                isBattleOver = true;
            }

            if (isBattleOver) {

                if (event.key.code == sf::Keyboard::Z) {
                    levelcleared = true;
                    std::cout << "Przechodzisz do następnego poziomu!" << std::endl;
                }
                return;
            }
            if (attackSelected && !cancelSelected) {
                if (event.key.code == sf::Keyboard::X) {
                    attackSelected = false;
                    cancelSelected = true;
                    opcja2.setString(" ");
                    return;
                }
            }
            if (attackSelected) {
                cancelSelected = false;
                int enemyIndex = -1;
                if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                    enemyIndex = 0;
                } else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                    enemyIndex = 1;
                } else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                    enemyIndex = 2;
                }

                if (enemyIndex >= 0 && enemyIndex < enemies.size() && enemies[enemyIndex] -> isAlive()) {
                    int damage = player->attack( * enemies[enemyIndex]);
                    playerActed = true;
                    attackSelected = false;
                    // Wy³¹czamy tryb obrony
                    player->setDefenseMode(false);
                    if (damage > 0) {
                        std::cout << "Zadales " << damage << " obrazen przeciwnikowi " << (enemyIndex + 1) << "!" << std::endl;
                    }

                } else {
                    std::cout << "Ten przeciwnik juz nie zyje." << std::endl;
                }


            } else {
                if (!attackSelected) {

                    if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                        // Gracz wybra³ atak
                        attackSelected = true;
                        std::string nowy = "";
                        for (int i = 0; i < enemies.size(); i++) {
                            if (enemies[i]->isAlive()) {
                                nowy += patch::to_string(i + 1) + ". Przeciwnik " + patch::to_string(i + 1) + ". Zdrowie: " + patch::to_string(enemies[i]->getHealth())+"\n";
                            } else {
                                nowy+="Przeciwnik " + patch::to_string(i + 1) + " jest martwy." + "\n";
                            }
                        }
                        opcja2.setString(nowy);

                    } else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                        // Gracz wybra³ obronê
                        player->setDefenseMode(true);
                        playerActed = true;
                    }
                    else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                        player->setDefenseMode(false);
                        if(!isabossfight){
                            player->setDefenseMode(false);
                            int surrenderProbabilityBase = 5;  // Bazowa szansa na poddanie siê
                            int charismaBonus = player->getCharisma();  // Bonus od charyzmy gracza
                            int deadEnemiesBonus = 0;
                            for (const auto& enemy : enemies) {
                                if (!enemy->isAlive()) {
                                    deadEnemiesBonus += 10;  // Bonus za ka¿dego martwego przeciwnika
                                }
                            }
                            int surrenderProbability = surrenderProbabilityBase + charismaBonus + deadEnemiesBonus;
                            if (rand() % 100 < surrenderProbability) {
                                if(currentBattleState == "special_battle"){
                                    canBeRecruited = true;
                                }

                                std::cout << "Przeciwnicy uciekaja!" << endl;
                                for (const auto& enemy : enemies) {
                                    if (enemy->isAlive()) {
                                        enemy->receiveDamage(enemy->getHealth());  // Zabij przeciwników, którzy siê poddali
                                    }
                                }
                            } else {
                                std::cout << "nie udalo sie przekonac przeciwnikow"<< endl;
                            }
                            if(!isTutorial){
                                playerActed = true;
                            }

                        }
                        else{
                            cout << "Ten przeciwnik nie boi sie Ciebie i nie zamierza uciekac" << endl;
                            playerActed = true;}
                    }
                    else if(event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4){
                        if(whichOne == Sidekick::Pilski and !allyUsed){
                            player->setAgility(player->getAgility()+5);
                            allyUsed = true;
                        }
                        std::cout << player->getAgility() << std::endl;
                    }
                }
            }
        }
        if(!player->isAlive()){
            resetBattle();
        }
    }

    int getEnemyNumber(const Character * enemy) {
        for (size_t i = 0; i < enemies.size(); ++i) {
            if (enemies[i].get() == enemy) {
                return i + 1;
            }
        }
        return -1;
    }
    void enemyAI() {
        if (playerActed) {
            opcja2.setString(" ");
            for (size_t i = 0; i < enemies.size(); ++i) {
                auto & enemy = enemies[i];
                if (enemy -> isAlive()) {
                    if(auto* boss = dynamic_cast<TarotBoss*>(enemy.get())) {

                        boss->drawCard();
                        if(boss->coins){
                            int damage = enemy->attack(*player);
                            cout << damage << endl;
                            enemy->setDefenecounter(0);
                            enemy->mustattack = false;
                            if (!player->getDefenseMode()) {
                                std::cout << "Przeciwnik " << (i + 1) << " zaatakowal i zadal " << damage << " obrazen."
                                          << std::endl;
                            } else {
                                std::cout << "Gracz obronil sie przed atakiem przeciwnika " << (i + 1) << "."
                                          << std::endl;
                            }
                            boss->coins=false;
                        }
                    }

                    int counter = enemy->getDefenseCounter();
                    enemy->setDefenseMode(false);
                    enemy->setDefenecounter(counter);
                    int healthPercentage = static_cast < int > ((static_cast < float > (enemy -> getHealth()) / enemy -> getMaxHealth()) * 100);

                    int defenseProbability = 0;

                    if (healthPercentage < 70) {
                        defenseProbability = 70 - healthPercentage;
                    }
                    if(enemy->isboss&&enemy->getHealth() < enemy->getMaxHealth() * 0.6){
                        enemy-> chargeattack();
                        enemy->setDefenecounter(0);
                    }
                    if(enemy->skipturn==false){
                        int randomAction = rand() % 100;

                        bool shouldDefend = randomAction < defenseProbability ;
                        if (shouldDefend && enemy->getDefenseCounter() < 2 && enemy->mustattack==false) {
                            enemy->setDefenseMode(shouldDefend);
                            std::cout << "Przeciwnik " << (i + 1) << " broni sie." << std::endl;
                        } else {
                            int damage = enemy->attack(*player);
                            cout << damage << endl;
                            enemy->setDefenecounter(0);
                            enemy->mustattack = false;
                            if (!player->getDefenseMode()) {
                                std::cout << "Przeciwnik " << (i + 1) << " zaatakowal i zadal " << damage << " obrazen."
                                          << std::endl;
                            } else {
                                std::cout << "Gracz obronil sie przed atakiem przeciwnika " << (i + 1) << "."
                                          << std::endl;
                            }
                        }
                    }


                } else {
                    enemy -> setDeadSprite();
                }
            }
            playerActed = false;
            printStats();
        }
    }
    void printStats() {
        std::cout << "Gracz: " << player->getHealth() << " HP\n";
        for (size_t i = 0; i < enemies.size(); ++i) {
            std::cout << "Przeciwnik " << (i + 1) << ": " << enemies[i] -> getHealth() << " HP\n";
        }
        std::cout << "----------------------\n";
    }
    std::vector < Character * > prepareCharacters() {
        std::vector < Character * > characters;
        characters.push_back(player);
        for (const auto & enemy: enemies) {
            characters.push_back(enemy.get());
        }
        return characters;
    }
    bool isTutorial = false;

    void resetBattle() {
        for (Character* character : characters) {
            character->returnfullhp();
            character->restart=true;
        }
        // Przywrócenie porz¹dku postaci
        characters = prepareCharacters();
    }

    void performTurns(sf::RenderWindow& window) {

        bool enemyActed = false;

        for (Character* character : characters) {
            if (character != player) {
                // AI przeciwnika
                if (!enemyActed) {
                    enemyAI();
                    enemyActed = true;
                }
            } else {
                if (playerActed) {
                    enemyActed = false;
                }
            }
        }
    }
    bool isabossfight=false;
    bool levelcleared=false;
    bool isBattleOver = false;
    bool allEnemiesDefeated() {
        if(!levelcleared){
            for (const auto& enemy : enemies) {
                if (enemy->isAlive()) {
                    return false;
                }
            }}
        else{
            awardExp(player, enemies.size() * 50);
            if(isabossfight){
                cout << "otrzymujesz 200" << "xp!" << endl;
            }
            else{
                cout << "otrzymujesz " << enemies.size() * 50 << "xp!" << endl;}
            levelcleared=false;
            isBattleOver = false;
            return true;}
    }
    void awardExp(PlayerCharacter *player, int amount) {
        if(allyUsed == true){
            player->setAgility(player->getAgility()-5);
        }
        if(isabossfight){
            player->gainExp(amount*4);
        }
        else{
            player->gainExp(amount);}


    }
};


#endif //UNTITLED_BATTLE_H
