#include "DelayedText.h"

DelayedText::DelayedText()
{
}

DelayedText::DelayedText(const std::string& gstring,const sf::Font& gfont,unsigned int gsize):
sf::Text("",gfont,gsize),
current(0),
m_string(gstring)
{
    if (!buffer.loadFromFile("music/boom.wav")){}
    sound.setBuffer(buffer);
}

DelayedText::~DelayedText(void)
{
}

void DelayedText::setString(const std::string& gstring)
{
        m_buffer.clear();
        m_string=gstring;
        current=0;
}

void DelayedText::setMtime(const sf::Time gtime)
{
        m_time=gtime;
}

void DelayedText::setDelay(sf::Time gtime)
{
        m_delay=gtime;
}

const DelayedText& DelayedText::update(void)
{
        m_time+=m_Clock.restart();
        while (m_time>=m_delay)
        {

                m_time-=m_delay;
                if(current<m_string.length())
                {
                    if ((m_string[current] == '\\') and m_string[current+1] == 'n') {  ///jezeli w pliku tekstowym napotkasz znak nowej linii
                        m_buffer+="\n";                                         ///to dopisuje go do wyswietlanego tekstu, bo normalnie nie dziala
                        current+=2;
                    }
                    else{
                        m_buffer+=m_string[current];
                        ++current;
                    }
                }
        }
        sf::Text::setString(m_buffer);
        sound.play();
        return *this;
}


