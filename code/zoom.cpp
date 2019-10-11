#include "zoom.h"

#define  GLUT_WHEEL_UP 3           //定义滚轮操作  
#define  GLUT_WHEEL_DOWN 4  

static scrPt fixedPoint;
static scrPt newBegin, newEnd;
static scrPt newCenter;
static double newRadiusX;
static double newRadiusY;
static double newLongAxis;
static double newMinAxis;
static vector<scrPt> newPoint;
static double amount;

static int endPtctr;
static int index;


void initZoom() {
	endPtctr = 0;
	amount = 1;
}
/*缩放圆*/
void zoomCircle(double amount) {
	glColor3f(1.0, 1.0, 1.0);
	middle_ellipse(newCenter, circle[index].radius, circle[index].radiusY);
//	MidPoint_Circle(newCenter, newRadius);
//	double n = newRadius;

	newCenter = circle[index].center;
//	newRadiusX = circle[index].radius;
//	newRadiusY = circle[index].radiusY;
	scrPt m = newCenter;
	newCenter.x = (m.x - fixedPoint.x)* amount + fixedPoint.x;
	newCenter.y = (m.y - fixedPoint.y)* amount + fixedPoint.y;
/*	if (newRadius > 0) {
		newRadius += amount;
	}*/
	newRadiusX = circle[index].radius * amount;
	newRadiusY = circle[index].radiusY * amount;
	glColor3f(1.0, 0.0, 0.0);
	middle_ellipse(newCenter, newRadiusX, newRadiusY);
//	MidPoint_Circle(newCenter, newRadius);

	circle[index].center = newCenter;
	circle[index].radius = newRadiusX;
	circle[index].radiusY = newRadiusY;
}
/*缩放Beizer曲线*/
void zoomBeizer(double amount) {
	
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
		newPoint[i].x = (m.x - fixedPoint.x)* amount + fixedPoint.x;
		newPoint[i].y = (m.y - fixedPoint.y)* amount + fixedPoint.y;
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
/*缩放B样条曲线*/
void zoomBCurve(double amount) {
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
		newPoint[i].x = (m.x - fixedPoint.x)* amount + fixedPoint.x;
		newPoint[i].y = (m.y - fixedPoint.y)* amount + fixedPoint.y;
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

/*缩放多边形*/
void zoomPolygon(double amount) {
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
		scrPt m = newPoint[i];
		newPoint[i].x = (m.x - fixedPoint.x)* amount + fixedPoint.x;
		newPoint[i].y = (m.y - fixedPoint.y)* amount + fixedPoint.y;
	}

	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < newPoint.size() - 1; i++) {
		DDA(newPoint[i], newPoint[i + 1]);
	}
	DDA(newPoint[newPoint.size() - 1], newPoint[0]);
	if (polygon[index].color != 'n') {
		fillArea(newPoint, polygon[index].color);
	}


//	polygon[index].point.clear();
	for (int i = 0; i < newPoint.size(); i++) {
//		polygon[index].point.push_back(newPoint[i]);
		polygon[index].point[i] = newPoint[i];
	}
}

/*缩放椭圆*/
void zoomEllipse(double amount) {
	glColor3f(1.0, 1.0, 1.0);
	middle_ellipse(newCenter, newLongAxis, newMinAxis);
	newCenter = ellipse[index].center;


	scrPt m = newCenter;
	newCenter.x = (m.x - fixedPoint.x)* amount + fixedPoint.x;
	newCenter.y = (m.y - fixedPoint.y)* amount + fixedPoint.y;
	newLongAxis = ellipse[index].longAxis * amount;
	newMinAxis = ellipse[index].minAxis * amount;

	glColor3f(1.0, 0.0, 0.0);
	middle_ellipse(newCenter, newLongAxis, newMinAxis);

	ellipse[index].center = newCenter;
	ellipse[index].longAxis = newLongAxis;
	ellipse[index].minAxis = newMinAxis;
}

/*缩放直线*/
void zoomLine(double amount) {
	glColor3f(1.0, 1.0, 1.0);
	DDA(newBegin, newEnd);
	newBegin = line[index].begin;
	newEnd = line[index].end;

	scrPt m = newBegin;
	scrPt n = newEnd;
	newBegin.x = (m.x - fixedPoint.x)* amount + fixedPoint.x;
	newBegin.y = (m.y - fixedPoint.y)* amount + fixedPoint.y;
	newEnd.x = (n.x - fixedPoint.x)* amount + fixedPoint.x;
	newEnd.y = (n.y - fixedPoint.y)* amount + fixedPoint.y;

	glColor3f(1.0, 0.0, 0.0);
	DDA(newBegin, newEnd);

	line[index].begin = newBegin;
	line[index].end = newEnd;
}

void judgeShapeZ() {
	if (lastEdit == 0) {
		if (!line.empty()) {
			index = line.size() - 1;
		}
		else {
			cout << "无可缩放图形！" << endl;
			endPtctr = 2;
		}
		newBegin = line[index].begin;
		newEnd = line[index].end;
		glutMouseFunc(zoom);
	}
	else if (lastEdit == 1) {
		if (!circle.empty()) {
			index = circle.size() - 1;
		}
		else {
			cout << "无可缩放图形！" << endl;
			endPtctr = 2;
		}
		newCenter = circle[index].center;
		newRadiusX = circle[index].radius;
		newRadiusY = circle[index].radiusY;
		glutMouseFunc(zoom);
	}
	else if (lastEdit == 2) {
		if (!ellipse.empty()) {
			index = ellipse.size() - 1;
		}
		else {
			cout << "无可缩放图形！" << endl;
			endPtctr = 2;
		}
		newCenter = ellipse[index].center;
		newLongAxis = ellipse[index].longAxis;
		newMinAxis = ellipse[index].minAxis;
		glutMouseFunc(zoom);
	}
	else if (lastEdit == 3) {
//		cout << "beizerCurve" << endl;
		if (!bePt.empty()) {
			index = bePt.size() - 1;
			//			cout << index << endl;
		}
		else {
			cout << "无可缩放图形！" << endl;
			endPtctr = 2;
		}
		newPoint.clear();
		for (int i = 0; i < bePt[index].beizerPt.size(); i++) {
			newPoint.push_back(bePt[index].beizerPt[i]);
		}
		glutMouseFunc(zoom);
	}
	else if (lastEdit == 4) {
//		cout << "polygon" << endl;
		if (!polygon.empty()) {
			index = polygon.size() - 1;
		}
		else {
			cout << "无可缩放图形！" << endl;
			endPtctr = 2;
		}
		newPoint.clear();
		for (int i = 0; i < polygon[index].point.size(); i++) {
			newPoint.push_back(polygon[index].point[i]);
		}
		glutMouseFunc(zoom);
		
	}
	else if (lastEdit == 5) {
//		cout << "bCurve" << endl;
		if (!bCurve.empty()) {
			index = bCurve.size() - 1;
			//			cout << index << endl;
		}
		else {
			cout << "无可缩放图形！" << endl;
			endPtctr = 2;
		}
		newPoint.clear();
		for (int i = 0; i < bCurve[index].bPt.size(); i++) {
			newPoint.push_back(bCurve[index].bPt[i]);
		}
		glutMouseFunc(zoom);
	}
	else {
		cout << "无可缩放图形！" << endl;
		endPtctr = 2;
	}
}


void zoom(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	//定点的xy 关于xy的缩放比例
	amount = 1;
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
		if (action == GLUT_DOWN) {
			endPtctr++;
		}
	}

	if (endPtctr != 2) {
//		cout << "here" << endl;
		if (action == GLUT_UP && button == GLUT_WHEEL_UP) {  //放大
			amount += 0.03;
			switch (lastEdit) {
			case 0: zoomLine(amount); break;
			case 1: zoomCircle(amount); break;
			case 2: zoomEllipse(amount); break;
			case 3: zoomBeizer(amount); break;
			case 4: zoomPolygon(amount); break;
			case 5: zoomBCurve(amount); break;
			default:break;
			}
		}
		if (action == GLUT_UP && button == GLUT_WHEEL_DOWN) {  //缩小
			if (amount >= 0.03) {
				amount -= 0.03;
			}
			switch (lastEdit) {
			case 0: zoomLine(amount); break;
			case 1:	zoomCircle(amount); break;
			case 2: zoomEllipse(amount); break;
			case 3: zoomBeizer(amount); break;
			case 4: zoomPolygon(amount);break;
			case 5: zoomBCurve(amount); break;
			default:break;
			}
		}
	}
	glutPostRedisplay();

/*	switch (lastEdit) {
	case 0:line[index].begin = newBegin;
		line[index].end = newEnd; break;
	case 1:circle[index].center = newCenter; break;
	case 2:ellipse[index].center = newCenter; break;
	case 4:
		for (int i = 0; i < newPoint.size(); i++) {
			polygon[index].point[i] = newPoint[i];
			//			newPoint.push_back(polygon[index].point[i]);
		}
		break;
	default:break;
	}*/
}