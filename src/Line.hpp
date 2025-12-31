#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Line{
    public:

    Line();
    Line(Vector2f begin_l, Vector2f end_l, Color c);
    void setPoints(Vector2f begin_l, Vector2f end_l);
    void setColor(Color c);
    void draw(RenderWindow &window);
    void move(Vector2f pos);
    void flip_x();

    private:

    VertexArray data;
};

#endif // LINE_H
