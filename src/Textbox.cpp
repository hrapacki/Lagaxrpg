#include "Textbox.h"
#include "game_exception.h"

Textbox::Textbox(sf::Font &inFont, std::string &a, std::string &b):font(inFont)
{
    std::ifstream input("dialog/"+b+"/"+a+"/"+a+".txt");
    if(!input.good()){
        std::string error = "Blad 003: blad wczytywania dialogu (plik +dialog/"+b+"/"+a+"/"+a+".txt"+" nie istnieje)";
        throw new GameException(error);
    }
    std::string in;
    sf::Text inText;
    do{
        getline(input, in);
        if(in.substr(0,3)=="<Z>"){          ///added
            sf::Texture temp;
            std::string txtName = in.substr(3,in.back());
            temp.loadFromFile("dialog/"+b+"/"+a+"/bgImages/"+txtName);
            tekstury.push_back(temp);
        }
        else{
            dialog.push_back(in);
        }

    }
    while(!input.eof());
    input.close();
    ///dialog.push_back("koniec wektora###");
    std::string temp = dialog[0];
    temp.pop_back();
    temp.pop_back();
    temp.pop_back();
    txt.setString(temp);
    txt.setCharacterSize(30);
    txt.setFont(font);
    txt.setDelay(sf::seconds(1.f/40.f));
    txt.setPosition(sf::Vector2f((1920-1920/1.6)/2, (1080-1080/2.6)));
    txt.setCharacterSize(50);
    sprite.setTexture(tekstury[whichTexture]);          ///added
    sprite.setOrigin(tekstury[whichTexture].getSize().x/2, tekstury[whichTexture].getSize().y/2);
    sprite.setPosition(1920.f/2, 1080.f/3);          ///added

    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(5);
    box.setPosition(1920/6, 1080*6/10);
    box.setSize(sf::Vector2f(1920/1.5, 1080/3));
}

Textbox::~Textbox()
{
    //dtor
}

void Textbox::displayInConsole(){
    for(int i=0;i<dialog.size();i++){
        std::cout << dialog[i] << std::endl;
    }
}

bool Textbox::isQuestion(){
    return (dialog[i].substr(dialog[i].size()-3, 2) == "<?");
}

bool Textbox::isEnd(){
    return (dialog[i].back() == '!');
}

void Textbox::setDialog(){
    if(i<dialog.size()){
        std::string temp = dialog[++i];
        if(temp.back()=='T'){          ///added
            setImage();
        }
        temp.pop_back();
        temp.pop_back();
        temp.pop_back();
        txt.setString(temp);
        if(isQuestion()){
            temp = dialog[i+1];
            temp.pop_back();
            temp.pop_back();
            temp.pop_back();
            q1.setString(temp);
            q1.setCharacterSize(50);
            q1.setFont(font);
            q1.setDelay(sf::seconds(1.f/10.f));
            q1.setPosition(txt.getPosition().x, txt.getPosition().y+60.0f);

            temp = dialog[i+2];
            temp.pop_back();
            temp.pop_back();
            temp.pop_back();
            q2.setString(temp);
            q2.setCharacterSize(50);
            q2.setFont(font);
            q2.setDelay(sf::seconds(1.f/10.f));
            q2.setPosition(txt.getPosition().x, txt.getPosition().y+120.0f);
        }
    }
    else{
        return;
    }
    /*
    if(isEnd()){
        i=dialog.size()-2;
    }*/
}

bool Textbox::findChoice(size_t c){
    for(int j=i;j<dialog.size();j++){
        std::string nowy = dialog[j];
        size_t k = dialog[j].size()-2;
        switch(c){
            case 1:{
                if(nowy[k]=='1'){
                    i=j-1;
                    setDialog();
                    return true;
                }
                break;
            }
            case 2:{
                if(nowy[k]=='2'){
                    i=j-1;
                    setDialog();
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

void Textbox::setImage(){
    sprite.setTexture(tekstury[++whichTexture]);
}

bool Textbox::handleKeyPress(size_t &choice){
    if(isQuestion()){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            if(choice == 1){
                choice = 2;
            }
            else if(choice == 2){
                choice = 1;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
            switch(choice){
                case 1:{
                    findChoice(1);
                    break;
                }
                case 2:{
                    findChoice(2);
                    break;
                }
            }
        }
    }
    else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            if(!isEnd()){
                setDialog();
            }
            else{
                return false;
            }
        }
    }
    return true;
}

void Textbox::whileActive(sf::RenderWindow &window){
    size_t choice = 1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:{
                    window.close();
                    break;
                }
                case sf::Event::TextEntered:{   ///tu chodzi o to ze jak piszesz cos na klawiaturze, to zapisze ci sie to w konsoli a nie w oknie gry
                    if(event.text.unicode<128){
                        printf("%c", event.text.unicode);
                        std::cout << std::endl;
                    }
                    break;
                }
                case sf::Event::KeyPressed:{
                    /*
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
                        std::cout << "debug:------------------------------" << std::endl;
                        std::cout << "zawartosc wektora:" << std::endl;
                        displayInConsole();
                        std::cout << "obecny tekst: " << dialog[textbox.i] << std::endl;
                        std::cout << "isQuestion = " << isQuestion() << std::endl;
                        std::cout << "choice = " << choice << std::endl;
                        std::cout << "------------------------------------" << std::endl;
                    }
                    */
                    if(!handleKeyPress(choice)){
                        return;
                    }
                    break;
                }
            }
        }
        window.clear();
        window.draw(box);
        if(isQuestion()){
            switch(choice){
                case 1:{
                    q1.setColor(sf::Color::Yellow);
                    q2.setColor(sf::Color::White);
                    break;
                }
                case 2:{
                    q1.setColor(sf::Color::White);
                    q2.setColor(sf::Color::Yellow);
                    break;
                }
            }

            window.draw(q1.update());
            window.draw(q2.update());
        }

        window.draw(txt.update());
        window.draw(sprite);          ///added
        window.display();
    }
}
