#include "EditCircle.h"

static int index;
static int endPtctr;
static int pointIndex;
static double deltX, deltY;
static bool mouseLeftDown;
static scrPt pointUp, pointDown, pointLeft, pointRight;
static scrPt lastPoint;

void initEditCircle() {
	endPtctr = 0;
	if (!circle.empty()) {
		index = circle.size() - 1;
	}
	else {
		cout << "无可编辑圆！" << endl;
		endPtctr = 1;
	}
}

static double calcuDis(scrPt p1, scrPt p2) {
	double dis = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return dis;
}
static int judgePoint(scrPt click) {
	int p = -1;
	scrPt center = circle[index].center;
//	scrPt pointUp, pointDown, pointLeft, pointRight;
	pointUp.x = circle[index].center.x;
	pointUp.y = circle[index].center.y + circle[index].radius;
	pointDown.x = circle[index].center.x;
	pointDown.y = circle[index].center.y - circle[index].radius;
	pointLeft.x = circle[index].center.x - circle[index].radius;
	pointLeft.y = circle[index].center.y;
	pointRight.x = circle[index].center.x + circle[index].radius;
	pointRight.y = circle[index].center.y;
	double disU = calcuDis(pointUp, click);
	double disD = calcuDis(pointDown, click);
	double disL = calcuDis(pointLeft, click);
	double disR = calcuDis(pointRight, click);
	double min = disU;
	p = 0;
	if (disD < min) {
		min = disD;
		p = 1;
	}
	if (disL < min) {
		min = disL;
		p = 2;
	}
	if (disR < min) {
		min = disR;
		p = 3;
	}

	return p;
}

void editC(int x, int y) {
	if (mouseLeftDown) {
		deltX = x - lastPoint.x;
		deltY = (winHeight - y) - lastPoint.y;
		glColor3f(1.0, 1.0, 1.0);
		middle_ellipse(circle[index].center, circle[index].radius, circle[index].radiusY);
		if (pointIndex == 0) {
			//	deltX = x - lastPoint.x;
			//	deltY = (winHeight - y) - lastPoint.y;
			//	ellipse[index].longAxis += deltX;
			circle[index].radiusY += deltY;
		}
		else if (pointIndex == 1) {
			//	deltX = x - line[index].end.x;
			//	deltY = (winHeight - y) - line[index].end.y;
			circle[index].radiusY -= deltY;
		}
		else if (pointIndex == 2) {
			//	deltX = x - line[index].end.x;
			//	deltY = (winHeight - y) - line[index].end.y;
			circle[index].radius -= deltX;
		}
		else if (pointIndex == 3) {
			//	deltX = x - line[index].end.x;
			//	deltY = (winHeight - y) - line[index].end.y;
			circle[index].radius += deltX;
		}

		glColor3f(1.0, 0.0, 0.0);
		middle_ellipse(circle[index].center, circle[index].radius, circle[index].radiusY);
	}

	lastPoint.x = x;
	lastPoint.y = winHeight - y;

}

void editCircle(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	scrPt click;
	click.x = xMouse;
	click.y = winHeight - yMouse;
	
//	cout << pointIndex << endl;
	lastPoint = click;
	if (button == GLUT_LEFT_BUTTON && endPtctr == 0) {
		if (action == GLUT_DOWN) {
			mouseLeftDown = true;
			pointIndex = judgePoint(click);//判断点击的点在圆心的什么位置
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