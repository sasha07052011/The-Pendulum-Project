#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "src/Pendulum.hpp"
#include "src/Ruler.hpp"
#include "src/TextDrawer.hpp"
#include "src/Protractor.hpp"
#include "src/ui/Table.hpp"
#include "src/ui/KeepView.hpp"
#include "src/PeriodTimer.hpp"

const std::wstring INFO(L"Очистка рабочего простр.: R, Измерение длины: Левая кн. мыши,\nИзменение угла маятника: Правая кн. мыши, Пауза/Запуск: Q, Секундомер: Пробел, Выход: ESC");
const std::wstring TITLE(L"Модель математического маятника");

using namespace sf;

double random_l(){
    return std::rand()/(double)(RAND_MAX)+0.5;
}

int main(){
    std::cout << "Autor: Smsxz (https://pikabu.ru/@smsxz, https://vk.com/smsxz). Using SFML library and NotoSans font." << std::endl;

    RenderWindow screen(VideoMode(WIDTH,HEIGHT),"The Pendium Project",Style::Fullscreen);
    TextDrawer text("fonts/NotoSans.ttf");
    text.set_position(Vector2f(50,20));
    text.set_text(L"Пауза");

    int pause_alpha = 0xFF;

    KeepView view(WIDTH,HEIGHT);
    view.attach(screen);

    Table lengths(5,200,150,L"L (см)",1);
    lengths.set_title(L"Табл. 1. Измерение длины маятника");
    Table times(5,200,150,L"t (с)");
    times.set_title(L"Табл. 2. Измерение времени N колебаний");

    lengths.move(Vector2f(WIDTH/3.0*2.0, 50));
    times.move(Vector2f(WIDTH/3.0*2.0, 250));

    screen.setFramerateLimit(60);

    std::srand(std::time(nullptr));

    Pendulum p1(random_l(),0,Vector2f(WIDTH/2-WIDTH/6,50),Color(0xDDDDDDFF));

    Ruler r(screen);
    PeriodTimer t;

    r.link(&lengths);
    t.link(&times);

    bool runned = false;
    int frame = 0;
    double delta = 1.0/60.0;

    RectangleShape bg(Vector2f(screen.getSize()));
    bg.setFillColor(Color::White);

    Clock clk;
    Clock global_t;

    while(screen.isOpen()){
        Event event;

        while(screen.pollEvent(event)){
            if(event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
                screen.close();
            }else if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Q){
                    runned = !runned;
                    if(!runned){
                        p1.reset();
                    }else{
                        global_t.restart();
                    }
                }
            }else if(event.type == Event::Resized){
                view.update(screen,event);
            }

            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                r.update_state(Ruler::States::FirstClick);
            }else if(event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left){
                r.update_state(Ruler::States::None);
            }

            if(Keyboard::isKeyPressed(Keyboard::R)){
                lengths.reset_data();
                times.reset_data();
                r.update_state(Ruler::States::Reset);
                t.reset();
                p1.deep_reset(random_l());
            }
        }

        screen.clear(Color::Black);
        screen.draw(bg);

        if(runned){
            p1.process(delta,runned,screen,global_t.getElapsedTime().asSeconds());
        }else{
            p1.process(delta,runned,screen,0);
        }

        p1.draw(screen,delta);
        r.render();
        t.process(screen);

        if(Keyboard::isKeyPressed(Keyboard::Space) && !t.working){
            t.start();
        }else if(!Keyboard::isKeyPressed(Keyboard::Space) && t.working){
            t.end();
        }

        if(!runned){
            text.make_central(false);
            text.set_text(L"Пауза");
            pause_alpha = (int)(std::abs(std::sin(frame/30.0))*0xFF);
            text.set_style(Color(pause_alpha),13);
            text.set_position(Vector2f(30,15));
            text.draw(screen);
        }

        text.make_central(false);
        text.set_text(INFO);
        text.set_style(Color::Black,11);
        text.set_position(Vector2f(30,HEIGHT-40));
        text.draw(screen);

        text.make_central(true);
        text.set_text(TITLE);
        text.set_style(Color::Black,18,Text::Italic | Text::Underlined);
        text.set_position(Vector2f(WIDTH/2,10));
        text.draw(screen);

        lengths.render(screen);
        times.render(screen);

        screen.display();

        delta = clk.getElapsedTime().asSeconds();
        clk.restart();
        frame++;
    }

    return 0;
}
