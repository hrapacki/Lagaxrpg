#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        virtual ~Animation();
        sf::IntRect uvRect;        ///ta zmienna przechowuje nam koordynaty obrazow z tekstury

        void update(int row, float deltaTime);

    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;   ///co ile zmienia sie obraz

};

#endif // ANIMATION_H
