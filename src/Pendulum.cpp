#include "Pendulum.hpp"

bool DRAW_V = false;

using namespace sf;

Pendulum::Pendulum(): Pendulum(1,0,Vector2f(0,0),Color(0xFFFFFFFF)){}

Pendulum::Pendulum(double l,double t, Vector2f pos, Color pc){
    theta = t;
    length = l;
    position = pos;

    point.setRadius(10);
    point.setOrigin(10,10);
    point.setPosition(pos);
    point.setFillColor(pc);

    stick.setSize(Vector2f(5,length*METER));
    stick.setOrigin(2.5,2.5);
    stick.setRotation(theta);
    stick.setFillColor(Color(0xAAAAAAFF)*pc);
    stick.setPosition(pos);

    cargo.setRadius(25);
    cargo.setOrigin(25,-length*METER+25);
    cargo.setRotation(theta);
    cargo.setFillColor(Color(0xCCCCCCFF)*pc);
    cargo.setPosition(pos);
}

double Pendulum::get_theta(){
    return theta;
}

void Pendulum::process(double d, bool do_physics, RenderWindow &w, double t){
    if(do_physics){
        //v += (-G / length * std::sin((theta/180.0)*PI))*d;
        theta = max_theta * std::cos(std::sqrt(G/length)*t);
    }else{
        v = 0;
        if(Mouse::isButtonPressed(Mouse::Right))
            theta = max_theta = get_angle_from_pos(position,get_mouse_pos(w));
    }

    stick.setRotation(theta);
    cargo.setRotation(theta);
}

void Pendulum::draw(RenderWindow &window, double d){
    r.render(window,true,true,position);

    window.draw(stick);
    window.draw(point);
    window.draw(cargo);

    Vector2f first_p;
    first_p.x = -length*METER*sin(theta/180*PI) + position.x;
    first_p.y = length*METER*cos(theta/180*PI) + position.y;

    Vector2f second_p;
    second_p.x = -length*METER*sin((theta+(v/d))/180*PI) + position.x;
    second_p.y = length*METER*cos((theta+(v/d))/180*PI) + position.y;
}

void Pendulum::reset(){
    theta = 0;
    v = 0;
}

void Pendulum::deep_reset(double l){
    reset();
    length = l;

    stick.setSize(Vector2f(5,length*METER));
    cargo.setOrigin(25,-length*METER+25);
}
