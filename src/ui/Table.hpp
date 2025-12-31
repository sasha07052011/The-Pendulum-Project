#ifndef TABLE_H
#define TABLE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <map>
#include "../Line.hpp"
#include "../TextDrawer.hpp"
#include "../Utils.hpp"
#include <iostream>

using namespace sf;

constexpr double INFO_C_SIZE_X = 0.2;
constexpr double INFO_C_SIZE_Y = 0.2;

class Table{
    public:

    Table();
    Table(int n, double size_x, double size_y, std::wstring name = L"Длины (см)", int show_n = 2);

    void set_var(int n, double v);
    void render(RenderWindow &window);
    void move(Vector2f mpos);
    void reset_data();
    void set_title(std::wstring t);

    int c_num;

    private:

    std::vector<Line> lines;
    std::vector<std::pair<Vector2f,std::wstring> > strings;
    std::map<int,double> data;
    TextDrawer text;
    Vector2f pos;
    Vector2f size;
    int show_nums;
    std::wstring title;
};

#endif
