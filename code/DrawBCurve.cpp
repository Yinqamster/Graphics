#include "DrawBCurve.h"

static int endPtctr;
static int rankB;
static int times;//要画多少次n次曲线
static scrPt endPt1, endPt2;
vector<BCurvePt> bCurve;
static BCurvePt ABPt;

#define MAX_CPTX 25

void initBCurve() {
	rankB = 3; 
	ABPt.bPt.clear();
	endPtctr = 0;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

static int factorial(int n) {
	if (n == 1 || n == 0) {
		return 1;
	}
	else{
		return n*factorial(n - 1);
	}
}

static double C(int n, int i){
	return ((double)factorial(n)) / ((double)(factorial(i)*factorial(n - i)));
}

/*
static double N(double u, int n) {
	double sum = 1.0;
	if (n == 0){
		return 1;
	}
	for (int i = 0; i<n; i++){
		sum *= u;
	}
	return sum;
}*/



//绘制B样条曲线
void drawB(vector<scrPt>p)
{
	int ncpts = p.size();
	if (ncpts <= 2) return;
	if (ncpts == 3){
		rankB = 2;
		times = 0;
	}
	else if (rankB < ncpts){
		times = ncpts - rankB - 1;
	}
	else if (rankB >= ncpts)
		return;
	scrPt *p1 = new scrPt[(times + 1) * 500];
	int num;
	for (int i = 0; i <= times; i++){
		p1[i * 500] = p[i];
		double t = 0;
		for (num = i * 500; num < (i + 1) * 500; t += 0.002){
			double x = 0;
			double y = 0;
			for (int k = 0; k <= rankB; k++){
				double b = 0;
				for (int j = 0; j <= rankB - k; j++)
					b += pow(-1, j)*C(rankB + 1, j)*pow(t + rankB - k - j, rankB);
				b /= factorial(rankB);
				x += p[k + i].x*b;
				y += p[k + i].y*b;
			}
			p1[num].x = x;
			p1[num].y = y;
			num++;
		}

	}

/*	for (int k = 1; k < (times + 1) * 500; k++) {
		DDA(p1[k - 1], p1[k]);
	}*/


//	glPointSize(4.0);
	glBegin(GL_LINE_STRIP);
	for (int k = 0; k<(times + 1) * 500; k++)
		glVertex2f(p1[k].x, p1[k].y);
	glEnd();
	glFlush();
	delete[] p1;
}

static void savePoint(scrPt p) {
	ABPt.bPt.push_back(p);
}

//键盘回调函数
static void finishDraw(unsigned char key, int x, int y){
	switch (key) {
	case 13: endPtctr = 2;
		if (ABPt.bPt.size() > 2) {
			glColor3f(0.0, 0.0, 1.0);
			drawB(ABPt.bPt);
		}
		break;
	}
}


//输入新的控制点
void drawBCurve(GLint button, GLint action, GLint xMouse, GLint yMouse){
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

			bCurve.push_back(ABPt);
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

			savePoint(endPt2);
			endPt1 = endPt2;

			glutKeyboardFunc(finishDraw);

			bCurve.pop_back();
			bCurve.push_back(ABPt);
		}
	}
	lastEdit = 5;
}