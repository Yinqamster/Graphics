#include <windows.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

#include "DrawLine.h"
#include "DrawCircle.h"
#include "DrawEllipse.h"
#include "DrawPolygon.h"
#include "DrawBezier.h"
#include "DrawBCurve.h"
#include "FillArea.h"
#include "Translation.h"
#include "Rotate.h"
#include "zoom.h"
#include "EditLine.h"
#include "EditCircle.h"
#include "EditEllipse.h"
#include "EditPolygon.h"
#include "EditBeizer.h"
#include "EditBCurve.h"
#include "CutPolygon.h"
#include "DrawCube.h"
#include "SaveToBmp.h"


GLsizei winWidth = 500;
GLsizei winHeight = 500;
GLint endPtctr = 0;
int lastEdit = -1; //0 line 1 circle 2 ellipse 3 beizer_curve 4 polygon 5 b_curve



void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glColor3f(0.0, 0.0, 0.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
//	glFlush();
	glColor3f(1.0, 0.0, 0.0);
	if (!line.empty()) {
//		cout << "here" << endl;
		for (int i = 0; i < line.size(); i++) {
			DDA(line[i].begin, line[i].end);
		}
		
	}
	if (!circle.empty()) {
		for (int i = 0; i < circle.size(); i++) {
			middle_ellipse(circle[i].center, circle[i].radius, circle[i].radiusY);
		}
	}
	if (!ellipse.empty()) {
		for (int i = 0; i < ellipse.size(); i++) {
			middle_ellipse(ellipse[i].center, ellipse[i].longAxis, ellipse[i].minAxis);
		}
	}
	if (!bePt.empty()) {
		for (int i = 0; i < bePt.size(); i++) {
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(5.0);
			for (int j = 0; j < bePt[i].beizerPt.size(); j++) {
				glBegin(GL_POINTS);
				glVertex2f(bePt[i].beizerPt[j].x, bePt[i].beizerPt[j].y);
				glEnd();
			}
			glFlush();
			glColor3f(1.0, 0.0, 0.0);
			glPointSize(1.0);
			for (int j = 0; j < bePt[i].beizerPt.size()-1; j++) {
				DDA(bePt[i].beizerPt[j], bePt[i].beizerPt[j + 1]);
			}
			glColor3f(0.0, 0.0, 1.0);
			drawBe(bePt[i].beizerPt);
			glColor3f(1.0, 0.0, 0.0);
		}
	}
	if (!bCurve.empty()) {
		for (int i = 0; i < bCurve.size(); i++) {
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(5.0);
			for (int j = 0; j < bCurve[i].bPt.size(); j++) {
				glBegin(GL_POINTS);
				glVertex2f(bCurve[i].bPt[j].x, bCurve[i].bPt[j].y);
				glEnd();
			}
			glFlush();
			glColor3f(1.0, 0.0, 0.0);
			glPointSize(1.0);
			for (int j = 0; j < bCurve[i].bPt.size() - 1; j++) {
				DDA(bCurve[i].bPt[j], bCurve[i].bPt[j + 1]);
			}
			glColor3f(0.0, 0.0, 1.0);
			drawB(bCurve[i].bPt);
			glColor3f(1.0, 0.0, 0.0);
		}
	}
	if (!polygon.empty()) {
		for (int i = 0; i < polygon.size(); i++) {
			for (int j = 0; j < polygon[i].point.size()-1; j++) {
				DDA(polygon[i].point[j], polygon[i].point[j + 1]);
			}
			DDA(polygon[i].point[polygon[i].point.size() - 1], polygon[i].point[0]);
			if (polygon[i].color != 'n') {
				fillArea(polygon[i].point, polygon[i].color);
			}
		}
	}
	
	glFlush();
}

void changeSize(int w, int h) {
	// ��ֹ�������߶�Ϊ0
/*	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// ��λ��ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �����ӿڴ�СΪ�������ڴ�С
	glViewport(0, 0, w, h);

	// ������ȷ��ͶӰ����
//	gluPerspective(45, ratio, 1, 1000);
	glOrtho(0, 100, 0, 200, -40, 40);
	//����������ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);*/

/*	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-200, 200, -200 * (GLfloat)h / (GLfloat)w, 200 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
	else
		glOrtho(-200 * (GLfloat)w / (GLfloat)h, 200 * (GLfloat)w / (GLfloat)h, -200, 200, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);//�����ӿ�
	winWidth = w;
	winHeight = h;
}

/*
void clearS(int btn, int state, int x, int y) {
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		cout << "ok" << endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		glFlush();
	}
}*/

/*�����д洢ͼ�ε����鶼��գ�ͬʱ�����Ļ*/
void clearS() {
//	cout << "ok" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	
	lastEdit = -1;
	line.clear();
	bCurve.clear();
	bePt.clear();
	circle.clear();
	ellipse.clear();
	polygon.clear();
	cout << polygon.empty() << endl << ellipse.empty() << endl;
	glFlush();
}

void processMenuEvents(int option) {
	switch (option) {
	case 0:

		system("cls");
		cout << "�������(������һ�λ��ƵĶ����)" << endl;
		cout << "�����ɫ��\nr\t��ɫ\ng\t��ɫ\nb\t��ɫ\ny\t��ɫ\np\tƷ��\nc\t��ɫ\n������Ӧ��ĸ����ѡ�������ɫ����������Ҽ�ѡȡ�������ܡ�" << endl;
		initFillArea();
		//		glutMouseFunc(fillArea);
		glutKeyboardFunc(chooseColor);
		//		fillArea();
		break;
	case 1:
		system("cls");
		cout << "����ͼ�Σ���ΪMyPicture����ʽΪbmp" << endl;
		screenshot("MyPicture.bmp");
		break;
	case 2:
		system("cls");
		cout << "�����Ļ��" << endl;
		clearS();
		break;
	}
	

}

void processMenuEventsInput(int option) {
	switch (option) {
	case 0:
		system("cls");
		cout << "����ֱ�ߣ�" << endl;
		cout << "����������ѡȡ�߶ε������˵㣬 ��������Ҽ�ѡȡ�������ܡ�" << endl;
		initLine();
		glutMouseFunc(drawLine);
		break;
	case 1:
		system("cls");
		cout << "����Բ��" << endl;
		cout<<"����������ѡȡԲ�ĺ�Բ������һ�㣬��������Ҽ�ѡȡ�������ܡ�"<<endl;
		initCircle();
		glutMouseFunc(drawCircle);
//		cout << "ok" << endl;
		break;
	case 2:
		system("cls");
		cout << "������Բ��" << endl;
		cout << "������Բ�ĳ���Ͷ��ᣬ����������ѡȡԲ�ģ���������Ҽ�ѡȡ�������ܡ�" << endl;
		initEllipse();
		glutMouseFunc(drawEllipse);
	//	cout <<"~~"<< ellipse.size();
		break;
	case 3:
		system("cls");
		cout << "����Beizer���ߣ�" << endl;
		cout<<"������ѡ�㣬����ʵʱ������" << endl;
		initBeizer();
		glutMouseFunc(drawBeizer);
		break;
	case 4:
		system("cls");
		cout << "����B�������ߣ�" << endl;
		cout << "������ѡ�㣬ѡȡ��������Enter���Ƴ�B�������ߡ�" << endl;
		initBCurve();
		glutMouseFunc(drawBCurve);
		break;
	case 5:
		system("cls");
		cout << "���ƶ���Σ�" << endl;
		cout << "����������ѡȡ����ζ��㣬ѡȡ�������»س���ɻ��ƣ���������Ҽ�ѡȡ�������ܡ�" << endl;
		initPolygon();
		glutMouseFunc(drawPolygon);
		break;
	case 6:
		system("cls");
		cout << "���������壺����϶�����ת�����壬����Esc�˳������崰��" << endl;
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);          /*������ʾģʽ��˫���壩*/
															  //		glutInitWindowSize(400, 400);              /*�趨���ڴ�С*/
															  //		glutInitWindowPosition(100, 100);         /*���Ͻ�����*/
		subW1 = glutCreateSubWindow(mainW, 0, 0, 500, 500);           /*�����Ӵ���*/

		initDrawCube();
		SetCamera(0.0f, 0.0f);
//		glutInitWindowSize(winWidth, winHeight);
		glutReshapeFunc(Reshape);
		glutDisplayFunc(drawC);
		glutKeyboardFunc(Keyboard);
		glutMouseFunc(drawCube);
		glutMotionFunc(OnMouseMove);
		glutMainLoop();
		break;
		break;
	}
}

void processMenuEventsEdit(int option) {
	switch (option) {
	case 0:
		system("cls");
		cout << "�༭ֱ�ߣ�" << endl;
		cout << "����϶�ֱ�ߵ������˵㣬��ֱ�߽��б༭��" << endl;
		initEditLine();
		glutMouseFunc(editLine);
		glutMotionFunc(editL);
		break;
	case 1:
		system("cls");
		cout << "�༭Բ��" << endl;
		cout << "����϶�Բ��ˮƽ����ֱֱ���˵㣬���Զ�Բ���б༭��" << endl;
		initEditCircle();
		glutMouseFunc(editCircle);
		glutMotionFunc(editC);
		break;
	case 2:
		system("cls");
		cout << "�༭��Բ��" << endl;
		cout << "����϶���Բ�ĳ��ᡢ����Ķ˵㣬���Զ���Բ���б༭��" << endl;
		initEditEllipse();
		glutMouseFunc(editEllipse);
		glutMotionFunc(editE);
		break;
	case 3:
		system("cls");
		cout << "�༭Beizer���ߣ�" << endl;
		cout << "����϶�Beizer����һ���Ƶ㣬���Ա༭Beizer���ߡ�" << endl;
		initEditBeizer();
		glutMouseFunc(editBeizer);
		glutMotionFunc(editBe);
		break;
	case 4:
		system("cls");
		cout << "�༭B�������ߣ�" << endl;
		cout << "����϶�B��������һ���Ƶ㣬���Ա༭B�������ߡ�" << endl;
		initEditBCurve();
		glutMouseFunc(editBCurve);
		glutMotionFunc(editB);
		break;
	case 5:
		system("cls");
		cout << "�༭����Σ�" << endl;
		cout << "����϶�����ε���һ���㣬�ɱ༭����ε���״��" << endl;
		initEditPolygon();
		glutMouseFunc(editPolygon);
		glutMotionFunc(editP);
		break;
	}
}

void processMenuEventsExchange(int option) {
	switch (option) {
	case 0:
		system("cls");
		cout << "ƽ�ƣ���ƽ�����һ�α༭��ͼ�Σ���" << endl;
		cout << "�϶��������ƶ�ͼ�Ρ�" << endl;
		initTranslation();
//		glutMouseFunc(translation);		
		judgeShape();
		break;
	case 1:
		system("cls");
		cout << "��ת������ת���һ�α༭��ͼ�Σ���" << endl;
		cout << "�ȵ��������ȷ����ת���ģ�Ȼ��ס����϶�������ת��" << endl;
		initRotate();	
		judgeShapeR();
		break;
	case 2:
		system("cls");
		cout << "���ţ����������һ�α༭��ͼ�Σ���" << endl;
		cout << "�ȵ��������ȷ���������ģ�Ȼ����������ַŴ����С���ٴε���������������š�" << endl;
		initZoom();
		judgeShapeZ();
		break;
	}
}

void processMenuEventsCut(int option) {
	switch (option) {
	case 0:
		system("cls");
		cout << "�ü�����Σ��ɲü����һ�α༭�Ķ���Σ���" << endl;
		cout << "�Ȱ������������϶��������ο򣬿ɵ������ο��С��Ȼ����Enter�ü�" << endl;
		initCutPolygon();
		glutMouseFunc(cutPolygon);
	//	glutMotionFunc(drawCf);
	//	glutMotionFunc(editCf);
		break;
	}
}

void createGLUTMenus() {
	//	 glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int menu, submenu0, submenu1, submenu2, submenu3;

	//ͼ������������Ӳ˵�
	submenu0 = glutCreateMenu(processMenuEventsInput);
	glutAddMenuEntry("����ֱ��", 0);
	glutAddMenuEntry("����Բ", 1);
	glutAddMenuEntry("������Բ", 2);
	glutAddMenuEntry("����Beizer����", 3);
	glutAddMenuEntry("����B��������", 4);
	glutAddMenuEntry("���ƶ����", 5);
	glutAddMenuEntry("����������", 6);

	submenu1 = glutCreateMenu(processMenuEventsEdit);
	glutAddMenuEntry("�༭ֱ��", 0);
	glutAddMenuEntry("�༭Բ", 1);
	glutAddMenuEntry("�༭��Բ", 2);
	glutAddMenuEntry("�༭Beizer����", 3);
	glutAddMenuEntry("�༭B��������", 4);
	glutAddMenuEntry("�༭�����", 5);

	submenu2 = glutCreateMenu(processMenuEventsCut);
	glutAddMenuEntry("�ü������", 0);

	submenu3 = glutCreateMenu(processMenuEventsExchange);
	glutAddMenuEntry("ƽ��", 0);
	glutAddMenuEntry("��ת", 1);
	glutAddMenuEntry("����", 2);

	menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("ͼ����������", submenu0);
	glutAddSubMenu("ͼ�����ݱ༭", submenu1);
	glutAddSubMenu("ͼ�����ݲü�", submenu2);
	glutAddSubMenu("ͼ�����ݱ任", submenu3);

	glutAddMenuEntry("�������", 0);
	glutAddMenuEntry("����ͼ��", 1);
	glutAddMenuEntry("�����Ļ", 2);

	// �Ѳ˵�������Ҽ�����������
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(800, 100);
	mainW = glutCreateWindow("CG-YinQi");
	init();
//	glutDisplayFunc(createGLUTMenus);
	glutDisplayFunc(display);
	//�ı䴰�ڴ�Сʱʹ��
	glutReshapeFunc(changeSize);
//	glutMouseFunc(clearS);
	createGLUTMenus();
	

	
	glutMainLoop();
	return 0;
}