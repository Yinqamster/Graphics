#include "EditBeizer.h"

static int index;
static int endPtctr;
static int pointIndex;
static double deltX, deltY;
static bool mouseLeftDown;
static int numOfPoint;
static scrPt click;

void initEditBeizer() {
	endPtctr = 0;
	if (!bePt.empty()) {
		index = bePt.size() - 1;
		numOfPoint = bePt[index].beizerPt.size();
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
	for (int i = 0; i < bePt[index].beizerPt.size(); i++) {
		disOfPoints[i] = calcuDis(bePt[index].beizerPt[i], click);
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




void editBe(int x, int y) {
	if (mouseLeftDown) {


		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex2f(bePt[index].beizerPt[pointIndex].x, bePt[index].beizerPt[pointIndex].y);
		glEnd();
		glFlush();
		glPointSize(1.0);
		if (pointIndex != 0) {
			DDA(bePt[index].beizerPt[pointIndex - 1], bePt[index].beizerPt[pointIndex]);
		}
		if (pointIndex != bePt[index].beizerPt.size() - 1) {
			DDA(bePt[index].beizerPt[pointIndex], bePt[index].beizerPt[pointIndex + 1]);
		}
		drawBe(bePt[index].beizerPt);


		deltX = x - bePt[index].beizerPt[pointIndex].x;
		deltY = (winHeight - y) - bePt[index].beizerPt[pointIndex].y;
		bePt[index].beizerPt[pointIndex].x += deltX;
		bePt[index].beizerPt[pointIndex].y += deltY;



		glColor3f(0.0, 0.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glVertex2f(bePt[index].beizerPt[pointIndex].x, bePt[index].beizerPt[pointIndex].y);
		glEnd();
		glFlush();
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(1.0);
		if (pointIndex != 0) {
			DDA(bePt[index].beizerPt[pointIndex - 1], bePt[index].beizerPt[pointIndex]);
		}
		if (pointIndex != bePt[index].beizerPt.size() - 1) {
			DDA(bePt[index].beizerPt[pointIndex], bePt[index].beizerPt[pointIndex + 1]);
		}
		glColor3f(0.0, 0.0, 1.0);
		drawBe(bePt[index].beizerPt);
		glColor3f(1.0, 0.0, 0.0);
	}

}

void editBeizer(GLint button, GLint action, GLint xMouse, GLint yMouse) {

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