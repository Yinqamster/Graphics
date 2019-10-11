#include "Translation.h"


static bool mouseLeftDown;
static int clickX, clickY;
static int deltX, deltY;
static scrPt newBegin, newEnd;
static scrPt newCenter;
static double  radius;
static int endPtctr;
static int index;
static vector<scrPt> newPoint;

void initTranslation() {
	endPtctr = 0;
}
/*平移直线*/
void translateLine(int x, int y) {
//	int index = line.size() - 1;
	deltX = x - clickX;
	deltY = (winHeight - y) - clickY;

	if (mouseLeftDown) {
		glColor3f(1.0, 1.0, 1.0);
		DDA(newBegin, newEnd);
		newBegin = line[index].begin;
		newEnd = line[index].end;

		newBegin.x += deltX;
		newBegin.y += deltY;
		newEnd.x += deltX;
		newEnd.y += deltY;

		glColor3f(1.0, 0.0, 0.0);
		DDA(newBegin, newEnd);
	}

	
}
/*平移圆*/
void translateCircle(int x, int y) {
	//	int index = line.size() - 1;
	deltX = x - clickX;
	deltY = (winHeight - y) - clickY;

	if (mouseLeftDown) {
		glColor3f(1.0, 1.0, 1.0);
	//	MidPoint_Circle(newCenter, radius);
		middle_ellipse(newCenter, circle[index].radius, circle[index].radiusY);
		newCenter = circle[index].center;

		newCenter.x += deltX;
		newCenter.y += deltY;

		glColor3f(1.0, 0.0, 0.0);
	//	MidPoint_Circle(newCenter, radius);
		middle_ellipse(newCenter, circle[index].radius, circle[index].radiusY);
	}
}
/*平移椭圆*/
void translateEllipse(int x, int y) {
	//	int index = line.size() - 1;
	deltX = x - clickX;
	deltY = (winHeight - y) - clickY;

	if (mouseLeftDown) {
		glColor3f(1.0, 1.0, 1.0);
		middle_ellipse(newCenter, ellipse[index].longAxis, ellipse[index].minAxis);
		newCenter = ellipse[index].center;

		newCenter.x += deltX;
		newCenter.y += deltY;

		glColor3f(1.0, 0.0, 0.0);
		middle_ellipse(newCenter, ellipse[index].longAxis, ellipse[index].minAxis);
	}
}
/*平移Beizer曲线*/
void translateBeizer(int x, int y) {
	deltX = x - clickX;
	deltY = (winHeight - y) - clickY;

	if (mouseLeftDown) {
		/*清除屏幕上的*/
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5.0);
//		glColor3f(0.0, 0.0, 0.0);
		for (int i = 0; i < newPoint.size(); i++) {	
			glBegin(GL_POINTS);
			glVertex2f(newPoint[i].x, newPoint[i].y);
			glEnd();
			glFlush();
		}
		glPointSize(1.0);
//		glColor3f(1.0, 1.0, 1.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}
//		glColor3f(0.0, 0.0, 0.1);
		drawBe(newPoint);

		/*更新点位置*/
		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i] = bePt[index].beizerPt[i];
		}

		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i].x += deltX;
			newPoint[i].y += deltY;
		}

		/*重新画出图形*/
//		glColor3f(1.0, 0.0, 0.0);
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

		glColor3f(1.0, 0.0, 0.0);
	}
}
/*平移B样条曲线*/
void translateBCurve(int x, int y) {
	deltX = x - clickX;
	deltY = (winHeight - y) - clickY;

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

		/*更新点位置*/
		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i] = bCurve[index].bPt[i];
		}

		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i].x += deltX;
			newPoint[i].y += deltY;
		}

		/*重新画出图形*/
		//		glColor3f(1.0, 0.0, 0.0);
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

		glColor3f(1.0, 0.0, 0.0);
	}
}
/*平移多边形*/
void translatePolygon(int x, int y) {
	//	int index = line.size() - 1;
	deltX = x - clickX;
	deltY = (winHeight - y) - clickY;

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

		for (int i = 0; i < newPoint.size(); i++) {
			newPoint[i].x += deltX;
			newPoint[i].y += deltY;
		}

		glColor3f(1.0, 0.0, 0.0);
		for (int i = 0; i < newPoint.size() - 1; i++) {
			DDA(newPoint[i], newPoint[i + 1]);
		}
		DDA(newPoint[newPoint.size() - 1], newPoint[0]);

		if (polygon[index].color != 'n') {
			fillArea(newPoint, polygon[index].color);
		}
	}
}



void judgeShape() {
	if (lastEdit == 0) {
		if (!line.empty()) {
			index = line.size() - 1;
		}
		else {
			cout << "无可移动图形！" << endl;
			endPtctr = 1;
		}
		newBegin = line[index].begin;
		newEnd = line[index].end;
		glutMouseFunc(translation);
		glutMotionFunc(translateLine);	
	}
	else if (lastEdit == 1) {
		if (!circle.empty()) {
			index = circle.size() - 1;
		}
		else {
			cout << "无可移动图形！" << endl;
			endPtctr = 1;
		}
		newCenter = circle[index].center;
		radius = circle[index].radius;
		glutMouseFunc(translation);
		glutMotionFunc(translateCircle);
	}
	else if (lastEdit == 2) {
		if (!ellipse.empty()) {
			index = ellipse.size() - 1;
		}
		else {
			cout << "无可移动图形！" << endl;
			endPtctr = 1;
		}
		newCenter = ellipse[index].center;
		glutMouseFunc(translation);
		glutMotionFunc(translateEllipse);
//		cout << "ellipse" << endl;
//		translateEllipse();
	}
	else if (lastEdit == 3) {
//		cout << "BeizerCurve" << endl;
		if (!bePt.empty()) {
			index = bePt.size() - 1;
//			cout << index << endl;
		}
		else {
			cout << "无可移动图形！" << endl;
			endPtctr = 1;
		}
		newPoint.clear();
		for (int i = 0; i < bePt[index].beizerPt.size(); i++) {
			newPoint.push_back(bePt[index].beizerPt[i]);
		}
		glutMouseFunc(translation);
		glutMotionFunc(translateBeizer);
	}
	else if (lastEdit == 4) {
//		cout << "polygon" << endl;
		if (!polygon.empty()) {
			index = polygon.size() - 1;
		}
		else {
			cout << "无可移动图形！" << endl;
			endPtctr = 1;
		}
		newPoint.clear();
		for (int i = 0; i < polygon[index].point.size(); i++) {
			newPoint.push_back(polygon[index].point[i]);
		}
		glutMouseFunc(translation);
		glutMotionFunc(translatePolygon);
//		translatePolygon();
	}
	else if (lastEdit == 5) {
//		cout << "BCurve" << endl;
		if (!bCurve.empty()) {
			index = bCurve.size() - 1;
			//			cout << index << endl;
		}
		else {
			cout << "无可移动图形！" << endl;
			endPtctr = 1;
		}
		newPoint.clear();
		for (int i = 0; i < bCurve[index].bPt.size(); i++) {
			newPoint.push_back(bCurve[index].bPt[i]);
		}
		glutMouseFunc(translation);
		glutMotionFunc(translateBCurve);
	}
	else {
		cout << "无可移动图形！" << endl;
		endPtctr = 1;
	}
}


void translation(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	clickX = xMouse;
	clickY = winHeight - yMouse;
//	int index = line.size() - 1;
	if (button == GLUT_LEFT_BUTTON && endPtctr == 0) {
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
			case 2:ellipse[index].center = newCenter; break;
			case 3:for (int i = 0; i < newPoint.size(); i++) {
						bePt[index].beizerPt[i] = newPoint[i];
					}
				   break;
			case 4:
				for (int i = 0; i < newPoint.size(); i++) {
					polygon[index].point[i] = newPoint[i];
		//			newPoint.push_back(polygon[index].point[i]);
				}
				break;
			case 5:for (int i = 0; i < newPoint.size(); i++) {
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