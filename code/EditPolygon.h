#ifndef _EDITLPOLYGON_H_
#define _EDITLPOLYGON_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawPolygon.h"
#include "DrawLine.h"
#include "FillArea.h"

/*初始化一些变量*/
extern void initEditPolygon();
/*编辑多边形的鼠标点击操作*/
extern void editPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*编辑多边形的鼠标拖动操作*/
extern void editP(int x, int y);
#endif

