#ifndef _SAVETOBMP_H_
#define _SAVETOBMP_H_

#include "Control.h"
#include <fstream>
using namespace std;

/*从屏幕读取数据*/
extern bool screenshot(const char* filename);
/*写入文件，生成bmp图片*/
extern bool writeBMP(const char filename[], unsigned char* data, unsigned int w, unsigned int h);

#endif