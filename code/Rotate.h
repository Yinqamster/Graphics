#ifndef _ROTATE_H_
#define _ROTATE_H_

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
extern void initRotate();
/*判断旋转的图形*/
extern void judgeShapeR();
/*旋转的鼠标操作*/
extern void rotate(GLint button, GLint action, GLint xMouse, GLint yMouse);

#endif 