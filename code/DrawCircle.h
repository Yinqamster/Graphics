#ifndef _DRAWCIRCLE_H_
#define _DRAWCIRCLE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*圆的数据结构*/
class circlePt {
public:
	scrPt center;
	double radius;
	double radiusY;     /*圆通过编辑成为椭圆后用*/
};
/*存储圆的数组*/
extern vector<circlePt> circle;
/*初始化一下变量*/
extern void initCircle();
/*画点*/
extern void setPixel(int x, int y);
/*中点圆算法画圆*/
extern void MidPoint_Circle(scrPt c, double r);
/*8路对称*/
extern void Cirpot(scrPt c, int x, int y);
/*绘制圆的鼠标操作*/
extern void drawCircle(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*将圆存入数组*/
extern void saveCircle(unsigned char key, int x, int y);



#endif
