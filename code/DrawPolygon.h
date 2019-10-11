#ifndef _DRAWPOLYGON_H_
#define _DRAWPOLYGON_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*多边形的数据结构*/
class polygonPt {
public:
	vector<scrPt> point;
	char color;
};
/*存储多边形的数组*/
extern vector<polygonPt> polygon;
/*初始化一些变量*/
extern void initPolygon();
/*绘制多边形的鼠标操作*/
extern void drawPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse);

#endif 