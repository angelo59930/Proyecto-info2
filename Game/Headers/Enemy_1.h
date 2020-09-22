
#include <SFML/Graphics.hpp>

using namespace sf;

#ifndef GAME_ENEMY_1_H
#define GAME_ENEMY_1_H


class Enemy_1 {
private:
    int x;
    int y;
    Sprite sp;
    int animation;
public:
    Enemy_1();

    void setTexture(Texture &tex);
    void setPosX(int x);

    bool getExistence();


    void move();

    void draw(RenderWindow &window);
};


#endif //GAME_ENEMY_1_H
