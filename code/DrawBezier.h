#ifndef _DRAWBEZIER_H_
#define _DRAWBEZIER_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"
#include<vector>
#include "DrawLine.h"

/*Beizer���ߵĿ��Ƶ�����ݽṹ*/
class BezierCurvePt {
public:
	vector<scrPt> beizerPt;
};
/*�洢Beizer���ߵ������*/
extern vector<BezierCurvePt> bePt;
/*��ʼ��һЩ����*/
extern void initBeizer();
/*��Beizer���ߵ�������*/
extern void drawBeizer(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*��Beizer���ߵ��㷨*/
extern void drawBe(vector<scrPt>p);


#endif