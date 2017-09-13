#pragma once

#include "glyph.h"
#include "globalvar.h"

class Button : public Glyph
{
    int initId;
public:
    int* corspVar;
    int step;
    Button(float x, float y, texName name);
    void mouseMove(int x, int y);
    void mouseClick(int btn, int state, int x, int y);
};
