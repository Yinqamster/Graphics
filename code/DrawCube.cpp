#include "DrawCube.h"

struct POLAR polar = { 3.0f, 60.0f, 45.0f };          /*初始化球坐标*/
struct CAMERA camera;                 /*这个摄像机的位置就是球坐标的位置*/
struct PointMouse oldpt = { -1, -1 };                    /*记录鼠标的前一个位置*/
int l_button_down = FALSE;               /*记录鼠标左键按下的状态*/
int mainW, subW1;

void initDrawCube(){                     /*初始化场景*/
	glClearColor(1.0, 1.0, 1.0, 1.0);                   /*将背景设为白色*/
	glColor3f(0.0, 0.0, 0.5);                /*物体用蓝色*/
}

void drawC(){               /*在这里绘制图形*/
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.xeye, camera.yeye, camera.zeye,
		0.0, 0.0, 0.0,/*这三个参数是摄像机观察的点*/
		0.0, 1.0, 0.0);/*这三个参数指定了视图的上方向*/
	glBegin(GL_QUADS);               //top
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);               //forward
	glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);               //right
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	glBegin(GL_QUADS);               //left
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);               //bottom
	glColor3f(1.0f, 0.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);   //back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	glFlush();

	glutSwapBuffers();
}

/*使随窗口大小改变而改变*/
void Reshape(int w, int h){                    
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-6.0, 6.0, -6.0, 6.0, -6.0, 6.0);                   //定义剪裁区
}

void Keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:                    /*按ESCAPE时退出窗口*/
		glutDestroyWindow(subW1);
		break;
	}
}

/*将球坐标转化为直角坐标，并设定为摄像机的位置*/
void SetCamera(GLfloat x, GLfloat y){         /*x，y 是水平方向和竖直方向的改变量*/
	GLfloat alpha, fy;                  /*和它的名字一样，不过是单位是弧度*/
	if ((polar.fy + y)>5.0f && (polar.fy + y)<175.0f){
		/*定义竖直偏角只能在5°到175°之间*/
		polar.alpha += x;                  /*根据鼠标移动的方向设置新的球坐标*/
		polar.fy += y;

		if (polar.alpha>360.0f) polar.alpha -= 360.0f;
		if (polar.alpha<0.0f) polar.alpha += 360.0f;      /*将水平偏角锁定在0°到360°之间*/

		alpha = polar.alpha*DEG_TO_RAD;
		fy = polar.fy*DEG_TO_RAD;               /*角度转弧度*/
		camera.xeye = polar.r * sin(fy) * cos(alpha);       /*极坐标转直角坐标*/
		camera.zeye = polar.r * sin(fy) * sin(alpha);
		camera.yeye = polar.r * cos(fy);                 /*注意：竖直方向的是y轴*/

		drawC();                     /*每次改变相机位置时重绘*/
									  
	}
}

void drawCube(int button, int state, int x, int y){        /*当鼠标按下或拿起时会回调该函数*/
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		l_button_down = TRUE;                /*当l_button_down为true时才可改变相机位置*/
		oldpt.x = x;                      /*记录旧坐标，以便移动发生时计算鼠标移动方向*/
		oldpt.y = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		l_button_down = FALSE;        /*拿起时不能改变摄像机位置*/
	}
}

void OnMouseMove(int x, int y){          /*当鼠标移动时会回调该函数*/
	if (l_button_down){         /*如果鼠标没有按下则不改变摄像机位置*/
		SetCamera(float(x - oldpt.x), float(oldpt.y - y));       /*根据增量重新设定摄像机位置*/

		oldpt.x = x;              /*将当前坐标置为旧坐标*/
		oldpt.y = y;
	}
}