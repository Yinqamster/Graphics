#ifndef _EDITLINE_H_
#define _EDITLINE_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawLine.h"

/*��ʼ��һЩ����*/
extern void initEditLine();
/*�༭ֱ�ߵ����������*/
extern void editLine(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*�༭ֱ�ߵ�����϶�����*/
extern void editL(int x, int y);
#endif

