//
// Created by Hubert on 25.05.2023.
//

#ifndef UNTITLED_CHARACTER_H
#define UNTITLED_CHARACTER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;



class Character {
public:      Character(float x, float y,
                       const std::string &texturePath,
                       const std::string &defenseTexturePath,
                       const std::string &deadTexturePath,
                       int health, int charisma,
                       int strength, int agility, int vigor)
            : vigor(vigor),
              health(health + 10 * vigor),
              defenseMode(false),
              charisma(charisma),
              strength(strength),
              agility(agility),
              maxhealth(health + 10 * vigor) {
        hptoreturn=maxhealth;
        texture.loadFromFile(texturePath);
        defenseTexture.loadFromFile(defenseTexturePath);
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        defenseSprite.setTexture(defenseTexture);
        defenseSprite.setPosition(x, y);

        deadTexture.loadFromFile(deadTexturePath);
        deadSprite.setTexture(deadTexture);
        deadSprite.setPosition(x, y);


        healthBarBackground.setSize(sf::Vector2f(50, 5));
        healthBarBackground.setFillColor(sf::Color::Red);
        healthBarBackground.setPosition(x+25, y - 10);


        healthBar.setSize(sf::Vector2f(50, 5));
        healthBar.setFillColor(sf::Color::Green);
        healthBar.setPosition(x+25, y - 10);

if(texturePath=="textures/dummy_idle.png"){
    isTargetDummy=true;
}
if(texturePath=="textures/player.png"){
    isPlayer=true;
}
    }
    bool isPlayer=false;
    bool isTargetDummy=false;
    bool isboss = false;
    int hptoreturn;
    int random() {
        int ran = rand() % 20 + 1;

        return ran;
    }
    Character(){}
    void updateHealth(){
        maxhealth=health + 10 * vigor;
        health = maxhealth;
    }
    void returnfullhp(){
        health=hptoreturn;
        maxhealth=hptoreturn;
        updateHealthBar();
    }
    int getCharisma() const {
        return charisma;
    }
    bool restart = false;
    virtual void draw(sf::RenderWindow & window) {
        if(restart){
            defenseMode=false;
            window.draw(sprite);
            restart=false;
        }
        if (defenseMode) {
            window.draw(defenseSprite);
        } else {
            if(isAlive()){
            window.draw(sprite);}
            else{
                window.draw(grave);
            }
        }
        window.draw(healthBarBackground);
        window.draw(healthBar);
    }

    void setDefenseMode(bool defense) {
        defenseMode = defense;
        if (defenseMode) {
            defenseCounter++;
        } else {
            defenseCounter = 0;
        }
        if(isTargetDummy){
            defenseMode=false;
        }
    }
    void setDefenecounter(int number){
        defenseCounter = number;
    }
    virtual void chargeattack() { }
    int getDefenseCounter() const {
        return defenseCounter;
    }
    virtual void receiveDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
        updateHealthBar();
    }

    void updateHealthBar() {
        float healthPercentage = static_cast < float > (health) / maxhealth;
        healthBar.setSize(sf::Vector2f(50 * healthPercentage, 5));
    }

    bool isAlive() const {
        return health > 0;
    }
    void setDeadSprite() {
        grave = deadSprite;
    }
    bool setisboss(){
        if(isboss==true){
            isboss=false;
        }
        else{
            isboss=true;
        }
    }


    int calculateDamage(int baseDamage) {
        int damage = baseDamage + strength;

        // Oblicz szanse na critical hit
        int criticalHitChance = 10 + agility;
        int randomCriticalHit = rand() % 100;

        if (randomCriticalHit < criticalHitChance) {
            damage = static_cast<int>(damage * 1.5); // 50% więcej obrażeń
            cout << "Udalo Ci sie zadac cios krytyczny!" << endl;
        }

        // Oblicz szanse na unikniecie ataku

        int dodgeChance = 5 + agility;
        int randomDodge = rand() % 100;
        if(isTargetDummy){
            dodgeChance=0;
        }
        if (randomDodge < dodgeChance) {
            damage = 0;
            if(isPlayer){
                cout << "Uniknales ataku!" << endl;
            }
            else{
            cout << "Przeciwnik uniknal ataku!" << endl;}
        }

        return damage;
    }
    virtual int attack(Character &target) {
        if(isTargetDummy){
            cout << "Twoj niesamowity przeciwnik czeka na twoj kolejny ruch" << endl;
            return 0;
        }
        else{
        int baseDamage = random();
        int damage;
        damage = calculateDamage(baseDamage);
        if (!target.defenseMode) {
            target.receiveDamage(damage);
        }
        return damage;}
    }
    bool getDefenseMode() const {
        return defenseMode;
    }
    int getHealth() const {
        return health;
    }
    int getMaxHealth() const {
        return maxhealth;
    }
    void setCharisma(int value) {
        charisma = value;
    }

    void setStrength(int value) {
        strength = value;
    }

    void setAgility(int value) {
        agility = value;
    }

    void setVigor(int value) {
        vigor = value;
        maxhealth = 400 + vigor * 10;
        health = maxhealth;
        hptoreturn = maxhealth;
    }
    int getVigor(){
    return vigor;
}
    int getAgility(){
        return agility;
    }
    int getStrength(){
        return strength;
    }
    void setDefaultSprite() {
        sprite.setTexture(texture);
    }
    bool skipturn=false;
    bool mustattack=false;

protected: sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBackground;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Sprite grave;
    sf::Texture defenseTexture;
    sf::Sprite defenseSprite;
    sf::Texture deadTexture;
    sf::Sprite deadSprite;
    int maxhealth;
    int health;
    int defenseCounter = 0;
    bool defenseMode;
    int charisma;
    int strength;
    int agility;
    int vigor;


    sf::Clock defenseClock;
};

class BossCharacter : public Character {
public:

    bool isCharging;
    bool hasActed;
    int turnsToCharge;
    BossCharacter(float x, float y,
                  const std::string &texturePath,
                  const std::string &chargedTexturePath,
                  const std::string &defenseTexturePath,
                  const std::string &deadTexturePath,
                  int health, int charisma,
                  int strength, int agility, int vigor)
            : Character(x, y, texturePath, defenseTexturePath, deadTexturePath, health, charisma, strength, agility, vigor),
              chargedTexturePath(chargedTexturePath), isCharging(false), hasActed(false), turnsToCharge(4) {
        chargedTexture.loadFromFile(chargedTexturePath);
        chargedSprite.setTexture(chargedTexture);
        chargedSprite.setPosition(x, y);
        setisboss();
        basic=sprite;
    }

    virtual int attack(Character& target) override {
        cout << "wykonano" << endl;
        if (isCharging) {
            sprite=basic;
            isCharging = false;
            hasActed = true;
            cout << "charge attack" << endl;
                int baseDamage = random();
                int damage;
                damage = calculateDamage(baseDamage);
                if (!target.getDefenseMode()) {
                    target.receiveDamage(damage*3);
                }
            return damage*3;
        } else {
            hasActed = true;
            cout << "Attack" << endl;
            return Character::attack(target);
        }
    }
    void charge() {
        if (turnsToCharge <= 0 && !hasActed) {
            sprite=chargedSprite;
            isCharging = true;
            cout << "Przeciwnik jest zirytowany, uwazaj na jego nastepny atak!" << endl;
            turnsToCharge = 4;
            skipturn=true;
            mustattack=true;
        }
    }
    void draw(sf::RenderWindow & window) override {
if(restart){
    defenseMode=false;
    window.draw(sprite);
    restart=false;
    isCharging=false;
}
        if (isCharging) {
            healthBar.setPosition(1350,300);
            healthBarBackground.setPosition(1350,300);
            window.draw(chargedSprite);
        }
        else if (defenseMode) {
            window.draw(defenseSprite);
            defenseSprite.setPosition(1150, 420);
            healthBar.setPosition(1170,360);
            healthBarBackground.setPosition(1170,360);
        }  else {
            healthBar.setPosition(1350,300);
            healthBarBackground.setPosition(1350,300);
            window.draw(sprite);
        }
        window.draw(healthBarBackground);
        window.draw(healthBar);
    }
    void chargeattack() override {
        skipturn=false;
            charge();
            if (!isCharging) {

                turnsToCharge--;
            }
        if(hasActed) {
            hasActed = false;
        }
    }

private:
    std::string chargedTexturePath;
    sf::Texture chargedTexture;
    sf::Sprite chargedSprite;
    sf::Sprite basic;
};

class TarotBoss : public Character {
public:

    TarotBoss(float x, float y,
              const std::string &texturePath,
              const std::string &defenseTexturePath,
              const std::string &deadTexturePath,
              const std::string &tarotTexturePath1,
              const std::string &tarotTexturePath2,
              const std::string &tarotTexturePath3,
              const std::string &tarotTexturePath4,
              const std::string &lowHealthTexturePath,
              int health, int charisma,
              int strength, int agility, int vigor)
            : Character(x, y, texturePath, defenseTexturePath, deadTexturePath, health, charisma, strength, agility, vigor)
    {
        tarotTexture1.loadFromFile(tarotTexturePath1);
        tarotTexture2.loadFromFile(tarotTexturePath2);
        tarotTexture3.loadFromFile(tarotTexturePath3);
        tarotTexture4.loadFromFile(tarotTexturePath4);

        lowHealthTexture.loadFromFile(lowHealthTexturePath);
        tarotSprite1.setTexture(tarotTexture1);
        tarotSprite2.setTexture(tarotTexture2);
        tarotSprite3.setTexture(tarotTexture3);
        tarotSprite4.setTexture(tarotTexture4);

        lowHealthSprite.setTexture(lowHealthTexture);
        setisboss();
        basic=sprite;
    }

    void draw(sf::RenderWindow & window) override {
        if(restart){
            cardEffectActive = false;
            defenseMode=false;
            window.draw(basic);
            restart=false;
        }
        window.draw(basic);
        if (defenseMode) {
            window.draw(defenseSprite);
        }
        else if(cardEffectActive == true){

            switch(whattodraw) {
                case 1: // Księżyc
                    tarotSprite1.setPosition(920, 380);
                    window.draw(tarotSprite1);

                    break;
                case 2: // Kielich
                    tarotSprite2.setPosition(920, 380);
                    window.draw(tarotSprite2);

                    break;
                case 3: // Miecze
                    tarotSprite3.setPosition(920, 380);
                    window.draw(tarotSprite3);

                    break;
                case 4: // Monety
                    tarotSprite4.setPosition(920, 380);
                    window.draw(tarotSprite4);

                    break;
            }
        }
        window.draw(healthBarBackground);
        window.draw(healthBar);
    }
    bool coins=false;
    int whattodraw;
    void drawCard() {
        cardEffectActive = false;
        if(turnCounter==3) {
            cardEffectActive =true;
            int card = rand() % 4 + 1;
            switch(card) {
                case 1: // Księżyc
                    damageMultiplier = 2;
                    whattodraw=1;
                    cout << "Rada tarota wylosowala Ksiezyc" << endl;
                    break;
                case 2: // Kielich
                    health += 20;
                    if (health > maxhealth) health = maxhealth;
                    whattodraw=2;
                    cout << "Rada tarota wylosowala kielich" << endl;
                    break;
                case 3: // Miecze
                    attackMultiplier = 2;
                    whattodraw=3;
                    cout << "Rada tarota wylosowala as mieczy" << endl;
                    break;
                case 4: // Monety

                    whattodraw=4;
                    coins=true;
                    cout << "Rada tarota wylosowala as monet" << endl;
                    break;
            }
            turnCounter=0;

        }
        turnCounter++;
    }


    int attack(Character &target) override {
        int baseDamage = random();
        int damage = calculateDamage(baseDamage);
        damage *= attackMultiplier;
        if(attackMultiplier>1){
            attackMultiplier=1;
        }
        if (!target.getDefenseMode()) {
            target.receiveDamage(damage);
        }
        return damage;
    }

    void receiveDamage(int damage) override {
        damage *= damageMultiplier;
        health -= damage;
        if(damageMultiplier>1){
        damageMultiplier=1;
        }
        if (health < 0) {
            health = 0;
        }
        updateHealthBar();
    }
    bool cardEffectActive = false;
private:
    sf::Texture tarotTexture1;
    sf::Sprite tarotSprite1;
    sf::Texture tarotTexture2;
    sf::Sprite tarotSprite2;
    sf::Texture tarotTexture3;
    sf::Sprite tarotSprite3;
    sf::Texture tarotTexture4;
    sf::Sprite tarotSprite4;
    sf::Texture lowHealthTexture;
    sf::Sprite lowHealthSprite;
    sf::Sprite basic;
    int turnCounter = 0;

    int damageMultiplier = 1;
    int attackMultiplier = 1;

};

#endif //UNTITLED_CHARACTER_H
