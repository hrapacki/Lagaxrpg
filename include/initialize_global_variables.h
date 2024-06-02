#ifndef INITIALIZE_GLOBAL_VARIABLES_H_INCLUDED
#define INITIALIZE_GLOBAL_VARIABLES_H_INCLUDED

#include "files_to_include.h"

sf::RenderWindow window(sf::VideoMode(1920, 1080), "LAGAX", sf::Style::Fullscreen);
sf::Font font;
gamestate state = gamestate::menu;
size_t steps = 0;
size_t procentWalka = 30;
std::vector<std::string> battles;
std::vector<std::string> dialogs;
std::string source;
std::string kind;
Sidekick whichOne = Sidekick::none;
int saldo = 0;

PlayerCharacter* player = new PlayerCharacter(700, 380, "textures/player/player.png", "textures/player/playerdef.png","textures/player/dead.png", 100, 50, 50, 50, 50);
sf::Clock enemyAttackClock;
sf::Clock deltaClock;

battlestate walka = battlestate::battle;
#endif // INITIALIZE_GLOBAL_VARIABLES_H_INCLUDED
