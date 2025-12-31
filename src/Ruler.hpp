#ifndef RULER_H
#define RULER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Line.hpp"
#include "ui/Table.hpp"
#include "Utils.hpp"

using namespace sf;

class Ruler{
    public:

    enum class States{None,FirstClick,Reset};

    Ruler(RenderWindow &w);
    void render();
    void update_state(Ruler::States state);
    void link(Table *t);

    private:

    Vector2f start_point;
    bool pressed;
    bool drawed;

    Line begin_l;
    Line end_l;
    Line line;

    Font f;
    Text t;

    Table *linked;
    int num;

    RenderWindow &window;
};

#endif // RULER_H
