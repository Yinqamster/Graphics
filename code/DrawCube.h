#ifndef _DRAWCUBE_H_
#define _DRAWCUBE_H_


#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <GL/glut.h>

#define DEG_TO_RAD 0.017453
#define TRUE 1
#define FALSE 0
/*���ڼ�¼���λ��*/
struct PointMouse{
	int x;
	int y;
};
/*�����������λ*/
struct CAMERA{
	GLfloat   xeye;
	GLfloat yeye;
	GLfloat zeye;
};
/*������*/
struct POLAR{
	float r;                   /*����r*/
	float alpha;                    /*ˮƽƫ�Ǧ�*/
	float fy;                 /*��ֱƫ�Ǧգ���λ���ýǶȣ�*/
};
/*mainWΪԭ���ڣ�subW1Ϊ�Ӵ���*/
extern int mainW, subW1;
/*��ʼ������*/
extern void initDrawCube();
/*��������ת��Ϊֱ�����꣬���趨Ϊ�������λ��*/
extern void SetCamera(GLfloat x, GLfloat y);
/*����ͼ��*/
extern void drawC();
/*���ƺ���������������*/
extern void drawCube(int button, int state, int x, int y);
/*���ƺ���������������*/
extern void OnMouseMove(int x, int y);
/*�ı䴰�ڴ�Сʱʹ��*/
extern void Reshape(int w, int h);
/*���̻ص��������˳��Ӵ���ʱ��*/
extern void Keyboard(unsigned char key, int x, int y);

#endif
