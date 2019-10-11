#ifndef _EDITBEIZER_H_
#define _EDITBEIZER_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawBezier.h"

/*初始化一些变量*/
extern void initEditBeizer();
/*编辑Beizer曲线的鼠标点击操作*/
extern void editBeizer(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*编辑Beizer曲线的鼠标拖动操作*/
extern void editBe(int x, int y);
#endif

