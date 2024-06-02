#include "GameException.h"

GameException::GameException(std::string a):runtime_error(a)
{
    //ctor
}

GameException::~GameException()
{
    //dtor
}
