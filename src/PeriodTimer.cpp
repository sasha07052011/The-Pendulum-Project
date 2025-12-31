#include "PeriodTimer.hpp"

using namespace sf;

PeriodTimer::PeriodTimer(): text("fonts/NotoSans.ttf"), text2("fonts/NotoSans.ttf"){
    working = false;
    n = 0;
    text.set_style(Color::Black,18);
    table = nullptr;
    showed = true;

    box_pos = Vector2f(30,HEIGHT-50);

    nums_box.push_back(Line(box_pos,box_pos+Vector2f(0,-S_Y),Color::Black));
    nums_box.push_back(Line(box_pos+Vector2f(0,-S_Y),box_pos+Vector2f(S_X,-S_Y),Color::Black));
    nums_box.push_back(Line(box_pos+Vector2f(S_X,-S_Y),box_pos+Vector2f(S_X,0),Color::Black));
    nums_box.push_back(Line(box_pos+Vector2f(S_X,0),box_pos,Color::Black));

    text2.set_style(Color::Black,10,Text::Italic);
    text2.set_text(L"Секундомер");
    text2.make_central(false);
    text2.set_position(box_pos+Vector2f(0,-S_Y-15));
}

void PeriodTimer::process(RenderWindow &window){
    std::wstring n_text = L"000.00 с.";
    text.set_style(Color::Black,18);

    if(table != nullptr && n >= (*table).c_num){
        showed = false;
        n_text = L"Табл. зап.";
        text.set_style(Color::Blue,18);
    }

    if(working && showed){
        std::wstring raw_s = format_double(clock.getElapsedTime().asSeconds(),2);
        constexpr int NUMS_K = 6;
        int sz = raw_s.length();
        if(sz > NUMS_K){
            raw_s.erase(0,sz-NUMS_K);
            n_text = raw_s;
        }else if(sz < NUMS_K){
            n_text.clear();
            for(int i = 0; i!=NUMS_K-sz;i++){
                n_text.push_back('0');
            }
            n_text.append(raw_s);
        }

        n_text.append(L" с.");
        text.set_style(Color::Red,18);
    }

    text.set_text(n_text);
    text.set_position(box_pos+Vector2f(S_X/2,-S_Y/2));
    text.draw(window);

    for(Line l : nums_box){
        l.draw(window);
    }

    text2.draw(window);
}

void PeriodTimer::link(Table *t){
    table = t;
}

void PeriodTimer::start(){
    working = true;
    clock.restart();
}

void PeriodTimer::end(){
    if(table != nullptr){
        if(n < (*table).c_num){
            (*table).set_var(n,clock.getElapsedTime().asMilliseconds()/1000.0);
            ++n;
        }
    }

    clock.restart();
    working = false;
}

void PeriodTimer::reset(){
    n = 0;
    showed = true;
}
