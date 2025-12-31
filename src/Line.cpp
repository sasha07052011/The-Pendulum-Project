#include "Line.hpp"

using namespace sf;

Line::Line(Vector2f b, Vector2f e, Color c): data(Lines,2){
    data[0].position = b;
    data[0].color = c;
    data[1].position = e;
    data[1].color = c;
}

Line::Line(): Line(Vector2f(10,10),Vector2f(1000,1000),Color(0x00FF00FF)){}


void Line::setColor(Color c){
    data[0].color = c;
    data[1].color = c;
}

void Line::setPoints(Vector2f b, Vector2f e){
    data[0].position = b;
    data[1].position = e;
}

void Line::draw(RenderWindow &window){
    window.draw(data);
}

void Line::move(Vector2f pos){
    data[0].position += pos;
    data[1].position += pos;
}

void Line::flip_x(){
    data[0].position.y = -data[0].position.y;
    data[1].position.y = -data[1].position.y;
}
