#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
#pragma comment( lib, "MSIMG32.LIB")

void putimage_t(int x, int y, IMAGE* srcimg, IMAGE* dstimg = NULL) //ÐÂ°æpng
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

/*
void outtext_shadow(COLORREF color, std::string str, int left, int top, int right, int bottom) {
	setbkmode(TRANSPARENT);
	RECT r = { left, top, right, bottom };
	RECT r_shadow = { left + 2, top + 2, right + 2, bottom + 2 };
	settextcolor(LIGHTGRAY);
	drawtext(str.c_str(), &r_shadow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextcolor(color);
	drawtext(str.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
}
*/