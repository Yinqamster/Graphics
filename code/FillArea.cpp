#include "FillArea.h"
#include "DrawLine.h"

static int po = -1;
static int number = -1;
static int ymin;
static int ymax;
static int countN;
static list<EDGE>aet;
static vector<list<EDGE>>slNet(600);

int getPolygonMin(vector<scrPt> point) {
//	cout << po << endl;
/*	double ymin = 0;
	if (po != -1 && number != -1) {
		ymin = polygon[po].point[0].y;
		for (int i = 1; i < number; i++) {
			if (polygon[po].point[i].y < ymin)
				ymin = polygon[po].point[i].y;
		}
	}*/

	int ymin = 0;
	ymin = point[0].y;
	for (int i = 1; i < number; i++) {
		if (point[i].y < ymin)
			ymin = point[i].y;
	}

	return ymin;
}

int getPolygonMax(vector<scrPt> point) {
/*	double ymax = 0;
	if (po != -1 && number != -1) {
		ymax = polygon[po].point[0].y;
		for (int i = 1; i < number; i++) {
			if (polygon[po].point[i].y > ymax)
				ymax = polygon[po].point[i].y;
		}
	}*/


	int ymax = 0;
	ymax = point[0].y;
	for (int i = 1; i < number; i++) {
		if (point[i].y > ymax)
			ymax = point[i].y;
	}
	return ymax;
}

//point polygon[10];


void initScanlineNewEdgeTable(vector<scrPt> point) {
	EDGE e;
	for (int i = 0; i < number; i++) {
		scrPt ps = point[i];
		scrPt pe = point[(i + 1) % number];
		scrPt pss = point[(i - 1 + number) % number];
		scrPt pee = point[(i + 2) % number];
		if (pe.y != ps.y) {
			e.dx = double(pe.x - ps.x) / double(pe.y - ps.y);
			if (pe.y>ps.y) {
				e.xi = ps.x;
				if (pee.y >= pe.y) {
					e.ymax = pe.y - 1;
	///				cout << "1!!" << endl;
				}
				else
					e.ymax = pe.y;
				slNet[ps.y - ymin].push_front(e);
			}
			else {
				e.xi = pe.x;
				if (pss.y >= ps.y) {
					e.ymax = ps.y - 1;
	///				cout << "2!!" << endl;
				}
				else
					e.ymax = ps.y;
				slNet[pe.y - ymin].push_front(e);
			}
		}
	}
}

void initFillArea() {
	///	po = -1;
	///	number = -1;
///	cout << aet.size() << " " << slNet[0].empty() << endl;

/*	aet.clear();
	for (int i = 0; i < 600; i++) {
		slNet[i].clear();
	}*/

///	cout << "here1" << endl;
	endPtctr = 0;
	if (!polygon.empty()) {
		
		po = polygon.size() - 1;
///		cout << "1 " << po << endl;
		if (!polygon[po].point.empty()) {
			number = polygon[po].point.size();
///			cout << "2 " << number << endl;
		}
	//	ymin = getPolygonMin();
///		cout << ymin << endl;
	//	ymax = getPolygonMax();
///		cout << ymax << endl;
	}
	else {
		cout << "无可填充图形！" << endl;
		endPtctr = 1;
	}

	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glColor3f(0.0, 1.0, 0.0);

	
}

void horizontalEdgeFill(vector<scrPt> point) {
	for (int i = 0; i < number - 1; i++) {
		scrPt ps = point[i];
		scrPt pe = point[(i + 1)];
		if (pe.y == ps.y) {
/*			glBegin(GL_LINES);
			glVertex2f(pe.x, pe.y);
			glVertex2f(ps.x, ps.y);
			glEnd();*/
			DDA(ps, pe);
		}
	}
}

bool EdgeXiComparator(EDGE&e1, EDGE&e2) {
	return (e1.xi < e2.xi);
}

void insertNetlistToAet(int y) {
	for (list<EDGE>::iterator it = slNet[y - ymin].begin(); it != slNet[y - ymin].end(); it++) {
		list<EDGE>::iterator it2 = it;
		aet.push_back(*it2);
	}
	aet.sort(EdgeXiComparator);
}
void fillAetScanline(int y) {
	scrPt p1, p2;
	for (list<EDGE>::iterator it1 = aet.begin(); it1 != aet.end(); it1++, it1++) {
		list<EDGE>::iterator it2 = it1;
		++it2;
		if (it2 != aet.end()) {
			glBegin(GL_LINES);
			glVertex2f((*it1).xi, y);
			glVertex2f((*it2).xi, y);
			glEnd();
	/*		p1.x = (*it1).xi;
			p1.y = y;
			p2.x = (*it2).xi;
			p2.y = y;
			DDA(p1, p2);*/

		}
	}
}
bool isEdgeOutOfActive(EDGE e, int y) {
	return (e.ymax == y);
}
void removeNonactiveedgeFromAet(int y) {
	aet.remove_if(bind2nd(ptr_fun(isEdgeOutOfActive), y));
}
void updateAetEdgeInfo(EDGE&e) {
	e.xi += e.dx;
}
void updateAndResortAet() {
	for_each(aet.begin(), aet.end(), updateAetEdgeInfo);
	aet.sort(EdgeXiComparator);
}


void processScanlineFill() {
///	cout <<"ymin: "<< ymin << " " <<"ymax: " << ymax << endl;
	for (int y = ymin; y <= ymax; y++) {
///		cout << "y: " << y << endl;
		insertNetlistToAet(y);
		fillAetScanline(y);
		removeNonactiveedgeFromAet(y);
		updateAndResortAet();
///		countN++;
///		cout << countN << endl;
	}
}

/*
void scanLinePolygonFill() {
	initScanlineNewEdgeTable();
}
*/

void chooseColor(unsigned char key, int x, int y) {
/*	if (key == 'r') {
		glColor3f(1.0, 0.0, 0.0);
	}
	else if (key == 'g') {
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (key == 'b') {
		glColor3f(0.0, 0.0, 1.0);
	}
	else if (key == 'y') {
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (key == 'w') {
		glColor3f(0.0, 0.0, 0.0);
	}
	else if (key == 'c') {
		glColor3f(0.0, 1.0, 1.0);
	}
	else if (key == 'p') {
		glColor3f(1.0, 0.0, 1.0);
	}*/
	
	countN = 0;
	if (endPtctr == 0) {
		//将颜色设置成已涂颜色
		polygon[po].color = key;

		fillArea(polygon[po].point, key);
	}

}

void fillArea(vector<scrPt> point, char key) {
/*	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		glColor3f(0.0, 1.0, 0.0);
	if (button == GLUT_MIDDLE_BUTTON && action == GLUT_DOWN) {
		cout << "clearOK" << endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		endPtctr = 0;
	}*/
//	glutKeyboardFunc(chooseColor);

	for (int i = 0; i < point.size(); i++) {
//		cout << point[i].x << "~" << point[i].y << endl;
		point[i].x = (int)point[i].x;
		point[i].y = (int)point[i].y;
	}
/*	for (int i = 0; i < point.size(); i++) {
		cout << point[i].x << "~" << point[i].y << endl;
	}*/

	if (key == 'r') {
		glColor3f(1.0, 0.0, 0.0);
	}
	else if (key == 'g') {
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (key == 'b') {
		glColor3f(0.0, 0.0, 1.0);
	}
	else if (key == 'y') {
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (key == 'c') {
		glColor3f(0.0, 1.0, 1.0);
	}
	else if (key == 'p') {
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (key == 'w') {
		glColor3f(1.0, 1.0, 1.0);
	}
	else {
		endPtctr = 1;
		cout << "输入错误" << endl;
		return;
	}

	aet.clear();
	for (int i = 0; i < 600; i++) {
		slNet[i].clear();
	}
	number = point.size();
	ymin = getPolygonMin(point);
///			cout << ymin << endl;
	ymax = getPolygonMax(point);
///			cout << ymax << endl;

	initScanlineNewEdgeTable(point);
	horizontalEdgeFill(point);
	processScanlineFill();
	glFlush();
}
