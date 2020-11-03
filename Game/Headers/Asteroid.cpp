#include "Asteroid.h"
#define WIDTH 575
#define HEIGHT 600


Asteroid::Asteroid(int pos, Texture &tx) {
    x = pos * 64;
    sp.setTexture(tx);
    animation = 0;
    y = (-64);
}

void Asteroid::move() {
    y += 3;
    if (y > HEIGHT)
        y = 1-64;
}

void Asteroid::draw(RenderWindow &window) {
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
