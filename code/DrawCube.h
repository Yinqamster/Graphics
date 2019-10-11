#ifndef _DRAWCUBE_H_
#define _DRAWCUBE_H_


#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <GL/glut.h>

#define DEG_TO_RAD 0.017453
#define TRUE 1
#define FALSE 0
/*用于记录鼠标位置*/
struct PointMouse{
	int x;
	int y;
};
/*用于摄像机定位*/
struct CAMERA{
	GLfloat   xeye;
	GLfloat yeye;
	GLfloat zeye;
};
/*球坐标*/
struct POLAR{
	float r;                   /*距离r*/
	float alpha;                    /*水平偏角α*/
	float fy;                 /*竖直偏角φ（单位均用角度）*/
};
/*mainW为原窗口，subW1为子窗口*/
extern int mainW, subW1;
/*初始化场景*/
extern void initDrawCube();
/*将球坐标转化为直角坐标，并设定为摄像机的位置*/
extern void SetCamera(GLfloat x, GLfloat y);
/*绘制图像*/
extern void drawC();
/*绘制好六面体后的鼠标操作*/
extern void drawCube(int button, int state, int x, int y);
/*绘制好六面体后的鼠标操作*/
extern void OnMouseMove(int x, int y);
/*改变窗口大小时使用*/
extern void Reshape(int w, int h);
/*键盘回调函数，退出子窗口时用*/
extern void Keyboard(unsigned char key, int x, int y);

#endif
