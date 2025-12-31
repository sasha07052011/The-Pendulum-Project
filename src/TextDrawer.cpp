#include "TextDrawer.hpp"

using namespace sf;

TextDrawer::TextDrawer(std::string path){
    centered = true;
    if(!f.loadFromFile(path)){
        throw std::runtime_error(path + std::string("не существует!"));
    }
    f.setSmooth(true);
    t.setFont(f);
    t.setString(L"");
}

void TextDrawer::set_position(Vector2f pos){
    if(centered){
        double l = t.getLocalBounds().width;
        double h = t.getLocalBounds().height;
        t.setPosition(pos - Vector2f(l/2,h/2));
    }else{
        t.setPosition(pos);
    }
}

void TextDrawer::set_style(Color c, unsigned int t_size, uint32_t style){
    t.setFillColor(c);
    t.setCharacterSize(t_size);
    t.setStyle(style);
}

void TextDrawer::set_text(std::wstring text){
    t.setString(text);
}

void TextDrawer::draw(RenderWindow &window){
    window.draw(t);
}

void TextDrawer::make_central(bool b){
    centered = b;
}
