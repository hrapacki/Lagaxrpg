#ifndef IS_IT_HERE_H_INCLUDED
#define IS_IT_HERE_H_INCLUDED
#include "to_string.h"

void isItHere(bool &dialogUsed, std::vector<std::string> &vec, std::string &source, std::string kind){
    int i;
    source = kind+patch::to_string(rand()%2+1);     /// tu zmienimy numerek w zaleznosci od tego ile dialogow bedzie
    std::cout << source << std::endl;
    for(i=0;i<vec.size();i++){
        if(vec[i] == source){
            break;
        }
    }
    if(i == vec.size()){
        vec.push_back(source);
        dialogUsed = false;
    }
}

#endif // IS_IT_HERE_H_INCLUDED
