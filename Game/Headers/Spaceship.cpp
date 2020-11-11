
#include "Spaceship.h"
#define WIDTH 575
#define HEIGHT 600

//Construye el objeto y le setea la textura
Spaceship::Spaceship() {
    tex_spaceship.loadFromFile("images/nave/ship_x2_64x64.png");
    sp.setTexture(tex_spaceship);
    animation = 0;
}

void Spaceship::delimitation() {

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

    //Animacion del jugador
    animation ++;

    if (animation < 8)
        aux = 0;
    else if (animation < 12)
        aux = 1;
    else
        aux = 2;

    if(animation > 24)
        animation = 0;

    //delimitacion de la parte de la textura que se quiere mostrar
    sp.setTextureRect({aux * 64, 0, 64 , 64});
    window.draw(sp);

}


void Spaceship::setPosition() {
    x = 250;
    y = HEIGHT/2;
}

Sprite Spaceship::getSprite() {
    return this->sp;
}

void Spaceship::move() {

    if (Keyboard::isKeyPressed(Keyboard::A)) {
        this->x -= 5;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        this->x += 5;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        this->y -= 5;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        this->y += 5;
    }

}


