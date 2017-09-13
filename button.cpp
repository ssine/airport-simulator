#include "stdafx.h"
#include "button.h"
#include "function.h"
#include "glyph.h"
#include "view.h"
#include <GL/glut.h>
#include "globalvar.h"

#include <iostream>
using namespace std;

extern texName a;
extern int texId[];

Button::Button(float x, float y, texName name) {
    pos.x = x; pos.y = y;
    width = 0.07; height = 0.1;
    texId = ::texId[name];
    initId = texId;
    cout << ::texId[name] << endl;
    cout << "constructured!" <<endl;
}

void Button::mouseMove(int x, int y) {
    if(mouseIn(x, y)) {
        texId = initId + 1;
    } else {
        texId = initId;
    }
}

void Button::mouseClick(int btn, int state, int x, int y) {
    if(mouseIn(x, y) && state == GLUT_DOWN) {
        texId = initId + 2;
        //dosomething
		if (texId == ::texId[button_normal] + 2) {
			aniWindow = true;
		} else if(texId == ::texId[arrow_left_normal] + 2) {
            if(*corspVar > 1) *corspVar -= 1;
            writeSettingFile();
        } else if(texId == ::texId[arrow_right_normal] + 2) {
            *corspVar += 1;
            writeSettingFile();
        }
    }
}
