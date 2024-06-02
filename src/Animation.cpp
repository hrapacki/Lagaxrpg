#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this -> imageCount = imageCount;                                    ///inicjalizacja atrybutów
    this -> switchTime = switchTime;
    totalTime = 0.0f;                                                   ///ustawiamy czas na zero, bedziemy go zmieniac w funkcji update
    currentImage.x = 0;                                                 ///ustawiamy na pierwszy obraz w teksturze

    uvRect.width = texture->getSize().x / float(imageCount.x);          ///te 2 linijki ustawiaja nam poczatkowy sprite
    uvRect.height = texture->getSize().y / float(imageCount.y);         ///
}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime){                       ///animacja jak masz teksture od lewej do prawej
    currentImage.y = row;                                               ///inicjalizacja zmiennych
    totalTime += deltaTime;                                             ///ustawiamy totalTime na podany deltaTime

    if(totalTime >= switchTime){                                        ///jezeli totalTime jest wiekszy od czasu na zmiane obrazu (switchTime)
        totalTime -= switchTime;                                        ///zmniejszamy totalTime o switchTime
        currentImage.x++;                                               ///oraz zmieniamy na nastêpny obraz
        std::cout << currentImage.x << std::endl;
        if(currentImage.x >= imageCount.x){                             ///jezeli wyjdziemy poza zakres tekstury
            currentImage.x = 0;                                         ///zmieniamy z powrotem na pierwszy obraz
        }
    }

    uvRect.left = currentImage.x * uvRect.width;                        ///te 2 linijki zmieniaja nam sprite na nastepny w kolejce
    uvRect.top = currentImage.y * uvRect.height;
}
