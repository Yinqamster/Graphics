#include "DrawBezier.h"

static int endPtctr;
static scrPt endPt1, endPt2;
vector<BezierCurvePt> bePt;
static BezierCurvePt ABePt;

void initBeizer() {
//	glPointSize(5.0);
	ABePt.beizerPt.clear();
	endPtctr = 0;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

/*求n!*/
static int factorial(int n){
	if (n == 1 || n == 0){
		return 1;
	}
	else{
		return n*factorial(n - 1);
	}
}
/*求组合排列*/
static double C(int n, int i){
	return ((double)factorial(n)) / ((double)(factorial(i)*factorial(n - i)));
}

//绘制bezier曲线

void drawBe(vector<scrPt>p){
	if (ABePt.beizerPt.empty()) return;
	int ncpts = ABePt.beizerPt.size();

	scrPt *p1 = new scrPt[500];

	GLfloat u = 0, x, y;
	int i, num = 0;
	p1[0] = p[0];
	for (num = 0; num<500; u = u + 0.002){
		x = 0;
		y = 0;
		for (i = 0; i<ncpts; i++){
			x += C(ncpts - 1, i)*pow(u, i)*pow((1 - u), (ncpts - 1 - i))*p[i].x;
			y += C(ncpts - 1, i)*pow(u, i)*pow((1 - u), (ncpts - 1 - i))*p[i].y;
		}
		p1[num].x = x;
		p1[num].y = y;
		num++;
	}
	
	//较慢
	for (int k = 1; k < 500; k++) {
		DDA(p1[k-1], p1[k]);
	}

	//较快
/*	glBegin(GL_LINE_STRIP);
	for (int k = 1; k < 1000; k++) {
		glVertex2f(p1[k].x, p1[k].y);
	}
	glEnd();*/
	glFlush();
	delete[] p1;
//	return;
}

/*存储Beizer曲线的控制点*/
static void savePoint(scrPt p) {
	ABePt.beizerPt.push_back(p);
}
/*
static void saveP() {
	bePt.push_back(ABePt);
}*/

/*键盘回调函数，结束绘制*/
static void finishDraw(unsigned char key, int x, int y){
	switch (key){
	case 13: endPtctr = 2;break;
	}
}


//输入新的控制点
void drawBeizer(GLint button, GLint action, GLint xMouse, GLint yMouse){
	if (endPtctr == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
	//		cout << "here1" << endl;
			endPt1.x = xMouse;
			endPt1.y = winHeight - yMouse;
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glVertex2f(endPt1.x, endPt1.y);
			glEnd();
			glFlush();
			savePoint(endPt1);
			endPtctr = 1;

			bePt.push_back(ABePt);
		}
	}
	else if (endPtctr == 1) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
	//		cout << "here2" << endl;
			endPt2.x = xMouse;
			endPt2.y = winHeight - yMouse;
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glVertex2f(endPt2.x, endPt2.y);
			glEnd();
			glFlush();
			glPointSize(1.0);
			
			glColor3f(1.0, 0.0, 0.0);
			DDA(endPt1, endPt2);
			

			if (ABePt.beizerPt.size() != 2) {
				glColor3f(1.0, 1.0, 1.0);
				drawBe(ABePt.beizerPt);
			}

			savePoint(endPt2);
			endPt1 = endPt2;

			if (ABePt.beizerPt.size() != 2) {
				glColor3f(0.0, 0.0, 1.0);
				drawBe(ABePt.beizerPt);
			}

			glutKeyboardFunc(finishDraw);

			bePt.pop_back();
			bePt.push_back(ABePt);
		}
	}
	lastEdit = 3;
}



