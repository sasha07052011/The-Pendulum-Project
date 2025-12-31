#ifndef PROTRACTOR_H
#define PROTRACTOR_H

#include "TextDrawer.hpp"
#include "Line.hpp"
#include "Utils.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

using namespace sf;

constexpr int VERTEX_COUNT = 30;
constexpr double RADIUS = METER / 2;
constexpr double NOT_INDICATOR_L = 0.9;
constexpr double NOT_INDICATOR_L_BIG = 0.8;
constexpr double TEXT_RADIUS_K = 1.1;
constexpr double INDICATOR_SIZE_FROM_R = 0.1;
constexpr int ONE_P = 3;

//Виверна оъелась яблоками. Как я объелся ошибками линковки при билде проекта.

class Protractor{
    public:

    Protractor();
    void render(RenderWindow &window, bool flip = false, bool set_pos = false, Vector2f setting_pos = Vector2f(0,0));

    private:

    Vector2f pos;
    TextDrawer text;
    TextDrawer info;
    std::vector<Line> lines;
    std::vector<Vector3f> angles;
};

#endif // PROTRACTOR_H
