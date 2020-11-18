#include <SFML/Graphics.hpp>

using namespace sf;

#ifndef GAME_ASTEROID_H
#define GAME_ASTEROID_H


class Asteroid {
private:
    int x;
    int y;
    Texture tex_asteroid;
    Sprite sp;
    int animation;

public:
    Asteroid(int pos);


    bool move();

    Sprite getSprite();


    void draw(RenderWindow &window);
};

#endif
