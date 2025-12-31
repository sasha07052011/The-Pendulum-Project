#include "Protractor.hpp"

using namespace sf;

Protractor::Protractor(): text("fonts/NotoSans.ttf"),info("fonts/NotoSans.ttf"){
    double angle = 0;
    double old_a = 0;
    Color c = Color::Black;

    info.make_central(false);
    std::wstring t = L"Одно деление\nравно ";
    t.append(std::to_wstring(ONE_P));
    t.append(L"°");
    info.set_text(t);
    info.set_style(Color::Black,8,Text::Italic);

    lines.push_back(Line(Vector2f(0,RADIUS * INDICATOR_SIZE_FROM_R),Vector2f(0,RADIUS * -INDICATOR_SIZE_FROM_R),c));

    for(int i = 0;i!=VERTEX_COUNT;i++){
        old_a = angle;
        angle += PI / VERTEX_COUNT;

        Vector2f first_p,second_p,back_p;

        first_p.x = std::cos(old_a) * RADIUS;
        first_p.y = -std::sin(old_a) * RADIUS;
        second_p.x = std::cos(angle) * RADIUS;
        second_p.y = -std::sin(angle) * RADIUS;

        lines.push_back(Line(first_p,second_p,c));
    }

    for(double a = 0;a != 180;a+=15){
        Vector2f second_p,back_p,text_p;
        double ra = a / 180 * PI;

        second_p.x = std::cos(ra) * RADIUS;
        second_p.y = -std::sin(ra) * RADIUS;
        text_p.x = -std::cos(ra) * RADIUS * TEXT_RADIUS_K;
        text_p.y = -std::sin(ra) * RADIUS * TEXT_RADIUS_K;
        back_p.x = std::cos(ra) * RADIUS * NOT_INDICATOR_L_BIG;
        back_p.y = -std::sin(ra) * RADIUS * NOT_INDICATOR_L_BIG;

        lines.push_back(Line(second_p,back_p,c));
        angles.push_back(Vector3f(text_p.x,text_p.y,a));
    }

    angles.push_back(Vector3f(RADIUS * TEXT_RADIUS_K,0,180));

    for(double a = 0;a != 180;a+=ONE_P){
        Vector2f second_p,back_p;
        double ra = a / 180 * PI;

        second_p.x = std::cos(ra) * RADIUS;
        second_p.y = -std::sin(ra) * RADIUS;
        back_p.x = std::cos(ra) * RADIUS * NOT_INDICATOR_L;
        back_p.y = -std::sin(ra) * RADIUS * NOT_INDICATOR_L;

        lines.push_back(Line(second_p,back_p,c));
    }

    lines.push_back(Line(Vector2f(-RADIUS,0),Vector2f(RADIUS,0),c));
    text.set_style(c,10);
}


void Protractor::render(RenderWindow &window, bool flip, bool set_pos, Vector2f setting_pos){
    if(!set_pos){
        pos = window.mapPixelToCoords(Mouse::getPosition(window));
    }else{
        pos = setting_pos;
    }

    if(!flip){
        for(Line l : lines){
            l.move(pos);
            l.draw(window);
            l.move(-pos);
        }
    }else{
        for(Line l : lines){
            l.flip_x();
            l.move(pos);
            l.draw(window);
            l.move(-pos);
            l.flip_x();
        }
    }

    for(Vector3f data : angles){
        text.set_text(std::to_wstring((int) data.z) + L"°");
        if(!flip){
            text.set_position(Vector2f(data.x,data.y) + pos);
        }else{
            text.set_position(Vector2f(data.x,-data.y) + pos);
        }
        text.draw(window);
    }

    info.set_position(Vector2f(-METER*0.35,-23+(flip*27))+pos);
    info.draw(window);
}
