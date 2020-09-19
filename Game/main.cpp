#include <iostream>
#include <SFML/Graphics.hpp>
#include "Headers/Spaceship.h"



#define WIDTH 540
#define HEIGHT 600

using namespace sf;

int main() {
    float background_y;

    RenderWindow window (VideoMode(WIDTH,HEIGHT),"SUPER DUPER GUPER SPACE SHIP");

    ///--------------SET BACKGROUND------------------------------------------------------------
    Texture tex_background;
    if (!tex_background.loadFromFile("imagenes_juego/bg_space_seamless_1.png")){     //origen:https://opengameart.org/content/space-background-7
        std::cout << "no se pudo cargar el background" << std::endl;
        return EXIT_FAILURE;
    }
    Sprite sp_background1;
    Sprite sp_background2;

    sp_background1.setTexture(tex_background);
    sp_background2.setTexture(tex_background);

    ///------------SET PLAYER---------------------------------------------------------------------

    Texture tex_spaceship;
    if (!tex_spaceship.loadFromFile("imagenes_juego/nave/ship_x2_64x64.png")){
        std::cout << "no se pudo cargar la spaceship" << std::endl;
        return EXIT_FAILURE;
    }
    Spaceship player((WIDTH/2), (HEIGHT/2), tex_spaceship); //--- tiene que estar en una funcion que lo pongan despues del menu


    ///-------------SET ENEMY GEN_1----------------------------------------------------------------------------
    Texture tex_enemy_1;
    if (!tex_enemy_1.loadFromFile("imagenes_juego/enemigos/En_gen_1/Enemy_1_v2_x2_64x64.png")){
        std::cout << "no se pudo cargar el enemigo" << std::endl;
        return EXIT_FAILURE;
    }


    window.setFramerateLimit(60);
    while(window.isOpen()){
        Event event{};

        while (window.pollEvent(event)){
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
            }
        }


        ///----------MOVE BACKGROUND---------------------------------------------------------

        background_y += 3.5;

        if (background_y > tex_background.getSize().y){
            background_y -= tex_background.getSize().y;
        }
        sp_background1.setPosition(0,background_y);
        sp_background2.setPosition(0,background_y - tex_background.getSize().y);

        ///----------MOVE PLAYER---------------------------------------------------------------

        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-5, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(5, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.move(0, -5);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.move(0, 5);
        }

        window.clear();
        window.draw(sp_background1);
        window.draw(sp_background2);
        player.draw(window);


        window.display();
    }
    return EXIT_SUCCESS;
}
