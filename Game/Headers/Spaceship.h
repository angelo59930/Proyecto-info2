
#include <SFML/Graphics.hpp>

#ifndef GAME_SPACESHIP_H
#define GAME_SPACESHIP_H

using namespace sf;

class Spaceship {
private:
    int x;
    int y;
    Texture tex_spaceship;
    Sprite sp;
    int animation;

public:
    //Constructor del objeto
    Spaceship();

    //Seteo de la posicion del jugador
    void setPosition();

    //Delimita hasta donde se puede mover el jugador
    void delimitation();

    //Mueve al jugador
    void move();

    //Devuelve el sprite del objeto
    Sprite getSprite();

    //Dibuja el objeto en pantalla
    void draw(RenderWindow &window);
};


#endif //GAME_SPACESHIP_H
