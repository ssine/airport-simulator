#pragma once

#include "glyph.h"
#include "globalvar.h"
#include "checkpoint.h"

class Button : public Glyph
{
    int initId;
public:
    int* corspVar;
    int corspCP;
    int step;
    Button(texName name, float x, float y, float width, float height);
    void mouseMove(int x, int y);
    void mouseClick(int btn, int state, int x, int y);
};
