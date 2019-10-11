#include "Rotate.h"

static scrPt fixedPoint;
static bool mouseLeftDown;
static int clickX, clickY;
static scrPt newBegin, newEnd;
static scrPt newCenter;
static scrPt lastPoint;
static int endPtctr;
static int index;
static vector<scrPt> newPoint;

void initRotate() {
	endPtctr = 0;
}

/*获取旋转的角度*/
double getAngle(int cX, int cY, int mX, int mY) {
//	cout << "cx " << cX << "cy " << cY << "mx " << mX << "my " << mY << endl;
//	cout << "fx " << fixedPoint.x << "fy " << fixedPoint.y << endl;
	double powB = pow((cX - fixedPoint.x), 2) + pow((cY - fixedPoint.y), 2);
	double powC = pow((mX - fixedPoint.x), 2) + pow((mY - fixedPoint.y), 2);
	double powA = pow((cX - mX), 2) + pow((cY - mY), 2);
	double cosA = (powB + powC - powA) / (2 * sqrt(powB * powC));
	double A = acos(cosA);
	return A;
}

/*判断旋转的方向是顺时针还是逆时针*/
int getDirection(scrPt fP,scrPt lP, int x, int y) {   //定点，上一次鼠标所在位置，当前鼠标xy
	y = winHeight - y;
	if (x >= fP.x && y >= fP.y) {   //1
		if ((lP.x > x && lP.y < y) || (lP.x > x && lP.y == y) || (lP.x == x && lP.y < y)) {
//			cout << "nishizhen" << endl;
			return 1;
		}
		else {
//			cout << "shunshizhen" << endl;
			return -1;
		}
	}
	else if (x < fP.x && y > fP.y) {   //2
		if ((lP.x > x && lP.y > y) || (lP.x > x && lP.y == y) || (lP.x == x && lP.y > y)) {
//			cout << "nishizhen" << endl;
			return 1;
		}
		else {
		//	cout << "shunshizhen" << endl;
			return -1;
		}
	}
	else if (x <= fP.x && y <= fP.y) {//3
		if ((lP.x < x && lP.y > y) || (lP.x < x && lP.y == y) || (lP.x == x && lP.y > y)) {
//			cout << "nishizhen" << endl;
			return 1;
		}
		else {
//			cout << "shunshizhen" << endl;
			return -1;
		}
	}
	else if (x > fP.x && y < fP.y) {   //4
		if ((lP.x < x && lP.y < y) || (lP.x < x && lP.y == y) || (lP.x == x && lP.y < y)) {
//			cout << "nishizhen" << endl;
			return 1;
		}
		else {
//			cout << "shunshizhen" << endl;
			return -1;
		}
	}
	return 0;
}

/*旋转直线*/
void rotateLine(int x, int y) {
	//	int index = line.size() - 1;
//	deltX = x - clickX;
//	deltY = (winHeight - y) - clickY;
	int dir = getDirection(fixedPoint, lastPoint, x, y);
	double A = dir * getAngle(lastPoint.x, lastPoint.y, x, winHeight - y);
//	double sinA = sqrt(1 - pow(cosA, 2));
//	cout << cosA << endl;
	if (mouseLeftDown) {
		
		glColor3f(1.0, 1.0, 1.0);
		DDA(newBegin, newEnd);
		newBegin = line[index].begin;
		newEnd = line[index].end;

		scrPt m = newBegin;
		scrPt n = newEnd;
//		cout << m.x << " " << m.y << " " << n.x << " " << n.y << endl;
//		cout << (m.x - fixedPoint.x)* cosA - (m.y - fixedPoint.y)* sinA + fixedPoint.x << endl;
//		if (dir == -1) {
			newBegin.x = (m.x - fixedPoint.x)* cos(A) - (m.y - fixedPoint.y)* sin(A) + fixedPoint.x;
			newBegin.y = (m.x - fixedPoint.x)* sin(A) + (m.y - fixedPoint.y)* cos(A)+ fixedPoint.y;
			newEnd.x = (n.x - fixedPoint.x)* cos(A) - (n.y - fixedPoint.y)* sin(A) + fixedPoint.x;
			newEnd.y = (n.x - fixedPoint.x)* sin(A) + (n.y - fixedPoint.y)* cos(A) + fixedPoint.y;
/*		}
		else if (dir == 1) {
			A = -1 * A;
			newBegin.x = (m.x - fixedPoint.x)* cos(A) - (m.y - fixedPoint.y)* sin(A) + fixedPoint.x;
			newBegin.y = (m.x - fixedPoint.x)* sin(A) + (m.y - fixedPoint.y)* cos(A) + fixedPoint.y;
			newEnd.x = (n.x - fixedPoint.x)* cos(A) - (n.y - fixedPoint.y)* sin(A) + fixedPoint.x;
			newEnd.y = (n.x - fixedPoint.x)* sin(A) + (n.y - fixedPoint.y)* cos(A) + fixedPoint.y;
		}*/
		

//		cout << newBegin.x << " " << newBegin.y << " " << newEnd.x << " " << newEnd.y << endl;

		glColor3f(1.0, 0.0, 0.0);
		DDA(newBegin, newEnd);

		line[index].begin = newBegin;
		line[index].end = newEnd;
	}

	lastPoint.x = x;
	lastPoint.y = winHeight - y;
	
}

/*旋转Beizer曲线*/
void rotateBeizer(int x, int y) {
	int dir = getDirection(fixedPoint, lastPoint, x, y);
	double A = dir * getAngle(lastPoint.x, lastPoint.y, x, winHeight - y);
//	cout << dir << " " << A << endl;
	if (mouseLeftDown) {
		/*清除屏幕上的*/
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0);
		for (int i = 0; i < newPoint.size(); i++) {
			glBegin(GL_POINTS);
			glVertex2f(newPoint[i].x, newPoint[i].y);
			glEnd();
			glFlush();
		}
		glPointSize(1.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}
		drawBe(newPoint);

		/*改变点的位置*/
		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i] = bePt[index].beizerPt[i];
		}

		for (int i = 0; i < newPoint.size(); i++) {
			scrPt m = newPoint[i];
			newPoint[i].x = (m.x - fixedPoint.x)* cos(A) - (m.y - fixedPoint.y)* sin(A) + fixedPoint.x;
			newPoint[i].y = (m.x - fixedPoint.x)* sin(A) + (m.y - fixedPoint.y)* cos(A) + fixedPoint.y;
		}
	
		/*重新画出*/
		glColor3f(0.0, 0.0, 0.0);
		glPointSize(5.0);
		for (int i = 0; i < newPoint.size(); i++) {
			glBegin(GL_POINTS);
			glVertex2f(newPoint[i].x, newPoint[i].y);
			glEnd();
			glFlush();
		}
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(1.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}

		glColor3f(0.0, 0.0, 1.0);
		drawBe(newPoint);
//		glColor3f(1.0, 0.0, 0.0);

		for (int i = 0; i < newPoint.size(); i++) {
			bePt[index].beizerPt[i] = newPoint[i];
		}
	}

	lastPoint.x = x;
	lastPoint.y = winHeight - y;
}

/*旋转B样条曲线*/
void rotateBCurve(int x, int y) {
	int dir = getDirection(fixedPoint, lastPoint, x, y);
	double A = dir * getAngle(lastPoint.x, lastPoint.y, x, winHeight - y);
	//	cout << dir << " " << A << endl;
	if (mouseLeftDown) {
		/*清除屏幕上的*/
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0);
		for (int i = 0; i < newPoint.size(); i++) {
			glBegin(GL_POINTS);
			glVertex2f(newPoint[i].x, newPoint[i].y);
			glEnd();
			glFlush();
		}
		glPointSize(1.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}
		drawB(newPoint);

		/*改变点的位置*/
		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i] = bCurve[index].bPt[i];
		}

		for (int i = 0; i < newPoint.size(); i++) {
			scrPt m = newPoint[i];
			newPoint[i].x = (m.x - fixedPoint.x)* cos(A) - (m.y - fixedPoint.y)* sin(A) + fixedPoint.x;
			newPoint[i].y = (m.x - fixedPoint.x)* sin(A) + (m.y - fixedPoint.y)* cos(A) + fixedPoint.y;
		}

		/*重新画出*/
		glColor3f(0.0, 0.0, 0.0);
		glPointSize(5.0);
		for (int i = 0; i < newPoint.size(); i++) {
			glBegin(GL_POINTS);
			glVertex2f(newPoint[i].x, newPoint[i].y);
			glEnd();
			glFlush();
		}
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(1.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}

		glColor3f(0.0, 0.0, 1.0);
		drawB(newPoint);
		//		glColor3f(1.0, 0.0, 0.0);

		for (int i = 0; i < newPoint.size(); i++) {
			bCurve[index].bPt[i] = newPoint[i];
		}
	}

	lastPoint.x = x;
	lastPoint.y = winHeight - y;
}

/*旋转多边形*/
void rotatePolygon(int x, int y) {
	int dir = getDirection(fixedPoint, lastPoint, x, y);
	double A = dir * getAngle(lastPoint.x, lastPoint.y, x, winHeight - y);
//	cout << dir << " " << A << endl;
	if (mouseLeftDown) {
		glColor3f(1.0, 1.0, 1.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}
		DDA(newPoint[newPoint.size() - 1], newPoint[0]);
		if (polygon[index].color != 'n') {
			fillArea(newPoint, 'w');
		}

		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i] = polygon[index].point[i];
		}

//		if (dir == -1) {
			for (int i = 0; i < newPoint.size(); i++) {
				scrPt m = newPoint[i];
				newPoint[i].x = (m.x - fixedPoint.x)* cos(A) - (m.y - fixedPoint.y)* sin(A) + fixedPoint.x;
				newPoint[i].y = (m.x - fixedPoint.x)* sin(A) + (m.y - fixedPoint.y)* cos(A) + fixedPoint.y;
			}
/*		}
		else if (dir == 1) {
			A = -1 * A;
			for (int i = 0; i < newPoint.size(); i++) {
				scrPt m = newPoint[i];
				newPoint[i].x = (m.x - fixedPoint.x)* cos(A) - (m.y - fixedPoint.y)* sin(A) + fixedPoint.x;
				newPoint[i].y = (m.x - fixedPoint.x)* sin(A) + (m.y - fixedPoint.y)* cos(A) + fixedPoint.y;
			}
		}*/

	///		cout << "here" << endl;

		glColor3f(1.0, 0.0, 0.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}
		DDA(newPoint[newPoint.size() - 1], newPoint[0]);


		for (int i = 0; i < newPoint.size(); i++) {
			polygon[index].point[i] = newPoint[i];
		}

	/*	for (int i = 0; i < newPoint.size(); i++) {
			cout << newPoint[i].x << "~" << newPoint[i].y << endl;
		}*/
		if (polygon[index].color != 'n') {
			fillArea(newPoint, polygon[index].color);
		}
	}

	lastPoint.x = x;
	lastPoint.y = winHeight - y;
}

/*旋转圆*/
void rotateCircle(int x, int y) {
	int dir = getDirection(fixedPoint, lastPoint, x, y);
	double A = dir * getAngle(lastPoint.x, lastPoint.y, x, winHeight - y);

	if (mouseLeftDown) {
		glColor3f(1.0, 1.0, 1.0);
		MidPoint_Circle(newCenter, circle[index].radius);
		newCenter = circle[index].center;

		scrPt m = newCenter;
		newCenter.x = (m.x - fixedPoint.x)* cos(A) - (m.y - fixedPoint.y)* sin(A) + fixedPoint.x;;
		newCenter.y = (m.x - fixedPoint.x)* sin(A) + (m.y - fixedPoint.y)* cos(A) + fixedPoint.y;;

		glColor3f(1.0, 0.0, 0.0);
		MidPoint_Circle(newCenter, circle[index].radius);

		circle[index].center = newCenter;
	}

	lastPoint.x = x;
	lastPoint.y = winHeight - y;
}

void judgeShapeR() {
	if (lastEdit == 0) {
		if (!line.empty()) {
			index = line.size() - 1;
		}
		else {
			cout << "无可旋转图形！" << endl;
			endPtctr = 2;
		}
		newBegin = line[index].begin;
		newEnd = line[index].end;
		glutMouseFunc(rotate);
		glutMotionFunc(rotateLine);
	}
	else if (lastEdit == 1) {
		if (!circle.empty()) {
			index = circle.size() - 1;
		}
		else {
			cout << "无可旋转图形！" << endl;
			endPtctr = 2;
		}
		if (circle[index].radius == circle[index].radiusY) {
			newCenter = circle[index].center;
	//		radius = circle[index].radius;
			glutMouseFunc(rotate);
			glutMotionFunc(rotateCircle);
		}
		else {
			cout << "该图形不可旋转！" << endl;
			endPtctr = 2;
		}
		
	}
	else if (lastEdit == 3) {
//		cout << "BeizerCurve" << endl;
		if (!bePt.empty()) {
			index = bePt.size() - 1;
//			cout << index << endl;
		}
		else {
			cout << "无可旋转图形！" << endl;
			endPtctr = 2;
		}
		newPoint.clear();
		for (int i = 0; i < bePt[index].beizerPt.size(); i++) {
			newPoint.push_back(bePt[index].beizerPt[i]);
		}
		glutMouseFunc(rotate);
		glutMotionFunc(rotateBeizer);
	}
	else if (lastEdit == 4) {
//		cout << "polygon" << endl;
		if (!polygon.empty()) {
			index = polygon.size() - 1;
		}
		else {
			cout << "无可旋转图形！" << endl;
			endPtctr = 2;
		}
		newPoint.clear();
		for (int i = 0; i < polygon[index].point.size(); i++) {
			newPoint.push_back(polygon[index].point[i]);
		}
		glutMouseFunc(rotate);
		glutMotionFunc(rotatePolygon);
		//		translatePolygon();
	}
	else if (lastEdit == 5) {
//		cout << "BCurve" << endl;
		if (!bCurve.empty()) {
			index = bCurve.size() - 1;
			//			cout << index << endl;
		}
		else {
			cout << "无可旋转图形！" << endl;
			endPtctr = 2;
		}
		newPoint.clear();
		for (int i = 0; i < bCurve[index].bPt.size(); i++) {
			newPoint.push_back(bCurve[index].bPt[i]);
		}
		glutMouseFunc(rotate);
		glutMotionFunc(rotateBCurve);
	}
	else {
		cout << "无可旋转图形！" << endl;
		endPtctr = 2;
	}
}


void rotate(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	//	int index = line.size() - 1;
	if (button == GLUT_LEFT_BUTTON && endPtctr == 0) {
		if (action == GLUT_DOWN) {
			fixedPoint.x = xMouse;
			fixedPoint.y = winHeight - yMouse;
		}
		else if (action == GLUT_UP) {
			endPtctr++;
//			cout << fixedPoint.x << " " << fixedPoint.y << endl;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && endPtctr == 1) {
		clickX = xMouse;
		clickY = winHeight - yMouse;
		lastPoint.x = clickX;
		lastPoint.y = clickY;
		if (action == GLUT_DOWN) {
			mouseLeftDown = true;
//			cout << "true" << endl;
		}
		else {
			mouseLeftDown = false;
			endPtctr++;
			switch (lastEdit) {
			case 0:line[index].begin = newBegin;
				line[index].end = newEnd; break;
			case 1:circle[index].center = newCenter; break;
			case 3:
				for (int i = 0; i < newPoint.size(); i++) {
					bePt[index].beizerPt[i] = newPoint[i];
				}
				   break;
			case 4:
				for (int i = 0; i < newPoint.size(); i++) {
					polygon[index].point[i] = newPoint[i];
				}
				break;
			case 5:
				for (int i = 0; i < newPoint.size(); i++) {
					bCurve[index].bPt[i] = newPoint[i];
				}
				break;
			default:break;
			}
//			cout << "false" << endl;
		}
	}

	glutPostRedisplay();
}