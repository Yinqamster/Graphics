#ifndef _EDITLPOLYGON_H_
#define _EDITLPOLYGON_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawPolygon.h"
#include "DrawLine.h"
#include "FillArea.h"

/*��ʼ��һЩ����*/
extern void initEditPolygon();
/*�༭����ε����������*/
extern void editPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*�༭����ε�����϶�����*/
extern void editP(int x, int y);
#endif

