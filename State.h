#ifndef STATE_H 
#define STATE_H 
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
 
class State
{
private:
 
   Sprite bg;
   Music music;
   bool quitRequested;
 
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
 
};
#endif