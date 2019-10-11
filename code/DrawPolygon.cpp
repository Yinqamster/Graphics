#include "DrawPolygon.h"
#include "DrawLine.h"

static polygonPt pPt;
vector<polygonPt> polygon;
static scrPt endPt1, endPt2;
static int finish;

void initPolygon() {
	pPt.point.clear();
	endPtctr = 0;
	finish = 0;
//	pPt = new polygonPt();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}


static void savePoint(scrPt p) {
	pPt.point.push_back(p);
	pPt.color = 'n';
//	cout << pPt.point[0].x << " " << pPt.point[0].y<<endl;
	//	cout << "saveOK" << endl;
}

/*
void saveP() {
	polygon.push_back(pPt);
}*/


static void finishDraw(unsigned char key, int x, int y) {
//	cout << "here" << endl;
	if (key == 13) {
		endPtctr = 2;
//		cout << endl<< pPt.point[0].x << endl << endl;
		if (finish == 0) {
			endPt2 = pPt.point[0];
			DDA(endPt1, endPt2);
			finish = 1;
		}

//		saveP();
//		savePoint();
	}
//	else if (key == 's') {
//		polygon.push_back(pPt);
//		cout << "ok" << endl;
//	}

/*	for (int i = 0; i < polygon.size(); i++) {
		for (int j = 0; j < polygon[i].point.size(); j++) {
			cout << polygon[i].point[j].x <<" "<<polygon[i].point[j].y<< endl;
		}
		cout << endl;
	}*/
}


void drawPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	//	static scrPt endPt1, endPt2;
	if (endPtctr == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			//		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			endPt1.x = xMouse;
			endPt1.y = winHeight - yMouse;
			//           drawPoint(xMouse,winHeight-yMouse);  
			savePoint(endPt1);
			polygon.push_back(pPt);
			endPtctr = 1;
		}
	}
	else if (endPtctr == 1) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			endPt2.x = xMouse;
			endPt2.y = winHeight - yMouse;
			DDA(endPt1, endPt2);
			//			endPt1 = endPt2;  
	//		endPtctr = 0;
			savePoint(endPt2);
			endPt1 = endPt2;
			
//			copy(pPt, temp);
//			pPt = temp; 
	//		saveP();
			polygon.pop_back();
			polygon.push_back(pPt);
			glutKeyboardFunc(finishDraw);
//			glutKeyboardFunc(savePolygon);

/*			for (int i = 0; i < pPt.point.size(); i++) {
				cout <<endl<< temp.point[i].x << endl<<endl;
			}*/
		}
	}

	glFlush();
	lastEdit = 4;
}

