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
/*边的数据结构*/
typedef struct tagEDGE {
	double xi;
	double dx;
	double ymax;
}EDGE;

/*初始化一些变量*/
extern void initFillArea();
/*填充多边形的算法*/
extern void fillArea(vector<scrPt> point, char key);
/*获取多边形顶点最小值*/
extern int getPolygonMin(vector<scrPt> point);
/*获取多边形顶点最小值*/
extern int getPolygonMax(vector<scrPt> point);
/*初始化新边表*/
extern void initScanlineNewEdgeTable(vector<scrPt> point);
/*填充水平边*/
extern void horizontalEdgeFill(vector<scrPt> point);
/*比较函数*/
extern bool EdgeXiComparator(EDGE&e1, EDGE&e2);
/*将扫描线对应的所有新边插入到aet中*/
extern void insertNetlistToAet(int y);
/*执行具体的填充动作*/
extern void fillAetScanline(int y);
/*判断活动边*/
extern bool isEdgeOutOfActive(EDGE e, int y);
/*删除非活动边*/
extern void removeNonactiveedgeFromAet(int y);
/*更新活动边表中每项的xi值，并根据xi重新排序*/
extern void updateAndResortAet();
/*对每条扫描线进行处理*/
extern void processScanlineFill();
//extern void scanLinePolygonFill();
/*选择多边形的填充颜色*/
extern void chooseColor(unsigned char key, int x, int y);

#endif