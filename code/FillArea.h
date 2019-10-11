#ifndef _FILLAREA_H_
#define _FILLAREA_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <list>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<functional>
using namespace std;
#include "Control.h"
#include "DrawPolygon.h"
/*�ߵ����ݽṹ*/
typedef struct tagEDGE {
	double xi;
	double dx;
	double ymax;
}EDGE;

/*��ʼ��һЩ����*/
extern void initFillArea();
/*������ε��㷨*/
extern void fillArea(vector<scrPt> point, char key);
/*��ȡ����ζ�����Сֵ*/
extern int getPolygonMin(vector<scrPt> point);
/*��ȡ����ζ�����Сֵ*/
extern int getPolygonMax(vector<scrPt> point);
/*��ʼ���±߱�*/
extern void initScanlineNewEdgeTable(vector<scrPt> point);
/*���ˮƽ��*/
extern void horizontalEdgeFill(vector<scrPt> point);
/*�ȽϺ���*/
extern bool EdgeXiComparator(EDGE&e1, EDGE&e2);
/*��ɨ���߶�Ӧ�������±߲��뵽aet��*/
extern void insertNetlistToAet(int y);
/*ִ�о������䶯��*/
extern void fillAetScanline(int y);
/*�жϻ��*/
extern bool isEdgeOutOfActive(EDGE e, int y);
/*ɾ���ǻ��*/
extern void removeNonactiveedgeFromAet(int y);
/*���»�߱���ÿ���xiֵ��������xi��������*/
extern void updateAndResortAet();
/*��ÿ��ɨ���߽��д���*/
extern void processScanlineFill();
//extern void scanLinePolygonFill();
/*ѡ�����ε������ɫ*/
extern void chooseColor(unsigned char key, int x, int y);

#endif