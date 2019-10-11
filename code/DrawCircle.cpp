#include "DrawCircle.h"

static scrPt center, point;
vector<circlePt> circle;
static double radius;

void initCircle(){
	endPtctr = 0;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

// 画点

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
	glFlush();
}

//8路对称

void Cirpot(scrPt c, int x, int y){
	// 1
	setPixel((c.x + x), (c.y + y));
	// 2
	setPixel((c.x + y), (c.y + x));
	// 3
	setPixel((c.x + y), (c.y - x));
	// 4
	setPixel((c.x + x), (c.y - y));
	// 5
	setPixel((c.x - x), (c.y - y));
	// 6
	setPixel((c.x - y), (c.y - x));
	// 7
	setPixel((c.x - y), (c.y + x));
	// 8
	setPixel((c.x - x), (c.y + y));
}

//中点画圆算法

void MidPoint_Circle(scrPt c, double r) {
	int x = 0;
	int y = r;
	int d = 1 - r;      // d = 1.25-r的取整的结果
	Cirpot(c, x, y);
	while (x < y) {
		if (d < 0) {
			d += 2 * x + 3;
		}
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		Cirpot(c, x, y);
	}
}

void saveC() {
	circlePt c;
	c.center = center;
	c.radius = radius;
	c.radiusY = radius;
	circle.push_back(c);
}

void saveCircle(unsigned char key, int x, int y) {
	if (key == 's') {
	/*	circlePt c;
		c.center = center;
		c.radius = radius;
		circle.push_back(c);*/
	}
//	cout << "saveOK" << endl;
}

void drawCircle(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (endPtctr == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			center.x = xMouse;
			center.y = winHeight - yMouse;
			endPtctr = 1;
		}
	}
	else if (endPtctr == 1) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			point.x = xMouse;
			point.y = winHeight - yMouse;
			radius = sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2));
			MidPoint_Circle(center, radius);
			endPtctr = 2;
			saveC();
			glutKeyboardFunc(saveCircle);
		}
	}

	glFlush();
	lastEdit = 1;
}

