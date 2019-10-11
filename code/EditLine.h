#ifndef _EDITLINE_H_
#define _EDITLINE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawLine.h"

/*初始化一些变量*/
extern void initEditLine();
/*编辑直线的鼠标点击操作*/
extern void editLine(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*编辑直线的鼠标拖动操作*/
extern void editL(int x, int y);
#endif

