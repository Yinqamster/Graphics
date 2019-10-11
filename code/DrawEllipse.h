#ifndef _DRAWELLIPSE_H_
#define _DRAWELLIPSE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*��Բ�����ݽṹ*/
class ellipsePt {
public:
	scrPt center;
	double longAxis, minAxis;
};
/*�洢��Բ������*/
extern vector<ellipsePt> ellipse;
/*��ʼ��һЩ����*/
extern void initEllipse();
/*����Բ��������*/
extern void drawEllipse(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*����Բ��������*/
extern void saveEllipse(unsigned char key, int x, int y);
/*�е���Բ�㷨*/
extern void middle_ellipse(scrPt center, double longAxis, double minAxis);
#endif
