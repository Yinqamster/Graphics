#ifndef _ZOOM_H_
#define _ZOOM_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawLine.h"
#include "DrawCircle.h"
#include "DrawEllipse.h"
#include "DrawPolygon.h"
#include "DrawBezier.h"
#include "DrawBCurve.h"
#include "FillArea.h"

/*初始化一些变量*/
extern void initZoom();
/*判断旋转图形的形状*/
extern void judgeShapeZ();
/*旋转的鼠标操作*/
extern void zoom(GLint button, GLint action, GLint xMouse, GLint yMouse);
#endif
