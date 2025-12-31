#ifndef KEEPVIEW_H
#define KEEPVIEW_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class KeepView{
    public:

    KeepView(double width,double height);
    void attach(RenderWindow &w);
    void update(RenderWindow &w, Event &e);

    private:

    View view;
    double width,height;
};

#endif // KEEPVIEW_H
