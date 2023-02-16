#include <stdio.h>
#include <stdlib.h>
#include "TitleState.h"
#include "Game.h"



int main (int argc, char** argv) {

    /* Inicializa todas as bibliotecas */
  auto &game = Game::GetInstance();
  game.Push(new TitleState());
  game.Run();
    return 0;
}


