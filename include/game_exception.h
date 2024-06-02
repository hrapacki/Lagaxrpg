#ifndef GAME_EXCEPTION_H_INCLUDED
#define GAME_EXCEPTION_H_INCLUDED

class GameException : public std::runtime_error {
public:
        GameException(std::string a):
        runtime_error(a){
        }
};

///--------- LISTA BLEDOW ------------
/// 000 - blad wczytywania czcionki - brakuje pliku z czcionka (folder font)
/// 001 - blad wczytywania tekstury - brakuje tekstury (folder textures lub bgImages)
/// 002 - blad wczytywania danych - brakuje pliku z danymi (folder data)
/// 003 - blad wczytywania dialogu - brakuje pliku z dialogiem (folder dialog)
/// 004 - blad wczytywania walki - brakuje pliku z przeciwnikami (folder battle)

#endif // GAME_EXCEPTION_H_INCLUDED
