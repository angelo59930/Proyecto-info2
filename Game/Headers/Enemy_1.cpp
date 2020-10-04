
#include "Enemy_1.h"
#define HEIGHT 600

Enemy_1::Enemy_1() {
    x = 0;
    y = 1-64;
    animation = 0;
}

void Enemy_1::move() {
    y += 3;
    if (y > HEIGHT)
       y = 1-64;
}

void Enemy_1::draw(RenderWindow &window) {
    int aux;
    sp.setPosition(this->x, this->y);

    animation ++;

    if (animation < 8)
        aux = 0;
    else if (animation < 12)
        aux = 1;
    else if (animation < 24)
        aux = 2;
    else
        aux = 3;

    if(animation > 32)
        animation = 0;

    sp.setTextureRect({aux * 64, 0, 64 , 64});
    window.draw(sp);
}

void Enemy_1::setTexture(Texture &tex) {
    sp.setTexture(tex);
}

void Enemy_1::setPosX(int x) {
    this -> x = x;
}

bool Enemy_1::getExistence() {
    if (y == 0 && y < HEIGHT)
        return true;
    else if (y > HEIGHT)
        return false;
}


