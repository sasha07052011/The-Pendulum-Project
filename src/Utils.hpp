#ifndef MATHUTIL_H
#define MATHUTIL_H

constexpr double PI = 3.14159;
constexpr double G = 9.81;
constexpr int METER = 200;

const int WIDTH = 800;
const int HEIGHT = 450;

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

double v_length(const Vector2f v);
double v_length(const Vector2i v);
double get_angle_from_pos(Vector2f origin, Vector2f pos);
Vector2f get_mouse_pos(RenderWindow &w);
std::wstring format_double(double n, int p);

#endif // MATHUTIL_H
