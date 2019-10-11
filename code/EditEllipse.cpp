#include "EditEllipse.h"

static int index;
static int endPtctr;
static int pointIndex;
static double deltX, deltY;
static bool mouseLeftDown;
static scrPt pointUp, pointDown, pointLeft, pointRight;
static scrPt lastPoint;
static scrPt click;


void initEditEllipse() {
	endPtctr = 0;
	if (!ellipse.empty()) {
		index = ellipse.size() - 1;
	}
	else {
		cout << "无可编辑椭圆！" << endl;
		endPtctr = 1;
	}
}

static double calcuDis(scrPt p1, scrPt p2) {
	double dis = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return dis;
}
static int judgePoint(scrPt click) {
	int p = -1;
	scrPt center = ellipse[index].center;
	//	scrPt pointUp, pointDown, pointLeft, pointRight;
	pointUp.x = ellipse[index].center.x;
	pointUp.y = ellipse[index].center.y + ellipse[index].minAxis;
	pointDown.x = ellipse[index].center.x;
	pointDown.y = ellipse[index].center.y - ellipse[index].minAxis;
	pointLeft.x = ellipse[index].center.x - ellipse[index].longAxis;
	pointLeft.y = ellipse[index].center.y;
	pointRight.x = ellipse[index].center.x + ellipse[index].longAxis;
	pointRight.y = ellipse[index].center.y;
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

void editE(int x, int y) {
	if (mouseLeftDown) {
		deltX = x - lastPoint.x;
		deltY = (winHeight - y) - lastPoint.y;
		glColor3f(1.0, 1.0, 1.0);
		middle_ellipse(ellipse[index].center, ellipse[index].longAxis, ellipse[index].minAxis);
		if (pointIndex == 0) {
		//	deltX = x - lastPoint.x;
		//	deltY = (winHeight - y) - lastPoint.y;
		//	ellipse[index].longAxis += deltX;
			ellipse[index].minAxis += deltY;
		}
		else if (pointIndex == 1) {
		//	deltX = x - line[index].end.x;
		//	deltY = (winHeight - y) - line[index].end.y;
			ellipse[index].minAxis -= deltY;
		}
		else if (pointIndex == 2) {
		//	deltX = x - line[index].end.x;
		//	deltY = (winHeight - y) - line[index].end.y;
			ellipse[index].longAxis -= deltX;
		}
		else if (pointIndex == 3) {
		//	deltX = x - line[index].end.x;
		//	deltY = (winHeight - y) - line[index].end.y;
			ellipse[index].longAxis += deltX;
		}

		glColor3f(1.0, 0.0, 0.0);
		middle_ellipse(ellipse[index].center, ellipse[index].longAxis, ellipse[index].minAxis);
	}

	lastPoint.x = x;
	lastPoint.y = winHeight - y;

}

void editEllipse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	
	click.x = xMouse;
	click.y = winHeight - yMouse;
	lastPoint = click;

	if (button == GLUT_LEFT_BUTTON && endPtctr == 0) {
		if (action == GLUT_DOWN) {
			mouseLeftDown = true;
			pointIndex = judgePoint(click);//判断点击的点在椭圆心的什么位置
//			cout << pointIndex << endl;
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