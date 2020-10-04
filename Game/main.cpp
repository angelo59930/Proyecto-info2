#include <iostream>
#include <SFML/Graphics.hpp>
#include "Headers/Spaceship.h"
#include "Headers/Enemy_1.h"


#define WIDTH 575
#define HEIGHT 600
#define CANT_ENEMY1_V1 4

void paused(bool &pause,RenderWindow &window, const Sprite &background1, Event &event, Text tx_menu, Text tx_aux1);

Event &getEvent(RenderWindow &window, Event &event);

void move_background(float &background_y, const Texture &tex_background, Sprite &sp_background1, Sprite &sp_background2);

void Move_player(Spaceship &player);

void move_enemy1(Texture &tex_enemy_1, Enemy_1 *enemy1);


using namespace sf;


int main() {
    float background_y = 0;
    bool pause = false;

    RenderWindow window (VideoMode(WIDTH,HEIGHT),"SUPER DUPER GUPER SPACE SHIP");
    ///----------------------------------------------------------------------------------------
    Font words;
    if (!words.loadFromFile("Font/8-bit Arcade In.ttf")){                   //origen: Damien Gosset-https://www.dafont.com/es/8-bit-arcade.font
        std::cout << "no se pudo cargar la fuente" << std::endl;
        return EXIT_FAILURE;
    }
    Text tx_menu;
    Text tx_aux1;
    Text tx_aux2;
    tx_aux1.setFont(words);
    tx_aux2.setFont(words);
    tx_menu.setFont(words);

    ///--------------SET BACKGROUND------------------------------------------------------------
    Texture tex_background;
    if (!tex_background.loadFromFile("images/bg_space_seamless_1.png")){     //origen:https://opengameart.org/content/space-background-7
        std::cout << "no se pudo cargar el background" << std::endl;
        return EXIT_FAILURE;
    }
    Sprite sp_background1;
    Sprite sp_background2;

    sp_background1.setTexture(tex_background);
    sp_background2.setTexture(tex_background);

    Sprite background1 = sp_background1;
    ///------------SET PLAYER---------------------------------------------------------------------

    Texture tex_spaceship;
    if (!tex_spaceship.loadFromFile("images/nave/ship_x2_64x64.png")){
        std::cout << "no se pudo cargar la spaceship" << std::endl;
        return EXIT_FAILURE;
    }
    Spaceship player((WIDTH/2), (HEIGHT/2), tex_spaceship);


    ///-------------SET ENEMY GEN_1----------------------------------------------------------------------------
    Texture tex_enemy_1;
    if (!tex_enemy_1.loadFromFile("images/enemigos/En_gen_1/Enemy_1_v2_x2_64x64.png")){
        std::cout << "no se pudo cargar el enemigo" << std::endl;
        return EXIT_FAILURE;
    }
    auto *enemy1 = new Enemy_1[CANT_ENEMY1_V1];

    ///---------------------------------------------------------------------------------------------------------
    window.setFramerateLimit(60);
    while(window.isOpen()){
        Event event{};


        try {
            event = getEvent(window, event);
        }
        catch (int) {
            return EXIT_SUCCESS;
        }

        move_background(background_y, tex_background, sp_background1, sp_background2);
        Move_player(player);

        move_enemy1(tex_enemy_1, enemy1);

        if(pause)
            paused(pause,window,background1,event,tx_menu,tx_aux1);
        if (Keyboard::isKeyPressed(Keyboard::P))
            pause = true;


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


void move_enemy1(Texture &tex_enemy_1, Enemy_1 *enemy1) {
    if (enemy1->getExistence()){
        for (int i = 0; i < CANT_ENEMY1_V1; ++i) {
            enemy1[i].setTexture(tex_enemy_1);
            enemy1[i].setPosX(64*i);
        }
    }
    for (int i = 0; i < CANT_ENEMY1_V1; ++i) {
        enemy1[i].move();
    }
}

void Move_player(Spaceship &player) {
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
}

void move_background(float &background_y, const Texture &tex_background, Sprite &sp_background1, Sprite &sp_background2) {
    background_y += 3.5;

    if (background_y > tex_background.getSize().y){
        background_y -= tex_background.getSize().y;
    }
    sp_background1.setPosition(0,background_y);
    sp_background2.setPosition(0,background_y - tex_background.getSize().y);
}

Event &getEvent(RenderWindow &window, Event &event) {
    while (window.pollEvent(event)){
        if (event.type == Event::Closed || !window.isOpen()){
            window.close();
            throw 0;
        }
    }
    return event;
}

void paused(bool &pause, RenderWindow &window, const Sprite &background1, Event &event, Text tx_menu, Text tx_aux1) {
    tx_menu.setString("PAUSE");
    tx_menu.setCharacterSize(80);
    tx_menu.setPosition(185,0);

    tx_aux1.setString("PRESS ENTER TO CONTINUE\n     PRESS Esc TO EXIT");
    tx_aux1.setCharacterSize(40);
    tx_aux1.setPosition(73,480);



    while (pause){

        try {
           event = getEvent(window, event);
        }
        catch (int) {
            return;
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            pause = false;
            break;
        }


        window.clear();
        window.draw(background1);
        window.draw(tx_aux1);
        window.draw(tx_menu);
        window.display();
    }

}
