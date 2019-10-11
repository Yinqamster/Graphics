#include "EditBCurve.h"

static int index;
static int endPtctr;
static int pointIndex;
static double deltX, deltY;
static bool mouseLeftDown;
static int numOfPoint;
static scrPt click;

void initEditBCurve() {
	endPtctr = 0;
	if (!bCurve.empty()) {
		index = bCurve.size() - 1;
		numOfPoint = bCurve[index].bPt.size();
	}
	else {
		cout << "无可编辑图形！" << endl;
		endPtctr = 1;
	}
}

static double calcuDis(scrPt p1, scrPt p2) {
	double dis = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return dis;
}


static int judgePoint(scrPt click) {
	int p = -1;
	int* disOfPoints = new int[numOfPoint];
	for (int i = 0; i < bCurve[index].bPt.size(); i++) {
		disOfPoints[i] = calcuDis(bCurve[index].bPt[i], click);
	}
	int min = disOfPoints[0];
	p = 0;
	for (int i = 0; i < numOfPoint; i++) {
		if (disOfPoints[i] < min) {
			min = disOfPoints[i];
			p = i;
		}
	}
	return p;
}

void editB(int x, int y) {
	if (mouseLeftDown) {


		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex2f(bCurve[index].bPt[pointIndex].x, bCurve[index].bPt[pointIndex].y);
		glEnd();
		glFlush();
		glPointSize(1.0);
		if (pointIndex != bCurve[index].bPt.size() - 1) {
			DDA(bCurve[index].bPt[pointIndex], bCurve[index].bPt[pointIndex + 1]);
		}
		if (pointIndex != 0) {
			DDA(bCurve[index].bPt[pointIndex - 1], bCurve[index].bPt[pointIndex]);
		}
		
		drawB(bCurve[index].bPt);


		deltX = x - bCurve[index].bPt[pointIndex].x;
		deltY = (winHeight - y) - bCurve[index].bPt[pointIndex].y;
		bCurve[index].bPt[pointIndex].x += deltX;
		bCurve[index].bPt[pointIndex].y += deltY;



		glColor3f(0.0, 0.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex2f(bCurve[index].bPt[pointIndex].x, bCurve[index].bPt[pointIndex].y);
		glEnd();
		glFlush();
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(1.0);
		if (pointIndex != bCurve[index].bPt.size() - 1) {
			DDA(bCurve[index].bPt[pointIndex], bCurve[index].bPt[pointIndex + 1]);
		}
		if (pointIndex != 0) {
			DDA(bCurve[index].bPt[pointIndex - 1], bCurve[index].bPt[pointIndex]);
		}
		glColor3f(0.0, 0.0, 1.0);
		drawB(bCurve[index].bPt);
		glColor3f(1.0, 0.0, 0.0);
	}

}

void editBCurve(GLint button, GLint action, GLint xMouse, GLint yMouse) {

	click.x = xMouse;
	click.y = winHeight - yMouse;
	
//	cout << pointIndex << endl;
	if (button == GLUT_LEFT_BUTTON && endPtctr == 0) {
		if (action == GLUT_DOWN) {
			mouseLeftDown = true;
			pointIndex = judgePoint(click);//判断点击的是哪个点
//			cout << "true" << endl;
		}
		else {
			mouseLeftDown = false;
			endPtctr++;
//			cout << "false" << endl;
		}

	}
	glutPostRedisplay();
}