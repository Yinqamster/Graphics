#include "DrawEllipse.h"

static scrPt centerE;
static double longAxis, minAxis;
vector<ellipsePt> ellipse;

void initEllipse(){
	endPtctr = 0;
//	longAxis = 60;
//	minAxis = 40;
	cout << "请输入椭圆平行于x轴的轴的长度：";
	cin >> longAxis;
	cout << "请输入椭圆平行于y轴的轴的长度：";
	cin >> minAxis;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void middle_ellipse(scrPt center, double longA, double minA) {
	double sqa = longA*longA;
	double sqb = minA*minA;
	double d = sqb + sqa*(0.25 - minA);
	double x = 0;
	double y = minA;
	glBegin(GL_POINTS);
		glVertex2i(center.x + x, center.y + y);
		glVertex2i(center.x - x, center.y + y);
		glVertex2i(center.x + x, center.y - y);
		glVertex2i(center.x - x, center.y - y);
		while ((double)sqb*(x + 1) < (double)sqa*(y - 0.5)) {
			if (d < 0)
				d += sqb*(2 * x + 3);
			else {
				d += sqb*(2 * x + 3) + sqa*(-2 * y + 2);
				y--;
			}
			x++;
			glVertex2d(center.x + x, center.y + y);
			glVertex2d(center.x - x, center.y + y);
			glVertex2d(center.x + x, center.y - y);
			glVertex2d(center.x - x, center.y - y);
		}
		d = (minA*(x + 0.5)) * 2 + (longA*(y - 1)) * 2 - (longA*minA) * 2;
		while (y > 0) {
			if (d < 0) {
				d += sqb*(2 * x + 2) + sqa*(-2 * y + 3);
				x++;
			}
			else
				d += sqa*(-2 * y + 3);
			y--;
			glVertex2d(center.x + x, center.y + y);
			glVertex2d(center.x - x, center.y + y);
			glVertex2d(center.x + x, center.y - y);
			glVertex2d(center.x - x, center.y - y);
		}
	glEnd();
	glFlush();
}

void saveE() {
	ellipsePt e;
	e.center = centerE;
	e.longAxis = longAxis;
	e.minAxis = minAxis;
	ellipse.push_back(e);
//	cout << "ok" << endl;
}

void saveEllipse(unsigned char key, int x, int y) {
	if (key == 's') {
	/*	ellipsePt e;
		e.center = centerE;
		e.longAxis = longAxis;
		e.minAxis = minAxis;
		ellipse.push_back(e);*/
	}
//	cout << "saveOK" << endl;
}

void drawEllipse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (endPtctr == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			centerE.x = xMouse;
			centerE.y = winHeight - yMouse;
			endPtctr = 1;
			middle_ellipse(centerE, longAxis, minAxis);
			saveE();
//			cout << ellipse.size();
			glutKeyboardFunc(saveEllipse);
		}
	}

	glFlush();
	lastEdit = 2;
}