#ifndef _DRAWPOLYGON_H_
#define _DRAWPOLYGON_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*����ε����ݽṹ*/
class polygonPt {
public:
	vector<scrPt> point;
	char color;
};
/*�洢����ε�����*/
extern vector<polygonPt> polygon;
/*��ʼ��һЩ����*/
extern void initPolygon();
/*���ƶ���ε�������*/
extern void drawPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse);

#endif 