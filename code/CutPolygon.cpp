#include "CutPolygon.h"
static cutFrame* cf;
static int index;
static int endPtctr;
static bool mouseLeftDownDraw;
static bool mouseLeftDownEdit;
static int pointIndex;
static int number;
static scrPt cfBegin;
static scrPt cfEnd;
static scrPt click;
/*裁剪后的多边形的顶点*/
struct Point {
	scrPt p;
	int code;
}cfPoint[4], p1[20], p2[20], p3[20], p4[20];
vector<Point> points;
//Point points[10];
int  p1n, p2n, p3n, p4n;
double xmin, xmax, ymin, ymax;

void initCutPolygon() {
	endPtctr = 0;
	cf = new cutFrame();
	p1n = 0;
	p2n = 0;
	p3n = 0;
	p4n = 0;
	if (!polygon.empty()) {
		index = polygon.size() - 1;
		number = polygon[index].point.size();
		points.clear();
		for (int i = 0; i < number; i++) {
			Point p;
			p.p = polygon[index].point[i];
	//		p.code = -1;
			points.push_back(p);
		}
/*		for (int i = 0; i < number; i++) {
			p4[i].p.x = points[i].p.x;
			p4[i].p.y = points[i].p.y;
			cout << p4[i].p.x <<" " << p4[i].p.y << endl;
		}
		p4n = number;*/
	}
	else {
		cout << "无可裁剪多边形！" << endl;
		endPtctr = 2;
	}
}

static double calcuDis(scrPt p1, scrPt p2) {
	double dis = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return dis;
}

static int judgePoint(scrPt click) {
	int p = -1;
	int* disOfPoints = new int[4];
	
	disOfPoints[0] = calcuDis(cf->leftUp, click);
	disOfPoints[1] = calcuDis(cf->leftDown, click);
	disOfPoints[2] = calcuDis(cf->rightDown, click);
	disOfPoints[3] = calcuDis(cf->rightUp, click);
	
	int min = disOfPoints[0];
	p = 0;
	for (int i = 0; i < 4; i++) {
		if (disOfPoints[i] < min) {
			min = disOfPoints[i];
			p = i;
		}
	}
	return p;
}

void editCf(int x, int y) {
	if (mouseLeftDownEdit) {
		glColor3f(1.0, 1.0, 1.0);
		DDA(cf->leftUp, cf->leftDown);
		DDA(cf->leftDown, cf->rightDown);
		DDA(cf->rightDown, cf->rightUp);
		DDA(cf->rightUp, cf->leftUp);

		
		double deltX, deltY;
		switch (pointIndex) {
		case 0: {
			deltX = x - cf->leftUp.x;
			deltY = (winHeight - y) - cf->leftUp.y;
			cf->leftUp.x += deltX;
			cf->leftUp.y += deltY;
			cf->leftDown.x += deltX;
			cf->rightUp.y += deltY;
			break;
		}
		case 1: {
			deltX = x - cf->leftDown.x;
			deltY = (winHeight - y) - cf->leftDown.y;
			cf->leftDown.x += deltX;
			cf->leftDown.y += deltY;
			cf->leftUp.x += deltX;
			cf->rightDown.y += deltY;
			break;
		}
		case 2: {
			deltX = x - cf->rightDown.x;
			deltY = (winHeight - y) - cf->rightDown.y;
			cf->rightDown.x += deltX;
			cf->rightDown.y += deltY;
			cf->rightUp.x += deltX;
			cf->leftDown.y += deltY;
			break;
		}
		case 3: {
			deltX = x - cf->rightUp.x;
			deltY = (winHeight - y) - cf->rightUp.y;
			cf->rightUp.x += deltX;
			cf->rightUp.y += deltY;
			cf->rightDown.x += deltX;
			cf->leftUp.y += deltY;
			break;
		}
		default:break;
		}
		

		glColor3f(0.0, 0.0, 0.0);
		DDA(cf->leftUp, cf->leftDown);
		DDA(cf->leftDown, cf->rightDown);
		DDA(cf->rightDown, cf->rightUp);
		DDA(cf->rightUp, cf->leftUp);
		if (polygon[index].color != 'n') {
			fillArea(polygon[index].point, polygon[index].color);
		}
	/*	switch (pointIndex) {
		case 0:DDA(cf.leftUp, cf.leftDown); DDA(cf.rightUp, cf.leftUp); break;
		case 1:DDA(cf.leftUp, cf.leftDown); DDA(cf.leftDown, cf.rightDown); break;
		case 2:DDA(cf.leftDown, cf.rightDown); DDA(cf.rightDown, cf.rightUp); break;
		case 3:DDA(cf.rightDown, cf.rightUp); DDA(cf.rightUp, cf.leftUp); break;
		default:break;
		}*/
	}

//	drawPolygon();
	

}



/*保存裁剪框*/
void saveCf() {
	if (cfBegin.x < cfEnd.x) {
		if (cfBegin.y < cfEnd.y) {
			cf->leftDown = cfBegin;
			cf->rightUp = cfEnd;
			cf->leftUp.x = cf->leftDown.x;
			cf->leftUp.y = cf->rightUp.y;
			cf->rightDown.x = cf->rightUp.x;
			cf->rightDown.y = cf->leftDown.y;
		}
		else {
			cf->leftUp = cfBegin;
			cf->rightDown = cfEnd;
			cf->leftDown.x = cf->leftUp.x;
			cf->leftDown.y = cf->rightDown.y;
			cf->rightUp.x = cf->rightDown.x;
			cf->rightUp.y = cf->leftUp.y;
		}
	}
	else {
		if (cfBegin.y < cfEnd.y) {
			cf->rightDown = cfBegin;
			cf->leftUp = cfEnd;
			cf->leftDown.x = cf->leftUp.x;
			cf->leftDown.y = cf->rightDown.y;
			cf->rightUp.x = cf->rightDown.x;
			cf->rightUp.y = cf->leftUp.y;
		}
		else {
			cf->rightUp = cfBegin;
			cf->leftDown = cfEnd;
			cf->leftUp.x = cf->leftDown.x;
			cf->leftUp.y = cf->rightUp.y;
			cf->rightDown.x = cf->rightUp.x;
			cf->rightDown.y = cf->leftDown.y;
		}
	}
}


void drawCf(int x, int y) {
	if (mouseLeftDownDraw) {
		cfEnd.x = x;
		cfEnd.y = winHeight - y;

		glColor3f(1.0, 1.0, 1.0);
		DDA(cf->leftUp, cf->leftDown);
		DDA(cf->leftDown, cf->rightDown);
		DDA(cf->rightDown, cf->rightUp);
		DDA(cf->rightUp, cf->leftUp);

		saveCf();

		glColor3f(0.0, 0.0, 0.0);
		DDA(cf->leftUp, cf->leftDown);
		DDA(cf->leftDown, cf->rightDown);
		DDA(cf->rightDown, cf->rightUp);
		DDA(cf->rightUp, cf->leftUp);


		glColor3f(1.0, 0.0, 0.0);
		for (int i = 1; i < polygon[index].point.size(); i++) {
			DDA(polygon[index].point[i - 1], polygon[index].point[i]);
		}
		DDA(polygon[index].point[polygon[index].point.size() - 1], polygon[index].point[0]);
		if (polygon[index].color != 'n') {
			fillArea(polygon[index].point, polygon[index].color);
		}
	}
	
}



static int encode(double x, double y){
	int code = 0;
	if (x<cfPoint[0].p.x)//xmin
		code += 1;
	if (x>cfPoint[2].p.x)//xmax
		code += 2;
	if (y<cfPoint[0].p.y)//ymin
		code += 4;
	if (y>cfPoint[2].p.y)//ymax
		code += 8;
	return code;
}
/*左边界裁剪*/
static void leftCut(){
	int i, code1, code2;
	double x1, x2, y1, y2, k;
	for (i = 0; i<number; i++)
	{
		x1 = points[i].p.x, y1 = points[i].p.y;
		x2 = points[(i + 1) % number].p.x, y2 = points[(i + 1) % number].p.y;
		k = (y1 - y2) / (x1 - x2);
		code1 = encode(x1, y1) & 1;
		code2 = encode(x2, y2) & 1;
		if (code1 == 0 && code2 == 0)//内内，保留第二个点
		{
			p1[p1n++] = points[(i + 1) % number];
		}
		else if (code1 == 0 && code2 == 1)//内外，保留交点
		{
			p1[p1n].p.y = y1 + k*(xmin - x1);
			p1[p1n].p.x = xmin;
			p1[p1n].code = encode(p1[p1n].p.x, p1[p1n].p.y);
			p1n++;
		}
		else if (code1 == 1 && code2 == 0)//外内，保留交点、第二个点
		{

			p1[p1n].p.y = y1 + k*(xmin - x1);
			p1[p1n].p.x = xmin;
			p1[p1n].code = encode(p1[p1n].p.x, p1[p1n].p.y);
			p1n++;
			p1[p1n++] = points[(i + 1) % number];
		}
	}
}

/*右边界裁剪*/
static void rightCut(){
	int i, code1, code2;
	double x1, x2, y1, y2, k;
	for (i = 0; i<p1n; i++)
	{
		x1 = p1[i].p.x, y1 = p1[i].p.y;
		x2 = p1[(i + 1) % p1n].p.x, y2 = p1[(i + 1) % p1n].p.y;
		k = (y1 - y2) / (x1 - x2);
		code1 = encode(x1, y1) & 2;
		code2 = encode(x2, y2) & 2;
		if (code1 == 0 && code2 == 0)//内内，保留第二个点
		{
			p2[p2n++] = p1[(i + 1) % p1n];
		}
		else if (code1 == 0 && code2 == 2)//内外，保留交点
		{
			p2[p2n].p.y = y1 + k*(xmax - x1);
			p2[p2n].p.x = xmax;
			p2[p2n].code = encode(p2[p2n].p.x, p2[p2n].p.y);
			p2n++;
		}
		else if (code1 == 2 && code2 == 0)//外内，保留交点、第二个点
		{
			p2[p2n].p.y = y1 + k*(xmax - x1);
			p2[p2n].p.x = xmax;
			p2[p2n].code = encode(p2[p2n].p.x, p2[p2n].p.y);
			p2n++;
			p2[p2n++] = p1[(i + 1) % p1n];
		}
	}
}

/*下边界裁剪*/
static void downCut(){
	int i, code1, code2;
	double x1, x2, y1, y2, k;
	for (i = 0; i<p2n; i++)
	{
		x1 = p2[i].p.x, y1 = p2[i].p.y;
		x2 = p2[(i + 1) % p2n].p.x, y2 = p2[(i + 1) % p2n].p.y;
		k = (y1 - y2) / (x1 - x2);
		code1 = encode(x1, y1) & 4;
		code2 = encode(x2, y2) & 4;
		if (code1 == 0 && code2 == 0)//内内，保留第二个点
		{
			p3[p3n++] = p2[(i + 1) % p2n];
		}
		else if (code1 == 0 && code2 == 4)//内外，保留交点
		{
			p3[p3n].p.x = (ymin - y1) / k + x1;
			p3[p3n].p.y = ymin;
			p3[p3n].code = encode(p3[p3n].p.x, p3[p3n].p.y);
			p3n++;
		}
		else if (code1 == 4 && code2 == 0)//外内，保留交点、第二个点
		{
			p3[p3n].p.x = (ymin - y1) / k + x1;
			p3[p3n].p.y = ymin;
			p3[p3n].code = encode(p3[p3n].p.x, p3[p3n].p.y);
			p3n++;
			p3[p3n++] = p2[(i + 1) % p2n];
		}
	}
}

//上边界裁剪
static void upCut(){
	int i, code1, code2;
	double x1, x2, y1, y2, k;
	p4n = 0;
	for (i = 0; i<p3n; i++)
	{
		x1 = p3[i].p.x, y1 = p3[i].p.y;
		x2 = p3[(i + 1) % p3n].p.x, y2 = p3[(i + 1) % p3n].p.y;
		k = (y1 - y2) / (x1 - x2);
		code1 = encode(x1, y1) & 8;
		code2 = encode(x2, y2) & 8;
		if (code1 == 0 && code2 == 0)//内内，保留第二个点
		{
			p4[p4n++] = p3[(i + 1) % p3n];
		}
		else if (code1 == 0 && code2 == 8)//内外，保留交点
		{
			p4[p4n].p.x = (ymax - y1) / k + x1;
			p4[p4n].p.y = ymax;
			p4[p4n].code = encode(p4[p4n].p.x, p4[p4n].p.y);
			p4n++;
		}
		else if (code1 == 8 && code2 == 0)//外内，保留交点、第二个点
		{
			p4[p4n].p.x = (ymax - y1) / k + x1;
			p4[p4n].p.y = ymax;
			p4[p4n].code = encode(p4[p4n].p.x, p4[p4n].p.y);
			p4n++;
			p4[p4n++] = p3[(i + 1) % p3n];
		}
	}
}

/*裁剪算法*/
static void Sutherland_Hodgman(){
//	cout << "here" << endl;

	cfPoint[0].p = cf->leftDown;
	cfPoint[1].p = cf->rightDown;
	cfPoint[2].p = cf->rightUp;
	cfPoint[3].p = cf->leftUp;
	xmin = cfPoint[0].p.x;
	ymin = cfPoint[0].p.y;
	xmax = cfPoint[2].p.x;
	ymax = cfPoint[2].p.y;


	leftCut();
	rightCut();
	downCut();
	upCut();

	/*绘制裁剪后的图形*/
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 1; i < polygon[index].point.size(); i++) {
		DDA(polygon[index].point[i - 1], polygon[index].point[i]);
	}
	DDA(polygon[index].point[polygon[index].point.size() - 1], polygon[index].point[0]);

	glColor3f(1.0, 1.0, 1.0);
	DDA(cf->leftUp, cf->leftDown);
	DDA(cf->leftDown, cf->rightDown);
	DDA(cf->rightDown, cf->rightUp);
	DDA(cf->rightUp, cf->leftUp);

	if (polygon[index].color != 'n') {
		fillArea(polygon[index].point, 'w');
	}

	polygonPt p;
	p.color = polygon[index].color;
	polygon.pop_back();
	for (int i = 0; i < p4n; i++) {
		scrPt t;
		t = p4[i].p;
		p.point.push_back(t);
	}
	polygon.push_back(p);
	if (polygon[index].color != 'n') {
		fillArea(polygon[index].point, polygon[index].color);
	}

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < p4n; i++)
		glVertex2f(p4[i].p.x, p4[i].p.y);
	glEnd();
	glFlush();

	
	
}




/*键盘回调函数，完成裁剪*/
static void finishDraw(unsigned char key, int x, int y) {
	switch (key) {
	case 13: {
		endPtctr = 2;
		/*裁剪*/
		Sutherland_Hodgman();		
		break;
	}
	}
}


void cutPolygon(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && endPtctr == 0) {
		if (action == GLUT_DOWN) {
			cfBegin.x = xMouse;
			cfBegin.y = winHeight - yMouse;
			mouseLeftDownDraw = true;
		}
		if (action == GLUT_UP) {
	//		cfEnd.x = xMouse;
	//		cfEnd.y = winHeight - yMouse;
			mouseLeftDownDraw = false;
	//		saveCf();

			

			endPtctr = 1;
			
		}
		glutMotionFunc(drawCf);
		glColor3f(0.0, 0.0, 0.0);
		DDA(cf->leftUp, cf->leftDown);
		DDA(cf->leftDown, cf->rightDown);
		DDA(cf->rightDown, cf->rightUp);
		DDA(cf->rightUp, cf->leftUp);
//		glutKeyboardFunc(finishDraw);
	}
	else if (button == GLUT_LEFT_BUTTON && endPtctr == 1) {
		if (action == GLUT_DOWN) {
			click.x = xMouse;
			click.y = winHeight - yMouse;
			pointIndex = judgePoint(click);
			mouseLeftDownEdit = true;
		}
		if (action == GLUT_UP) {
			mouseLeftDownEdit = false;
		//	glutKeyboardFunc(finishDraw);
			
			
		}
		glutMotionFunc(editCf);
		glColor3f(0.0, 0.0, 0.0);
		DDA(cf->leftUp, cf->leftDown);
		DDA(cf->leftDown, cf->rightDown);
		DDA(cf->rightDown, cf->rightUp);
		DDA(cf->rightUp, cf->leftUp);
		
	}
	glutKeyboardFunc(finishDraw);
	if (endPtctr != 2) {
		glColor3f(1.0, 0.0, 0.0);
		for (int i = 1; i < polygon[index].point.size(); i++) {
			DDA(polygon[index].point[i - 1], polygon[index].point[i]);
		}
		DDA(polygon[index].point[polygon[index].point.size() - 1], polygon[index].point[0]);
	//	if (polygon[index].color != 'n') {
//			fillArea(polygon[index].point, polygon[index].color);
//		}
	}
}