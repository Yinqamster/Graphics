#ifndef _DRAWBCURVE_H_
#define _DRAWBCURVE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawLine.h"

/*B样条曲线控制点的数据结构*/
class BCurvePt {
public:
	vector<scrPt> bPt;
};
/*存储B样条曲线控制点的数组*/
extern vector<BCurvePt> bCurve;
/*绘制B样条曲线的算法*/
extern void drawB(vector<scrPt>p);
/*初始化一些变量*/
extern void initBCurve();
/*绘制B样条曲线的鼠标操作*/
extern void drawBCurve(GLint button, GLint action, GLint xMouse, GLint yMouse);


#endif
