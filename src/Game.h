//
// Created by Element on 04/03/2018.
//

#ifndef MINICARD_GAME_H
#define MINICARD_GAME_H

#include "CardGame.h"

class Game {
public:
    void Init();
    void Update();
    void Draw();
private:
    CardGame cardGame;
};


#endif //MINICARD_GAME_H
