#include "Asteroid.h"
#define WIDTH 575
#define HEIGHT 600


Asteroid::Asteroid(int pos) {
    tex_asteroid.loadFromFile("images/asteroid/asteroid.png");
    x = pos * 64;
    sp.setTexture(tex_asteroid);
    animation = 0;
    y = (-64);

}

bool Asteroid::move() {
    this->y += 3;
    if (this->y > HEIGHT)
        return false;
    else
        return true;
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

Sprite Asteroid::getSprite() {
    return this->sp;
}

