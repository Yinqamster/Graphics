#ifndef _DRAWLINE_H_
#define _DRAWLINE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*直线的数据结构*/
class linePt {
public:
	/*scrPt为自定义点的类型*/
	scrPt begin;  /*直线的起点*/
	scrPt end;    /*直线的终点*/
};

/*存储直线的数组*/
extern vector<linePt> line;
/*初始化一些变量*/
extern void initLine();
/*DDA绘制直线算法*/
extern void DDA(scrPt pointA, scrPt pointB);
/*绘制点*/
extern void drawPoint(GLint x, GLint y);
/*绘制直线的鼠标操作*/
extern void drawLine(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*将直线存入数组*/
extern void saveLine(unsigned char key, int x, int y);

#endif 