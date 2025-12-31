#include "Table.hpp"

using namespace sf;

Table::Table(): Table(5,200,200){};

Table::Table(int n, double size_x, double size_y, std::wstring name, int show_n): text("fonts/NotoSans.ttf"){
    show_nums = show_n;

    double info_c_size_r_x = size_x * INFO_C_SIZE_X;
    double info_c_size_r_y = size_y * INFO_C_SIZE_Y;
    Color c(0x000000FF);

    size = Vector2f(size_x,size_y);

    for(int i = 0; i!=n; ++i){
        data[i] = 0;
        double one_element_size = (size_y-info_c_size_r_y)/n;
        double posy = one_element_size*i+info_c_size_r_y;
        lines.push_back(Line(Vector2f(0,posy),Vector2f(size_x,posy),c));
        strings.push_back(std::pair(Vector2f(info_c_size_r_x/2,posy+one_element_size/2),std::to_wstring(i+1)));
    }

    lines.push_back(Line(Vector2f(0,0),Vector2f(0,size_y),c));
    lines.push_back(Line(Vector2f(0,0),Vector2f(size_x,0),c));
    lines.push_back(Line(Vector2f(size_x,0),Vector2f(size_x,size_y),c));
    lines.push_back(Line(Vector2f(0,size_y),Vector2f(size_x,size_y),c));

    lines.push_back(Line(Vector2f(0,info_c_size_r_y),Vector2f(size_x,info_c_size_r_y),c));
    lines.push_back(Line(Vector2f(info_c_size_r_x,0),Vector2f(info_c_size_r_x,size_y),c));

    strings.push_back(std::pair(Vector2f(info_c_size_r_x/2, info_c_size_r_y/2), L"№"));
    strings.push_back(std::pair(Vector2f((size_x-info_c_size_r_x)/2+info_c_size_r_x, info_c_size_r_y/2), name));

    text.set_style(c,14);
    c_num = n;
}


void Table::render(RenderWindow &window){
    text.make_central(false);
    text.set_style(Color::Black,10,Text::Italic);
    text.set_text(title);
    text.set_position(pos+Vector2f(0,-15));
    text.draw(window);

    for(Line l : lines){
        l.move(pos);
        l.draw(window);
        l.move(-pos);
    }

    for(std::pair<Vector2f,std::wstring> p : strings){
        text.make_central(true);
        text.set_style(Color::Black,14);
        text.set_text(p.second);
        text.set_position(p.first + pos);
        text.draw(window);
    }

    double l1 = size.x * INFO_C_SIZE_X;
    double l2 = size.y * INFO_C_SIZE_Y;
    double x = l1 + (size.x-l1)/2;
    double el_size = (size.y-l2)/c_num/2;

    for(std::pair<int,double> d : data){
        Vector2f d_p;

        d_p.x = x;
        d_p.y = l2 + (size.y-l2)/c_num*d.first+el_size;

        std::wstring s = format_double(d.second,show_nums);

        text.set_text(s);
        text.set_position(d_p + pos);
        text.draw(window);
    }
}

void Table::move(Vector2f mpos){
    pos = mpos;
}

void Table::set_var(int n, double v){
    data[n] = v;
}

void Table::reset_data(){
    for(std::pair<int,double> d : data){
        data[d.first] = 0;
    }
}

void Table::set_title(std::wstring t){
    title = t;
}
