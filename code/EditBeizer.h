#ifndef _EDITBEIZER_H_
#define _EDITBEIZER_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawBezier.h"

/*��ʼ��һЩ����*/
extern void initEditBeizer();
/*�༭Beizer���ߵ����������*/
extern void editBeizer(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*�༭Beizer���ߵ�����϶�����*/
extern void editBe(int x, int y);
#endif

