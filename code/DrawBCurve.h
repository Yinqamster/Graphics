#ifndef _DRAWBCURVE_H_
#define _DRAWBCURVE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawLine.h"

/*B�������߿��Ƶ�����ݽṹ*/
class BCurvePt {
public:
	vector<scrPt> bPt;
};
/*�洢B�������߿��Ƶ������*/
extern vector<BCurvePt> bCurve;
/*����B�������ߵ��㷨*/
extern void drawB(vector<scrPt>p);
/*��ʼ��һЩ����*/
extern void initBCurve();
/*����B�������ߵ�������*/
extern void drawBCurve(GLint button, GLint action, GLint xMouse, GLint yMouse);


#endif
