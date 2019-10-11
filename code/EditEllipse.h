#ifndef _EDITELLIPSE_H_
#define _EDITELLIPSE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawEllipse.h"

/*初始化一些变量*/
extern void initEditEllipse();
/*编辑椭圆的鼠标点击操作*/
extern void editEllipse(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*编辑椭圆的鼠标拖动操作*/
extern void editE(int x, int y);
#endif

