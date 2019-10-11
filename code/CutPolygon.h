#ifndef _CUTPOLYGON_H_
#define _CUTPOLYGON_H_

#include "Control.h"
#include "DrawPolygon.h"
#include "DrawLine.h"
#include "FillArea.h"
/*裁剪框的数据结构*/
class cutFrame {
public:
	scrPt leftUp;
	scrPt leftDown;
	scrPt rightUp;
	scrPt rightDown;
};

/*初始化一些变量*/
extern void initCutPolygon();
/*绘制裁剪框*/
extern void drawCf(int x, int y);
/*编辑裁剪框*/
extern void editCf(int x, int y);
/*裁剪多边形的鼠标操作*/
extern void cutPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse);
#endif

