#ifndef _EDITBCURVE_H_
#define _EDITBCURVE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawBCurve.h"

/*��ʼ��һЩ����*/
extern void initEditBCurve();
/*�༭B�������ߵ����������*/
extern void editBCurve(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*�༭B�������ߵ�����϶�����*/
extern void editB(int x, int y);
#endif

