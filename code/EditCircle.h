#ifndef _EDITCIRCLE_H_
#define _EDITCIRCLE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawCircle.h"
#include "DrawEllipse.h"

/*��ʼ��һЩ����*/
extern void initEditCircle();
/*�༭Բ�����������*/
extern void editCircle(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*�༭Բ������ƶ�����*/
extern void editC(int x, int y);
#endif

