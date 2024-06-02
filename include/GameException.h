#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <runtime_error.h>


class GameException : public runtime_error
{
    public:
        GameException(std::string a);
        virtual ~GameException();

    protected:

    private:
};

#endif // GAMEEXCEPTION_H
