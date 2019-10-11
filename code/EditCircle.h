#ifndef _EDITCIRCLE_H_
#define _EDITCIRCLE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawCircle.h"
#include "DrawEllipse.h"

/*初始化一些变量*/
extern void initEditCircle();
/*编辑圆的鼠标点击操作*/
extern void editCircle(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*编辑圆的鼠标移动操作*/
extern void editC(int x, int y);
#endif

