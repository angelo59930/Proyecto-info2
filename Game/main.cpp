#include <iostream>
#include <SFML/Graphics.hpp>
#include "Headers/Spaceship.h"
#include "Headers/Enemy_1.h"


#define WIDTH 575
#define HEIGHT 600
#define CANT_ENEMY1_V1 4

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
    ///------------SET COLLISION---------------------------------------------------------------------

    ///------------SET PLAYER---------------------------------------------------------------------

    Texture tex_spaceship;
    if (!tex_spaceship.loadFromFile("imagenes_juego/nave/ship_x2_64x64.png")){
        std::cout << "no se pudo cargar la spaceship" << std::endl;
        return EXIT_FAILURE;
    }
    Spaceship player((WIDTH/2), (HEIGHT/2), tex_spaceship);


    ///-------------SET ENEMY GEN_1----------------------------------------------------------------------------
    Texture tex_enemy_1;
    if (!tex_enemy_1.loadFromFile("imagenes_juego/enemigos/En_gen_1/Enemy_1_v2_x2_64x64.png")){
        std::cout << "no se pudo cargar el enemigo" << std::endl;
        return EXIT_FAILURE;
    }
    auto *enemy1 = new Enemy_1[CANT_ENEMY1_V1];

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
        ///-----------------------ENEMY1---------------------------------------------------------

        if (enemy1->getExistence()){
            for (int i = 0; i < CANT_ENEMY1_V1; ++i) {
                enemy1[i].setTexture(tex_enemy_1);
                enemy1[i].setPosX(64*i);
            }
        }


        for (int i = 0; i < CANT_ENEMY1_V1; ++i) {
            enemy1[i].move();
        }


        ///----------------------DRAW--------------------------------------------------------------
        window.clear();
        window.draw(sp_background1);
        window.draw(sp_background2);
        player.draw(window);
        for (int i = 0; i < CANT_ENEMY1_V1; ++i) {
            enemy1[i].draw(window);
        }
        window.display();

    }

    delete [] enemy1;

    return EXIT_SUCCESS;
}
