#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <stack>
#include <queue>

#include "Headers/List/LinkedList.h"
#include "Headers/Spaceship.h"
#include "Headers/Asteroid.h"


#define WIDTH 575
#define HEIGHT 600


void paused(bool &pause,RenderWindow &window, const Sprite &background1, Event &event, Text tx_menu, Text tx_aux1, bool &menu);

void move_background(float &background_y, const Texture &tex_background, Sprite &sp_background1, Sprite &sp_background2);

void Move_player(Spaceship &player);

using namespace sf;

int main() {
    int score = 0;
    float background_y = 0;
    bool pause = false, menu = true, menu_score = false, life = true;

    srand(time(NULL));

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
    Text tx_aux3;
    tx_aux1.setFont(words);
    tx_aux2.setFont(words);
    tx_aux3.setFont(words);
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
    Spaceship player((250), (HEIGHT/2), tex_spaceship);

    ///--------------------------------------------------------------------------------------------

    Texture tex_asteroid;
    if (!tex_asteroid.loadFromFile("images/asteroid/asteroid.png")) {
        std::cout << "no se pudo cargar asteroid" << std::endl;
        return EXIT_FAILURE;
    }

    LinkedList<Asteroid> list_asteroid;
    std::stack<int> stack_score;

    window.setFramerateLimit(60);
    while(window.isOpen()){
        Event event{};



        while (window.pollEvent(event)){
            if (event.type == Event::Closed || !window.isOpen()){
                window.close();
                return EXIT_SUCCESS;
            }
        }

        while (menu){

            player.setPosition((250), (HEIGHT/2));

            tx_menu.setString("F  A  R ");
            tx_menu.setCharacterSize(80);
            tx_menu.setPosition(175,150);

            tx_aux1.setString("Press S for look scores\n  Press Enter for play\n     Press Esc to exit");
            tx_aux1.setCharacterSize(40);
            tx_aux1.setPosition(73,300);

            while (window.pollEvent(event)){
                if (event.type == Event::Closed || !window.isOpen()){
                    window.close();
                    return EXIT_SUCCESS;
                }
            }
            std::ifstream write;
            write.open("score.txt");
            while (!write.eof() && !stack_score.empty()){
                write >> stack_score.top();
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)){
                menu = false;
                score = 0;
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)){
                window.close();
                break;
            }

            if (Keyboard::isKeyPressed(Keyboard::S)){
                menu_score = true;
                break;
            }


            write.close();

            window.clear();
            window.draw(background1);
            window.draw(tx_aux1);
            window.draw(tx_menu);
            window.display();
        }
        while (menu_score){
            LinkedList<String> score_list;
            int aux,i = 0;
            String scr;
            std::ifstream reed;
            tx_aux1.setString("SCORES");
            tx_aux1.setCharacterSize(70);
            tx_aux1.setPosition(180,100);

            tx_aux3.setString("Press Backspace to return");
            tx_aux3.setCharacterSize(40);
            tx_aux3.setPosition(55,480);

            while (window.pollEvent(event)){
                if (event.type == Event::Closed || !window.isOpen()){
                    window.close();
                    return EXIT_SUCCESS;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace)){
                menu_score = false;
                break;
            }

            reed.open("score.txt");
            if(reed.fail()){
                return EXIT_FAILURE;
            }
            while (!reed.eof()){
                reed >> aux;
                scr = std::to_string(aux);
                score_list.insert(i,scr);
                i++;
            }
            window.clear();
            window.draw(background1);
            window.draw(tx_aux1);
            window.draw(tx_aux3);
            for (i = 0; i < 10; ++i) {

                tx_aux2.setString(score_list.get(i));
                tx_aux2.setCharacterSize(70);
                tx_aux2.setPosition(205,150 + (i*30));
                window.draw(tx_aux2);

            }
            window.display();
        }



        /*if (score <= 500 && !list_asteroid.size()){
            int aux = rand()%3 - 0;                            |    ESTO ROMPE
            for (int i = 0; i < aux; ++i) {                    |    EL MAL****
                Asteroid a((rand()%8-0),tex_asteroid);   ----->|       JUEGO
                list_asteroid.insert(i,a);
            }
        }*/


        if (life == true)
            score +=1;
        if (life == false)
            stack_score.push(score);

        String sc = std::to_string(score);
        tx_aux1.setString(sc);
        tx_aux1.setCharacterSize(40);
        tx_aux1.setPosition(260,550);


        move_background(background_y, tex_background, sp_background1, sp_background2);
        Move_player(player);

        if(pause)
            paused(pause,window,background1,event,tx_menu,tx_aux1,menu);
        if (Keyboard::isKeyPressed(Keyboard::P))
            pause = true;


        window.clear();
        window.draw(sp_background1);
        window.draw(sp_background2);
        window.draw(tx_aux1);
        if (life == true)
            player.draw(window);
        for (int i = 0; i < list_asteroid.size(); ++i) {
            list_asteroid.get(i).draw(window);
        }
        list_asteroid.empty();

        window.display();

    }

    return EXIT_SUCCESS;
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


void paused(bool &pause, RenderWindow &window, const Sprite &background1, Event &event, Text tx_menu, Text tx_aux1, bool &menu) {
    tx_menu.setString("PAUSE");
    tx_menu.setCharacterSize(80);
    tx_menu.setPosition(185,0);

    tx_aux1.setString("PRESS Enter TO CONTINUE\nPRESS Backspace TO EXIT");
    tx_aux1.setCharacterSize(40);
    tx_aux1.setPosition(73,480);



    while (pause){

        while (window.pollEvent(event)){
            if (event.type == Event::Closed || !window.isOpen()){
                window.close();
                return;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            pause = false;
            break;
        }
        if (Keyboard::isKeyPressed(Keyboard::BackSpace)){
            menu = true;
            break;
        }

        window.clear();
        window.draw(background1);
        window.draw(tx_aux1);
        window.draw(tx_menu);
        window.display();
    }

}

