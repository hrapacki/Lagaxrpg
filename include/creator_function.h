#ifndef CREATOR_FUNCTION_H_INCLUDED
#define CREATOR_FUNCTION_H_INCLUDED

void handleCreation(sf::RenderWindow &window, PlayerCharacter *& player, Creating_Character *& characterCreator, sf::Music &music_title, battlestate &state){
    while(window.isOpen()){


    sf::Texture editorBackgroundTexture;
    editorBackgroundTexture.loadFromFile("textures/backgrounds/edytor.png");
    sf::Sprite editorBackgroundSprite;
    editorBackgroundSprite.setPosition(1920/2, 1080*1/3);
    editorBackgroundSprite.setOrigin(editorBackgroundTexture.getSize().x/2,editorBackgroundTexture.getSize().y/2);
    editorBackgroundSprite.setTexture(editorBackgroundTexture);

    if (music_title.getStatus() != sf::Music::Playing) {
        music_title.play();
    }
    characterCreator->handleEvents();

        if (characterCreator->isFinished()) {
            player->setVigor(characterCreator->getVigor());
            player->setAgility(characterCreator->getAgility());
            player->setCharisma(characterCreator->getCharisma());
            player->setStrength(characterCreator->getStrength());
            player->updateHealth();
            std::fstream stats("data/playerstats.txt", std::ios::out|std::ios::trunc);
            stats<<characterCreator->getCharisma()<<endl<<characterCreator->getStrength()<<endl<<characterCreator->getAgility()<<endl<<characterCreator->getVigor()<<endl;
            stats.close();
            //test= new Battle(&player,font);
            cout << characterCreator->getRemainingPoints();
            pointskept += characterCreator->getRemainingPoints();
            state = battlestate::battle;
            music_title.stop();
            return;
        }
        window.clear();
        window.draw(editorBackgroundSprite);
        characterCreator->draw();
        window.display();
        sf::sleep(sf::milliseconds(100));
}

}

#endif // CREATOR_FUNCTION_H_INCLUDED
