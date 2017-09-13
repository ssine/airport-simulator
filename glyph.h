#pragma once

#include "struct.h"

class Glyph
{
protected:
public:
    float width, height;
    int texId;
    Point pos;
    void draw();
    bool mouseIn(int x, int y);
};
