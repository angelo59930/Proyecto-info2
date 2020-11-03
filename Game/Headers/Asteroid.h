#include <SFML/Graphics.hpp>

using namespace sf;

#ifndef GAME_ASTEROID_H
#define GAME_ASTEROID_H


class Asteroid {
private:
    int x;
    int y;
    Sprite sp;
    int animation;
public:
    Asteroid(int pos,Texture &tx);

    void move();


    void draw(RenderWindow &window);
};


#endif
