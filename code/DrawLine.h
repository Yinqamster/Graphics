#ifndef _DRAWLINE_H_
#define _DRAWLINE_H_


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Control.h"

/*ֱ�ߵ����ݽṹ*/
class linePt {
public:
	/*scrPtΪ�Զ���������*/
	scrPt begin;  /*ֱ�ߵ����*/
	scrPt end;    /*ֱ�ߵ��յ�*/
};

/*�洢ֱ�ߵ�����*/
extern vector<linePt> line;
/*��ʼ��һЩ����*/
extern void initLine();
/*DDA����ֱ���㷨*/
extern void DDA(scrPt pointA, scrPt pointB);
/*���Ƶ�*/
extern void drawPoint(GLint x, GLint y);
/*����ֱ�ߵ�������*/
extern void drawLine(GLint button, GLint action, GLint xMouse, GLint yMouse);
/*��ֱ�ߴ�������*/
extern void saveLine(unsigned char key, int x, int y);

#endif 