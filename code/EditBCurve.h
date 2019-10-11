#ifndef _EDITBCURVE_H_
#define _EDITBCURVE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawBCurve.h"

/*初始化一些变量*/
extern void initEditBCurve();
/*编辑B样条曲线的鼠标点击操作*/
extern void editBCurve(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*编辑B样条曲线的鼠标拖动操作*/
extern void editB(int x, int y);
#endif

