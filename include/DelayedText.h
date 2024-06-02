#ifndef DELAYEDTEXT_H
#define DELAYEDTEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class DelayedText : public sf::Text
{
    public:
        sf::Clock m_Clock;
        sf::Time m_time,m_delay;
        std::string m_string,m_buffer;
        unsigned int current;
        sf::SoundBuffer buffer;
        sf::Sound sound;


        DelayedText();
        DelayedText(const std::string& gstring,const sf::Font& gfont,unsigned int gsize);
        ~DelayedText(void);
        void setString(const std::string& string);//covering text's setter
        void setDelay(sf::Time gtime);
        void setMtime(sf::Time gtime);
        const DelayedText& update(void);
};

#endif // DELAYEDTEXT_H
