#include "EditLine.h"

static int index;
static int endPtctr;
static int pointIndex;
static double deltX, deltY;
static bool mouseLeftDown;
static scrPt click;

void initEditLine() {
	endPtctr = 0;
	if (!line.empty()) {
		index = line.size() - 1;
	}
	else {
		cout << "无可编辑直线！" << endl;
		endPtctr = 1;
	}
}
/*计算鼠标点击的点到直线两端点的距离*/
static double calcuDis(scrPt p1, scrPt p2) {
	double dis = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return dis;
}
/*判断鼠标点击的点是直线的哪个端点*/
static int judgePoint(scrPt click) {
	int p = -1;
	double disB = calcuDis(line[index].begin, click);
	double disE = calcuDis(line[index].end, click);
//	cout << disB << " " << disE << endl;
	p = disB < disE ? 0 : 1;
	return p;
}

void editL(int x, int y) {
	if (mouseLeftDown) {
		glColor3f(1.0, 1.0, 1.0);
		DDA(line[index].begin, line[index].end);
		if (pointIndex == 0) {
			deltX = x - line[index].begin.x;
			deltY = (winHeight - y) - line[index].begin.y;
			line[index].begin.x += deltX;
			line[index].begin.y += deltY;
		}
		else if (pointIndex == 1) {
			deltX = x - line[index].end.x;
			deltY = (winHeight - y) - line[index].end.y;
			line[index].end.x += deltX;
			line[index].end.y += deltY;
		}

		glColor3f(1.0, 0.0, 0.0);
		DDA(line[index].begin, line[index].end);
	}
	
}

void editLine(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	
	click.x = xMouse;
	click.y = winHeight - yMouse;
	
//	cout << pointIndex << endl;
	if (button == GLUT_LEFT_BUTTON && endPtctr == 0) {
		if (action == GLUT_DOWN) {
			mouseLeftDown = true;
			pointIndex = judgePoint(click);//判断点击的是哪个点
	//		cout << "true" << endl;
		}
		else {
			mouseLeftDown = false;
			endPtctr++;
//			cout << "false" << endl;
		}

	}
	glutPostRedisplay();
}