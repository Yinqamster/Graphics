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
	// 防止除数即高度为0
/*	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// 单位化投影矩阵。
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置视口大小为增个窗口大小
	glViewport(0, 0, w, h);

	// 设置正确的投影矩阵
//	gluPerspective(45, ratio, 1, 1000);
	glOrtho(0, 100, 0, 200, -40, 40);
	//下面是设置模型视图矩阵
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
	glViewport(0, 0, w, h);//调整视口
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

/*将所有存储图形的数组都清空，同时清空屏幕*/
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
		cout << "填充区域(填充最后一次绘制的多边形)" << endl;
		cout << "填充颜色表：\nr\t红色\ng\t绿色\nb\t蓝色\ny\t黄色\np\t品红\nc\t青色\n按下相应字母即可选择填充颜色，按下鼠标右键选取其他功能。" << endl;
		initFillArea();
		//		glutMouseFunc(fillArea);
		glutKeyboardFunc(chooseColor);
		//		fillArea();
		break;
	case 1:
		system("cls");
		cout << "保存图形：名为MyPicture，格式为bmp" << endl;
		screenshot("MyPicture.bmp");
		break;
	case 2:
		system("cls");
		cout << "清空屏幕。" << endl;
		clearS();
		break;
	}
	

}

void processMenuEventsInput(int option) {
	switch (option) {
	case 0:
		system("cls");
		cout << "绘制直线：" << endl;
		cout << "按下鼠标左键选取线段的两个端点， 按下鼠标右键选取其他功能。" << endl;
		initLine();
		glutMouseFunc(drawLine);
		break;
	case 1:
		system("cls");
		cout << "绘制圆：" << endl;
		cout<<"按下鼠标左键选取圆心和圆上任意一点，按下鼠标右键选取其他功能。"<<endl;
		initCircle();
		glutMouseFunc(drawCircle);
//		cout << "ok" << endl;
		break;
	case 2:
		system("cls");
		cout << "绘制椭圆：" << endl;
		cout << "输入椭圆的长轴和短轴，按下鼠标左键选取圆心，按下鼠标右键选取其他功能。" << endl;
		initEllipse();
		glutMouseFunc(drawEllipse);
	//	cout <<"~~"<< ellipse.size();
		break;
	case 3:
		system("cls");
		cout << "绘制Beizer曲线：" << endl;
		cout<<"鼠标左键选点，曲线实时画出。" << endl;
		initBeizer();
		glutMouseFunc(drawBeizer);
		break;
	case 4:
		system("cls");
		cout << "绘制B样条曲线：" << endl;
		cout << "鼠标左键选点，选取结束后按下Enter绘制出B样条曲线。" << endl;
		initBCurve();
		glutMouseFunc(drawBCurve);
		break;
	case 5:
		system("cls");
		cout << "绘制多边形：" << endl;
		cout << "按下鼠标左键选取多边形顶点，选取结束后按下回车完成绘制，按下鼠标右键选取其他功能。" << endl;
		initPolygon();
		glutMouseFunc(drawPolygon);
		break;
	case 6:
		system("cls");
		cout << "绘制六面体：鼠标拖动可旋转六面体，按下Esc退出六面体窗口" << endl;
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);          /*设置显示模式（双缓冲）*/
															  //		glutInitWindowSize(400, 400);              /*设定窗口大小*/
															  //		glutInitWindowPosition(100, 100);         /*左上角坐标*/
		subW1 = glutCreateSubWindow(mainW, 0, 0, 500, 500);           /*创建子窗口*/

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
		cout << "编辑直线：" << endl;
		cout << "点击拖动直线的两个端点，对直线进行编辑。" << endl;
		initEditLine();
		glutMouseFunc(editLine);
		glutMotionFunc(editL);
		break;
	case 1:
		system("cls");
		cout << "编辑圆：" << endl;
		cout << "点击拖动圆的水平、竖直直径端点，可以对圆进行编辑。" << endl;
		initEditCircle();
		glutMouseFunc(editCircle);
		glutMotionFunc(editC);
		break;
	case 2:
		system("cls");
		cout << "编辑椭圆：" << endl;
		cout << "点击拖动椭圆的长轴、短轴的端点，可以对椭圆进行编辑。" << endl;
		initEditEllipse();
		glutMouseFunc(editEllipse);
		glutMotionFunc(editE);
		break;
	case 3:
		system("cls");
		cout << "编辑Beizer曲线：" << endl;
		cout << "点击拖动Beizer的任一控制点，可以编辑Beizer曲线。" << endl;
		initEditBeizer();
		glutMouseFunc(editBeizer);
		glutMotionFunc(editBe);
		break;
	case 4:
		system("cls");
		cout << "编辑B样条曲线：" << endl;
		cout << "点击拖动B样条的任一控制点，可以编辑B样条曲线。" << endl;
		initEditBCurve();
		glutMouseFunc(editBCurve);
		glutMotionFunc(editB);
		break;
	case 5:
		system("cls");
		cout << "编辑多边形：" << endl;
		cout << "点击拖动多边形的任一顶点，可编辑多边形的形状。" << endl;
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
		cout << "平移（可平移最后一次编辑的图形）：" << endl;
		cout << "拖动鼠标左键移动图形。" << endl;
		initTranslation();
//		glutMouseFunc(translation);		
		judgeShape();
		break;
	case 1:
		system("cls");
		cout << "旋转（可旋转最后一次编辑的图形）：" << endl;
		cout << "先点击鼠标左键确定旋转中心，然后按住左键拖动进行旋转。" << endl;
		initRotate();	
		judgeShapeR();
		break;
	case 2:
		system("cls");
		cout << "缩放（可缩放最后一次编辑的图形）：" << endl;
		cout << "先点击鼠标左键确定缩放中心，然后滚动鼠标滚轮放大或缩小，再次点击鼠标左键结束缩放。" << endl;
		initZoom();
		judgeShapeZ();
		break;
	}
}

void processMenuEventsCut(int option) {
	switch (option) {
	case 0:
		system("cls");
		cout << "裁剪多边形（可裁剪最后一次编辑的多边形）：" << endl;
		cout << "先按下鼠标左键并拖动画出矩形框，可调整矩形框大小，然后按下Enter裁剪" << endl;
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

	//图形数据输入的子菜单
	submenu0 = glutCreateMenu(processMenuEventsInput);
	glutAddMenuEntry("绘制直线", 0);
	glutAddMenuEntry("绘制圆", 1);
	glutAddMenuEntry("绘制椭圆", 2);
	glutAddMenuEntry("绘制Beizer曲线", 3);
	glutAddMenuEntry("绘制B样条曲线", 4);
	glutAddMenuEntry("绘制多边形", 5);
	glutAddMenuEntry("绘制六面体", 6);

	submenu1 = glutCreateMenu(processMenuEventsEdit);
	glutAddMenuEntry("编辑直线", 0);
	glutAddMenuEntry("编辑圆", 1);
	glutAddMenuEntry("编辑椭圆", 2);
	glutAddMenuEntry("编辑Beizer曲线", 3);
	glutAddMenuEntry("编辑B样条曲线", 4);
	glutAddMenuEntry("编辑多边形", 5);

	submenu2 = glutCreateMenu(processMenuEventsCut);
	glutAddMenuEntry("裁剪多边形", 0);

	submenu3 = glutCreateMenu(processMenuEventsExchange);
	glutAddMenuEntry("平移", 0);
	glutAddMenuEntry("旋转", 1);
	glutAddMenuEntry("缩放", 2);

	menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("图形数据输入", submenu0);
	glutAddSubMenu("图形数据编辑", submenu1);
	glutAddSubMenu("图形数据裁剪", submenu2);
	glutAddSubMenu("图形数据变换", submenu3);

	glutAddMenuEntry("填充多边形", 0);
	glutAddMenuEntry("保存图形", 1);
	glutAddMenuEntry("清空屏幕", 2);

	// 把菜单和鼠标右键关联起来。
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
	//改变窗口大小时使用
	glutReshapeFunc(changeSize);
//	glutMouseFunc(clearS);
	createGLUTMenus();
	

	
	glutMainLoop();
	return 0;
}