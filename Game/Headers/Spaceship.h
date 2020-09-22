
#include <SFML/Graphics.hpp>

using namespace sf;

#ifndef GAME_SPACESHIP_H
#define GAME_SPACESHIP_H


class Spaceship {
private:
    int x;
    int y;
    Sprite sp;
    int animation;
public:
    Spaceship(int initial_x, int initial_y, Texture &tex);

    void move(int x,int y);

    void draw(RenderWindow &window);

};


#endif //GAME_SPACESHIP_H
