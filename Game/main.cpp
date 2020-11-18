#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <stack>
#include <queue>
#include "Headers/Colision/Collision.h"
#include "Headers/List/LinkedList.h"
#include "Headers/Spaceship.h"
#include "Headers/Asteroid.h"


#define WIDTH 575
#define HEIGHT 600


void paused(bool &pause,RenderWindow &window, const Sprite &background1, Event &event, Text tx_menu, Text tx_aux1, bool &menu,bool &game);

void move_background(float &background_y, const Texture &tex_background, Sprite &sp_background1, Sprite &sp_background2,int score);

void load_score(std::stack<int> &stack_score);

void extracData(std::queue<String> &score_queue);


void
dead_menu(bool dead, RenderWindow &window, Text &tx_menu, Text &tx_aux1, const Sprite &background1, Spaceship &player,
          int &score, bool &menu, bool &life, bool &game, Event &event);

void asteroids(int score, int &clock, LinkedList<Asteroid *> &asteroid_list);

void colisions(Spaceship &player, LinkedList<Asteroid *> &asteroid_list, bool &life);

void score_menu(bool &menu_score, RenderWindow &window, Text &tx_aux1, Text &tx_aux2, Text &tx_aux3,
                  const Sprite &background1, Event &event);

void
main_menu(RenderWindow &window, Text &tx_menu, Text &tx_aux1, const Sprite &background1, Spaceship &player, int &score,
          bool &menu, bool &menu_score, bool &life, bool &game, std::stack<int> &stack_score, Event &event);

using namespace sf;

int main() {
    int score = 0,clock = 0;
    float background_y = 0;
    bool pause = false, menu = true, menu_score = false, life = false, game = false, dead = false;

    srand(time(NULL));

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "SUPER DUPER GUPER SPACE SHIP");

    ///----------------------------------------------------------------------------------------
    Font words;
    words.loadFromFile("Font/8-bit Arcade In.ttf"); //origen: Damien Gosset-https://www.dafont.com/es/8-bit-arcade.font

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
    tex_background.loadFromFile("images/bg_space_seamless_1.png");  //origen:https://opengameart.org/content/space-background-7

    Sprite sp_background1;
    Sprite sp_background2;

    sp_background1.setTexture(tex_background);
    sp_background2.setTexture(tex_background);

    Sprite background1 = sp_background1;

    //Crea el objeto Jugador
    Spaceship player;


    //Crea una lista enlazada de objetos del tipo asteroid
    LinkedList<Asteroid *> asteroid_list;

    //Crea una pila de puntuaciones
    std::stack<int> stack_score;

    window.setFramerateLimit(60);
    while (window.isOpen()) {
        Event event{};

        main_menu(window, tx_menu, tx_aux1, background1, player, score, menu, menu_score, life, game, stack_score,
                  event);


        score_menu(menu_score, window, tx_aux1, tx_aux2, tx_aux3, background1, event);

        dead_menu(dead, window, tx_menu, tx_aux1, background1, player, score, menu, life, game, event);

        while (game) {
            score++;

            while (window.pollEvent(event)) {
                if (event.type == Event::Closed || !window.isOpen()) {
                    window.close();
                    exit (EXIT_SUCCESS);
                }
            }

            move_background(background_y, tex_background, sp_background1, sp_background2, score);

            player.move();
            player.delimitation();

            //funcion encargada de la aparicion de asteroides
            asteroids(score, clock, asteroid_list);

            //funcion encargada de las colisiones entre el jugador y los asteroides
            colisions(player, asteroid_list,life);

            String sc = std::to_string(score);
            tx_aux1.setString(sc);
            tx_aux1.setCharacterSize(40);
            tx_aux1.setPosition(260, 550);


            if (pause)
                paused(pause, window, background1, event, tx_menu, tx_aux1, menu, game);
            if (Keyboard::isKeyPressed(Keyboard::P))
                pause = true;


            window.clear();
            window.draw(sp_background1);
            window.draw(sp_background2);
            window.draw(tx_aux1);
            if (life)
                player.draw(window);
            if (!life) {
                //si el jugador pierde se borra la lista,
                //se pasa la puntuacion al stack y muestra 
                //la pantalla de meurte
                asteroid_list.~LinkedList();
                stack_score.push(score);
                game = false;
                dead = true;
            }
            for (asteroid_list.loopStart();!asteroid_list.loopEnd();asteroid_list.loopNext()) {
                //Recorre la lista de asteroides para dibujarlos
                asteroid_list.loopGet()->draw(window);
            }
            window.display();
        }
    }
    return EXIT_SUCCESS;
}

void
main_menu(RenderWindow &window, Text &tx_menu, Text &tx_aux1, const Sprite &background1, Spaceship &player, int &score,
          bool &menu, bool &menu_score, bool &life, bool &game, std::stack<int> &stack_score, Event &event) {
    while (menu) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || !window.isOpen()) {
                window.close();
                exit (EXIT_SUCCESS);
            }
        }

        player.setPosition();

        tx_menu.setString("F  A  R ");
        tx_menu.setCharacterSize(80);
        tx_menu.setPosition(175, 150);

        tx_aux1.setString("Press S for look scores\n  Press Enter for play\n     Press Esc to exit");
        tx_aux1.setCharacterSize(40);
        tx_aux1.setPosition(73, 300);

        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            game = true;
            life = true;
            score = 0;
            menu = false;
            break;
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            exit (EXIT_SUCCESS);
        }

        if (Keyboard::isKeyPressed(Keyboard::S)) {
            load_score(stack_score);
            menu_score = true;
            break;
        }

        window.clear();
        window.draw(background1);
        window.draw(tx_aux1);
        window.draw(tx_menu);
        window.display();
    }
}

void score_menu(bool &menu_score, RenderWindow &window, Text &tx_aux1, Text &tx_aux2, Text &tx_aux3,
                  const Sprite &background1, Event &event) {
    while (menu_score) {
        //se crea la cola en donde se van a estar las puntuaciones
        std::queue<String> score_queue;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || !window.isOpen()) {
                window.close();
                exit (EXIT_SUCCESS);
            }
        }
        tx_aux1.setString("SCORES");
        tx_aux1.setCharacterSize(70);
        tx_aux1.setPosition(180, 100);

        tx_aux3.setString("Press Backspace to return");
        tx_aux3.setCharacterSize(40);
        tx_aux3.setPosition(55, 480);

        //pasa las puntuaciopnes del archivo a la cola
        extracData(score_queue);

        if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
            menu_score = false;
            break;
        }



        window.clear();
        window.draw(background1);
        window.draw(tx_aux1);
        window.draw(tx_aux3);

        for (int i = 0; i < 10; i++) {
            if (!score_queue.empty()) {
                tx_aux2.setString(score_queue.front());
                score_queue.pop();
            }
            else
                tx_aux2.setString("0");

            tx_aux2.setCharacterSize(70);
            tx_aux2.setPosition(205, 150 + (i * 30));
            window.draw(tx_aux2);


        }
        window.display();
    }

}

void colisions(Spaceship &player, LinkedList<Asteroid *> &asteroid_list, bool &life) {

    for (int i = 0; i < asteroid_list.size(); ++i) {
        if(Collision::PixelPerfectTest(asteroid_list.get(i)->getSprite(),player.getSprite())){
            life = false;
        }
    }
}

void asteroids(int score, int &clock, LinkedList<Asteroid *> &asteroid_list) {
    if (score <= 500 && clock == 0) {
        int aux = rand() % 3 - 0;
        for (int i = 0; i < aux; ++i) {
            asteroid_list.push_front(new Asteroid(rand() % 9 - 0));
        }
    }
    if (score > 500 && score < 1000 && clock == 0) {
        int aux = rand() % 4 - 0;
        for (int i = 0; i < aux; ++i) {
            asteroid_list.push_front(new Asteroid(rand() % 9 - 0));
        }
    }
    if (score > 1000 && score < 1500 && clock == 0) {
        int aux = rand() % 6 - 0;
        for (int i = 0; i < aux; ++i) {
            asteroid_list.push_front(new Asteroid(rand() % 9 - 0));
        }
    }
    if (score > 1500 && clock == 0) {
        int aux = rand() % 8 - 0;
        for (int i = 0; i < aux; ++i) {
            asteroid_list.push_front(new Asteroid(rand() % 9 - 0));
        }
    }
    for (int i = 0; i < asteroid_list.size(); ++i) {
        if(!asteroid_list.get(i)->move()) {
            asteroid_list.erase(i);
        }

    }
    clock++;
    if (clock == 50)
        clock=0;
}

void dead_menu(bool dead, RenderWindow &window, Text &tx_menu, Text &tx_aux1,
               const Sprite &background1, Spaceship &player,
          int &score, bool &menu, bool &life, bool &game, Event &event) {


    while (dead){
        player.setPosition();

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || !window.isOpen()) {
                window.close();
                exit (EXIT_SUCCESS);
            }
        }

        tx_menu.setString("GAME OVER");
        tx_menu.setCharacterSize(80);
        tx_menu.setPosition(120,0);

        tx_aux1.setString("PRESS Enter TO RESET\nPRESS Backspace TO EXIT");
        tx_aux1.setCharacterSize(40);
        tx_aux1.setPosition(73,480);

        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            score = 0;
            game = true;
            life = true;
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


void extracData(std::queue<String> &score_queue) {
    //TOMAS LOS DATOS QUE SE ENCUENTREN EN EL ARCHIVO
    //LOS PASA A UNA COLA

    String scr;
    std::ifstream reed;
    int aux;
    reed.open("score.txt");
    while (!reed.eof()) {
        reed >> aux;
        scr = std::to_string(aux);
        score_queue.push(scr);

    }
    reed.close();

}

void load_score(std::stack<int> &stack_score) {
    //ABRE EL ARCHIVO EN DONDE SE GUARDA LAS PUNTUACIONES
    //PASA LOS DATOS QUE SE ENCUENTRARN EN EL STACK AL ARCHIVO

    std::ofstream write;
    write.open("score.txt");
    while (true){
        for (int i = 0;!stack_score.empty(); ++i) {
            int a = stack_score.top();
            write << a << std::endl;
            stack_score.pop();
        }
        break;
    }
    write.close();
}


void move_background(float &background_y, const Texture &tex_background, Sprite &sp_background1, Sprite &sp_background2, int score) {
    //HACER QUE EL FONDO SE MUEVA

    if (score <= 500)
        background_y += 3.5;
    else if (score <= 1000)
        background_y += 5.0;
    else if (score > 1000)
        background_y += 7.5;

    if (background_y > tex_background.getSize().y){
        background_y -= tex_background.getSize().y;
    }
    sp_background1.setPosition(0,background_y);
    sp_background2.setPosition(0,background_y - tex_background.getSize().y);
}


void paused(bool &pause, RenderWindow &window, const Sprite &background1, Event &event, Text tx_menu, Text tx_aux1, bool &menu,bool &game) {
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
                exit(EXIT_SUCCESS);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            pause = false;
            break;
        }
        if (Keyboard::isKeyPressed(Keyboard::BackSpace)){
            menu = true;
            game = false;
            break;
        }

        window.clear();
        window.draw(background1);
        window.draw(tx_aux1);
        window.draw(tx_menu);
        window.display();
    }

}

