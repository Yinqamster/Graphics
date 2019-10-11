#ifndef _Translation_H_
#define _Translation_H_

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
extern void initTranslation();
/*判断移动形状*/
extern void judgeShape();
/*平移图形时的鼠标点击操作*/
extern void translation(GLint button, GLint action, GLint xMouse, GLint yMouse);

#endif 