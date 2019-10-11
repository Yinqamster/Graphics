#ifndef _Translation_H_
#define _Translation_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include "DrawLine.h"
#include "DrawCircle.h"
#include "DrawEllipse.h"
#include "DrawPolygon.h"
#include "DrawBezier.h"
#include "DrawBCurve.h"
#include "FillArea.h"

/*��ʼ��һЩ����*/
extern void initTranslation();
/*�ж��ƶ���״*/
extern void judgeShape();
/*ƽ��ͼ��ʱ�����������*/
extern void translation(GLint button, GLint action, GLint xMouse, GLint yMouse);

#endif 