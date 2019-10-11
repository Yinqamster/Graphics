#include "DrawCube.h"

struct POLAR polar = { 3.0f, 60.0f, 45.0f };          /*��ʼ��������*/
struct CAMERA camera;                 /*����������λ�þ����������λ��*/
struct PointMouse oldpt = { -1, -1 };                    /*��¼����ǰһ��λ��*/
int l_button_down = FALSE;               /*��¼���������µ�״̬*/
int mainW, subW1;

void initDrawCube(){                     /*��ʼ������*/
	glClearColor(1.0, 1.0, 1.0, 1.0);                   /*��������Ϊ��ɫ*/
	glColor3f(0.0, 0.0, 0.5);                /*��������ɫ*/
}

void drawC(){               /*���������ͼ��*/
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.xeye, camera.yeye, camera.zeye,
		0.0, 0.0, 0.0,/*������������������۲�ĵ�*/
		0.0, 1.0, 0.0);/*����������ָ������ͼ���Ϸ���*/
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

/*ʹ�洰�ڴ�С�ı���ı�*/
void Reshape(int w, int h){                    
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-6.0, 6.0, -6.0, 6.0, -6.0, 6.0);                   //���������
}

void Keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:                    /*��ESCAPEʱ�˳�����*/
		glutDestroyWindow(subW1);
		break;
	}
}

/*��������ת��Ϊֱ�����꣬���趨Ϊ�������λ��*/
void SetCamera(GLfloat x, GLfloat y){         /*x��y ��ˮƽ�������ֱ����ĸı���*/
	GLfloat alpha, fy;                  /*����������һ���������ǵ�λ�ǻ���*/
	if ((polar.fy + y)>5.0f && (polar.fy + y)<175.0f){
		/*������ֱƫ��ֻ����5�㵽175��֮��*/
		polar.alpha += x;                  /*��������ƶ��ķ��������µ�������*/
		polar.fy += y;

		if (polar.alpha>360.0f) polar.alpha -= 360.0f;
		if (polar.alpha<0.0f) polar.alpha += 360.0f;      /*��ˮƽƫ��������0�㵽360��֮��*/

		alpha = polar.alpha*DEG_TO_RAD;
		fy = polar.fy*DEG_TO_RAD;               /*�Ƕ�ת����*/
		camera.xeye = polar.r * sin(fy) * cos(alpha);       /*������תֱ������*/
		camera.zeye = polar.r * sin(fy) * sin(alpha);
		camera.yeye = polar.r * cos(fy);                 /*ע�⣺��ֱ�������y��*/

		drawC();                     /*ÿ�θı����λ��ʱ�ػ�*/
									  
	}
}

void drawCube(int button, int state, int x, int y){        /*����갴�»�����ʱ��ص��ú���*/
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		l_button_down = TRUE;                /*��l_button_downΪtrueʱ�ſɸı����λ��*/
		oldpt.x = x;                      /*��¼�����꣬�Ա��ƶ�����ʱ��������ƶ�����*/
		oldpt.y = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		l_button_down = FALSE;        /*����ʱ���ܸı������λ��*/
	}
}

void OnMouseMove(int x, int y){          /*������ƶ�ʱ��ص��ú���*/
	if (l_button_down){         /*������û�а����򲻸ı������λ��*/
		SetCamera(float(x - oldpt.x), float(oldpt.y - y));       /*�������������趨�����λ��*/

		oldpt.x = x;              /*����ǰ������Ϊ������*/
		oldpt.y = y;
	}
}