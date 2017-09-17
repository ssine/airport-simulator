#pragma once

#include <string>

struct Entry
{
    int no;
    int sec;
    char type;
    int mans;
    int check;
};

struct Point {
    float x, y;
    Point();
    Point(float a, float b);
    Point(const Point& p);
    Point& operator = (const Point& p);
    Point operator + (const Point& p);
    Point operator * (const float m);
    bool operator == (const Point& p);
    inline static float Point::norm(const Point& a, const Point& b) {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }
};

