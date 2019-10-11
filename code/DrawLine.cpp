#include "DrawLine.h"

vector<linePt> line;
static scrPt endPt1, endPt2;

void initLine() {
	endPtctr = 0;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void DDA(scrPt pointA, scrPt pointB) {

	GLfloat delta_x, delta_y, x, y;
	int steps;
	scrPt d;
	d.x = pointB.x - pointA.x;
	d.y = pointB.y - pointA.y;

	if (abs(d.x)>abs(d.y))
		steps = abs(d.x);
	else
		steps = abs(d.y);

	delta_x = (GLfloat)d.x / (GLfloat)steps;
	delta_y = (GLfloat)d.y / (GLfloat)steps;
	x = pointA.x;
	y = pointA.y;
	glBegin(GL_POINTS);
		glVertex3f(x, y, 0);
	glEnd();
	for (int k = 1; k <= steps; k++) {
		x += delta_x;
		y += delta_y;
		glBegin(GL_POINTS);
			glVertex3f(x, y, 0);
		glEnd();
	}
	glFlush();
}


void drawPoint(GLint x, GLint y) {
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	//	glFlush();  
}

void saveL() {
	linePt l;
	l.begin = endPt1;
	l.end = endPt2;
	line.push_back(l);
}

void saveLine(unsigned char key, int x, int y) {
	if (key == 's') {
	/*	linePt l;
		l.begin = endPt1;
		l.end = endPt2;
		line.push_back(l);*/
	}
//	cout << "saveOK" << endl;
}

void drawLine(GLint button, GLint action, GLint xMouse, GLint yMouse) {
//	static scrPt endPt1, endPt2;

	if (endPtctr == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			//		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			endPt1.x = xMouse;
			endPt1.y = winHeight - yMouse;
			//           drawPoint(xMouse,winHeight-yMouse);  
			endPtctr = 1;
		}
	/*	else if (button == GLUT_MIDDLE_BUTTON && action == GLUT_DOWN){
			cout<<"clearOK"<<endl;
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );       //clear screen
			endPtctr = 0;
		}*/
	}
	else if (endPtctr == 1) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			endPt2.x = xMouse;
			endPt2.y = winHeight - yMouse;
			DDA(endPt1, endPt2);
			//			endPt1 = endPt2;  
			endPtctr = 2;
			saveL();
			glutKeyboardFunc(saveLine);
		}
	/*	else if (button == GLUT_MIDDLE_BUTTON && action == GLUT_DOWN) {
			cout<<"clearOK"<<endl;
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			endPtctr = 0;
		}*/
	}
	
	glFlush();
	lastEdit = 0;
}

