#ifndef _EDITELLIPSE_H_
#define _EDITELLIPSE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawEllipse.h"

/*��ʼ��һЩ����*/
extern void initEditEllipse();
/*�༭��Բ�����������*/
extern void editEllipse(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*�༭��Բ������϶�����*/
extern void editE(int x, int y);
#endif

