#ifndef PERIODTIMER_H
#define PERIODTIMER_H

#include "ui/Table.hpp"
#include "TextDrawer.hpp"
#include "PeriodTimer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Line.hpp"

using namespace sf;

constexpr double S_X = 100;
constexpr double S_Y = 30;

class PeriodTimer{
    public:

    PeriodTimer();
    void link(Table *t);
    void start();
    void end();
    void process(RenderWindow &window);
    void reset();

    bool working;
    bool showed;

    private:

    Table *table;
    int n;
    Clock clock;
    TextDrawer text;
    TextDrawer text2;
    std::vector<Line> nums_box;
    Vector2f box_pos;
};

#endif // PERIODTIMER_H
