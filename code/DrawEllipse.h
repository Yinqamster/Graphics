#ifndef _DRAWELLIPSE_H_
#define _DRAWELLIPSE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*椭圆的数据结构*/
class ellipsePt {
public:
	scrPt center;
	double longAxis, minAxis;
};
/*存储椭圆的数组*/
extern vector<ellipsePt> ellipse;
/*初始化一些变量*/
extern void initEllipse();
/*画椭圆的鼠标操作*/
extern void drawEllipse(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*将椭圆存入数组*/
extern void saveEllipse(unsigned char key, int x, int y);
/*中点椭圆算法*/
extern void middle_ellipse(scrPt center, double longAxis, double minAxis);
#endif
