#include "Utils.hpp"

//Обычный коментарий. Для красоты. Не обращайте на него внимание.

using namespace sf;

double v_length(const sf::Vector2f v){
    return std::sqrt(v.x*v.x + v.y * v.y);
}

double v_length(const sf::Vector2i v){
    return std::sqrt(v.x*v.x + v.y * v.y);
}

double get_angle_from_pos(Vector2f origin, Vector2f pos){
    Vector2f sub = pos - origin;
    float l = v_length(sub);
    Vector2f dir = Vector2f(sub.x/l,sub.y/l);
    return std::atan(dir.x/-std::clamp(dir.y,0.0f,65536.0f)) / PI * 180;
}

Vector2f get_mouse_pos(RenderWindow &w){
    Vector2i p = Mouse::getPosition(w);
    return w.mapPixelToCoords(p);
};

std::wstring format_double(double n, int p){
    std::wstring r = std::to_wstring(n);
    r = r.erase(r.find('.')+p+1,r.length());
    return r;
}
