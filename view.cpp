#include "stdafx.h"
#include "view.h"
#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;

// 窗口名称
const char* windowTitle = "测试样例";

// texWidth[texName] 为预设的宽高
enum texName { _passenger, _checkPoint, _serpQueue, _restArea };
float texWidth[20] = {0.3, 0.5, 1.4, 1.7};
float texHeight[20] = {0.3, 0.5, 1, 0.5};
int texId[100];

// 动画步长
float step = 0.005;
// 距离终点多远时停止
float stopEps = 0.01;

// 控制FPS
int FPS = 30;
int timeInterval;

// 测试用
std::vector<Passenger> q;


void show(int argc, char *argv[]) {
    //glut设定
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(windowTitle);
    
    //初始化
    drawInit();
    
    //初始绘图函数
    glutDisplayFunc(display);
    flush(1);
    
    //进入主循环
    glutMainLoop();
}

void display() { } // 在窗口改变大小时调用，不灵活，先不用了

void drawInit() {

    q.push_back(Passenger());
    q.push_back(Passenger(0.3, 0));
    q[0].endPoint = Point::Point(0, 0.7);
    q[1].endPoint = Point::Point(0.7, 0);


    // 设定空白色
    glClearColor(0.5, 0.5, 0.5, 1.0);
    
    // 测试回调函数
    glutKeyboardFunc(onEscPressed);
    // 计算Timer时间
    timeInterval = 1000 / FPS;
    // 读取材质
    loadTexture();
}


void drawObject(texName name, Point& pos, float width=0.0, float height=0.0) {
/* 已封装好，传入名字画出对应对象，参数1名字 2位置 34宽高(无则使用预设) */

    glEnable(GL_TEXTURE_2D);//图像有效化
    glBindTexture( GL_TEXTURE_2D, texId[name] );
    if(width < 0.001) width = texWidth[name];
    if(height < 0.001) height = texHeight[name];
    //cout << name << ' ' << pos.x << ' ' << pos.y << ' ' << width << ' ' << height << endl;
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



// 键鼠操作回调函数
void onEscPressed(unsigned char key, int x, int y) {
    if(key == 27) glutHideWindow();
}


// 辅助绘图
inline float sym(float a, float b) {
    if(std::abs(a - b) < stopEps) return 0.0f;
    else if(a - b > 0) return -1.0f;
    else return 1.0f;
}
// 每一帧的绘图函数
void flush(int value) {
    glutTimerFunc(timeInterval, flush, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cout << "flushing..." << endl;

    drawObject(_serpQueue, Point(-0.5, -0.2));
    for(int i = 0; i < q.size(); i++) {
        if(q[i].needMove) {
            q[i].pos.x += sym(q[i].pos.x, q[i].endPoint.x) * step;
            q[i].pos.y += sym(q[i].pos.y, q[i].endPoint.y) * step;
            if(Point::norm(q[i].pos, q[i].endPoint) < stopEps) q[i].needMove = false;
        }
        drawObject(_passenger, q[i].pos);
        cout << "drawn " << endl;
    }

    glutSwapBuffers();
}




// 读取材质，要用GIF的话需要重写
void loadTexture() {
    texId[_passenger] = SOIL_load_OGL_texture(
        ".\\source\\passenger.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    texId[_checkPoint] = SOIL_load_OGL_texture(
        ".\\source\\checkPoint.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    texId[_serpQueue] = SOIL_load_OGL_texture(
        ".\\source\\serpQueue.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    texId[_restArea] = SOIL_load_OGL_texture(
        ".\\source\\restArea.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
}

// 点结构体的实现
Point::Point() { x = 0.0f; y = 0.0f; }
Point::Point(float a, float b) : x(a), y(b) { }
Point::Point(const Point& p) { x = p.x; y = p.y; }
Point& Point::operator = (const Point& p) { x = p.x; y = p.y; return *this; }

