#ifndef _DRAWCIRCLE_H_
#define _DRAWCIRCLE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*Բ�����ݽṹ*/
class circlePt {
public:
	scrPt center;
	double radius;
	double radiusY;     /*Բͨ���༭��Ϊ��Բ����*/
};
/*�洢Բ������*/
extern vector<circlePt> circle;
/*��ʼ��һ�±���*/
extern void initCircle();
/*����*/
extern void setPixel(int x, int y);
/*�е�Բ�㷨��Բ*/
extern void MidPoint_Circle(scrPt c, double r);
/*8·�Գ�*/
extern void Cirpot(scrPt c, int x, int y);
/*����Բ��������*/
extern void drawCircle(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*��Բ��������*/
extern void saveCircle(unsigned char key, int x, int y);



#endif
