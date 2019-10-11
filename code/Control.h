#ifndef _Control_H_
#define _Control_H_

#include <windows.h>
#include <GL/glut.h>

extern GLsizei winWidth;
extern GLsizei winHeight;
extern GLint endPtctr;

extern int lastEdit;

class scrPt {
public:
	double x, y;
};

#endif
