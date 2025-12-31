#include "KeepView.hpp"

using namespace sf;

KeepView::KeepView(double width, double height): view(FloatRect(0,0,width,height)){}

void KeepView::attach(RenderWindow &w){
    w.setView(view);
}

void KeepView::update(RenderWindow &w, Event &e){
    double size_w = view.getSize().x;
    double size_h = view.getSize().y;

    double coof = size_w/size_h;

    double ev_w = e.size.width;
    double ev_h = e.size.height;

    double res_w = ev_w >= ev_h*coof ? ev_h*coof/ev_w : 1; //Пропр. разм. ширины h/w
    double res_w_b = ev_w >= ev_h*coof ? (1-res_w)/2 : 0; //Отступ от края x
    double res_h = ev_w < ev_h*coof ? ev_w/ev_h/coof : 1; //Пропр. разм. высоты w/h
    double res_h_b = ev_w < ev_h*coof ? (1-res_h)/2 : 0; //Отступ от края y

    view.setViewport(FloatRect(res_w_b,res_h_b,res_w,res_h));

    w.setView(view);
}
