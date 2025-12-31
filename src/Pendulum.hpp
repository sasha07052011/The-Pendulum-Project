#ifndef PENDIUM_H
#define PENDIUM_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

#include "Line.hpp"
#include "Utils.hpp"
#include "Protractor.hpp"

using namespace sf;

class Pendulum{
    public:

    Pendulum();
    Pendulum(double l,double t, Vector2f pos, Color pc);
    void process(double delta, bool do_physics, RenderWindow &w, double t);
    void draw(RenderWindow &window, double d);
    double get_theta();
    void reset();
    void deep_reset(double l);

//и зачем вы меня читаете?

    private:

    double length;
    double theta;
    double max_theta;
    double v;
    Protractor r;
    RectangleShape stick;
    CircleShape point;
    CircleShape cargo;
    Vector2f position;
};

#endif // PENDIUM_H
