#include "Ruler.hpp"

using namespace sf;

Ruler::Ruler(RenderWindow &w): window(w){
    start_point = Vector2f(0,0);
    linked = nullptr;
    pressed = false;
    drawed = true;
    if(!f.loadFromFile("fonts/NotoSans.ttf")){
        std::cout << "АЛЯРМА!" << std::endl;
        throw std::runtime_error("ГДЕ ШРИФТ!? Переустановите программу!");
    }
    t.setFont(f);
    t.setFillColor(Color(0xFF0000FF));
    t.setCharacterSize(13);
}

void Ruler::render(){
    if(pressed && drawed){
        Vector2f mp = get_mouse_pos(window);

        line.setPoints(start_point,mp);
        line.setColor(Color::Red);
        line.draw(window);

        Vector2f dir = start_point - mp;
        double l = v_length(dir);
        dir = Vector2f(dir.x / l,dir.y / l);

        begin_l.setPoints(Vector2f(-dir.y*10,dir.x*10)+start_point,Vector2f(-dir.y*-10,dir.x*-10)+start_point);
        begin_l.setColor(Color::Red);
        begin_l.draw(window);

        end_l.setPoints(Vector2f(-dir.y*10,dir.x*10)+mp,Vector2f(-dir.y*-10,dir.x*-10)+mp);
        end_l.setColor(Color::Red);
        end_l.draw(window);

        l = ((int)(l/METER*10000))/100.0;

        std::wstring s = std::to_wstring(l);
        s = format_double(l,1);
        s.append(L" см");
        t.setString(s);
        t.setPosition(Vector2f(mp)+Vector2f(20,0));
        window.draw(t);
    }
}

void Ruler::update_state(Ruler::States state){
    if(state == States::FirstClick){
        start_point = get_mouse_pos(window);
        pressed = true;
        if(num > 4){
            drawed = false;
        }
    }else if(state == States::None){
        Vector2f dir = start_point - get_mouse_pos(window);
        double l = v_length(dir) / METER * 100;
        start_point = Vector2f(-1,-1);
        if(linked != nullptr && num < 5){
            (*linked).set_var(num,l);
            ++num;
        }
        pressed = false;
    }else if(state == States::Reset){
        num = 0;
        drawed = true;
    }
}

void Ruler::link(Table *t){
    linked = t;
    num = 0;
}
