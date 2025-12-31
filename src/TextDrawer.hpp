#ifndef TEXT_DRAWER_H
#define TEXT_DRAWER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class TextDrawer{

    public:

    TextDrawer(std::string path);
    void set_position(Vector2f pos);
    void set_style(Color c, unsigned int t_size, uint32_t style = Text::Regular);
    void set_text(std::wstring text);
    void draw(RenderWindow &window);
    void make_central(bool b);

    Text t;

    private:

    Font f;
    bool centered;
};

#endif // TEXT_DRAWER_H
