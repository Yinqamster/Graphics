#ifndef _CUTPOLYGON_H_
#define _CUTPOLYGON_H_

#include "Control.h"
#include "DrawPolygon.h"
#include "DrawLine.h"
#include "FillArea.h"
/*�ü�������ݽṹ*/
class cutFrame {
public:
	scrPt leftUp;
	scrPt leftDown;
	scrPt rightUp;
	scrPt rightDown;
};

/*��ʼ��һЩ����*/
extern void initCutPolygon();
/*���Ʋü���*/
extern void drawCf(int x, int y);
/*�༭�ü���*/
extern void editCf(int x, int y);
/*�ü�����ε�������*/
extern void cutPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse);
#endif

