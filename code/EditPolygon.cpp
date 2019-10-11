#include "EditPolygon.h"

static int index;
static int endPtctr;
static int pointIndex;
static double deltX, deltY;
static bool mouseLeftDown;
static int numOfPoint;
static scrPt click;

void initEditPolygon() {
	endPtctr = 0;
	if (!polygon.empty()) {
		index = polygon.size() - 1;
		numOfPoint = polygon[index].point.size();
	}
	else {
		cout << "无可编辑多边形！" << endl;
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
	for (int i = 0; i < polygon[index].point.size(); i++) {
		disOfPoints[i] = calcuDis(polygon[index].point[i], click);
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

void editP(int x, int y) {
	if (mouseLeftDown) {
		glColor3f(1.0, 1.0, 1.0);
		DDA(polygon[index].point[(pointIndex+ numOfPoint -1)% numOfPoint], polygon[index].point[pointIndex]);
		DDA(polygon[index].point[pointIndex], polygon[index].point[(pointIndex+1) % numOfPoint]);
		if (polygon[index].color != 'n') {
			fillArea(polygon[index].point, 'w');
		}

//		if (pointIndex == 0) {
		deltX = x - polygon[index].point[pointIndex].x;
		deltY = (winHeight - y) - polygon[index].point[pointIndex].y;
		polygon[index].point[pointIndex].x += deltX;
		polygon[index].point[pointIndex].y += deltY;
/*		}
		else if (pointIndex == 1) {
			deltX = x - line[index].end.x;
			deltY = (winHeight - y) - line[index].end.y;
			line[index].end.x += deltX;
			line[index].end.y += deltY;
		}*/

		glColor3f(1.0, 0.0, 0.0);
		DDA(polygon[index].point[(pointIndex + numOfPoint - 1) % numOfPoint], polygon[index].point[pointIndex]);
		DDA(polygon[index].point[pointIndex], polygon[index].point[(pointIndex + 1) % numOfPoint]);
		if (polygon[index].color != 'n') {
			fillArea(polygon[index].point, polygon[index].color);
		}
		
	}

}

void editPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse) {

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