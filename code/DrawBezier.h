#ifndef _DRAWBEZIER_H_
#define _DRAWBEZIER_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include<vector>
#include "DrawLine.h"

/*Beizer曲线的控制点的数据结构*/
class BezierCurvePt {
public:
	vector<scrPt> beizerPt;
};
/*存储Beizer曲线点的数组*/
extern vector<BezierCurvePt> bePt;
/*初始化一些变量*/
extern void initBeizer();
/*画Beizer曲线的鼠标操作*/
extern void drawBeizer(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*画Beizer曲线的算法*/
extern void drawBe(vector<scrPt>p);


#endif