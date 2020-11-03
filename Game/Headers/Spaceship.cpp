
#include "Spaceship.h"
#define WIDTH 575
#define HEIGHT 600

Spaceship::Spaceship(int initial_x, int initial_y, Texture &tex) {
    x = initial_x;
    y = initial_y;
    sp.setTexture(tex);
    animation = 0;
}

void Spaceship::move(int x, int y) {
    this->x += x;
    this->y += y;

    if (this->x < 0)
        this->x = 0;
    if (this->x > WIDTH  - 64)
        this->x = WIDTH  - 64;
    if (this->y < 0)
        this->y = 0;
    if (this->y > HEIGHT - 64)
        this->y = HEIGHT - 64;

}

void Spaceship::draw(RenderWindow &window) {
    int aux;
    sp.setPosition(this->x, this->y);

    animation ++;

    if (animation < 8)
        aux = 0;
    else if (animation < 12)
        aux = 1;
    else
        aux = 2;

    if(animation > 24)
        animation = 0;

    sp.setTextureRect({aux * 64, 0, 64 , 64});
    window.draw(sp);

}

void Spaceship::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}


