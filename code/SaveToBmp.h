#ifndef _SAVETOBMP_H_
#define _SAVETOBMP_H_

#include "Control.h"
#include <fstream>
using namespace std;

/*����Ļ��ȡ����*/
extern bool screenshot(const char* filename);
/*д���ļ�������bmpͼƬ*/
extern bool writeBMP(const char filename[], unsigned char* data, unsigned int w, unsigned int h);

#endif