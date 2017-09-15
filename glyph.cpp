#include "stdafx.h"
#include <GL/glut.h>
#include "view.h"
#include "glyph.h"

#include <iostream>
using namespace std;

bool Glyph::mouseIn(int x, int y) {
    if(
        curWindowWidth/2*(pos.x+1) < x && x < curWindowWidth/2*(pos.x+width+1)
        && curWindowHeight/2*(-pos.y-height+1) < y && y < curWindowHeight/2*(-pos.y+1)
    ) return true;
    else return false;
}

void Glyph::draw() {
    glEnable(GL_TEXTURE_2D);//图像有效化
    glBindTexture( GL_TEXTURE_2D, texId );
    glEnable(GL_ALPHA_TEST);//试描画开始
    glAlphaFunc(GL_GREATER, 0.5);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(pos.x, pos.y);//左下
	glTexCoord2f(0.0f, 1.0f); glVertex2f(pos.x, pos.y + height);//左上
	glTexCoord2f(1.0f, 1.0f); glVertex2f(pos.x + width, pos.y + height);//右上
	glTexCoord2f(1.0f, 0.0f); glVertex2f(pos.x + width, pos.y);//右下
	glEnd();
	glDisable(GL_ALPHA_TEST);//试描画结束
    glDisable(GL_TEXTURE_2D);//图像无效
}
