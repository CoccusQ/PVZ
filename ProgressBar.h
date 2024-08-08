#pragma once
#include <string>
#include "Object.h"
#include "Transparent.h"

class ProgressBar :public Object {
public:
	IMAGE* img;
	//double progress = 0;
public:
	ProgressBar() {};

	ProgressBar(std::string type, int x, int y, int width, int height)
		:Object(x, y, width, height) {
		std::string path = "pic\\progressbar\\" + type + ".png";
		loadimage(img, path.c_str(), width, height);
	}

	void set_size(int x, int y, int width, int height) {
		this->set_x(x);
		this->set_y(y);
		this->set_width(width);
		this->set_height(height);
	}

	void set_img(IMAGE* image) {
		this->img = image;
	}

	void Draw(double progress) {
		setbkmode(TRANSPARENT);
		setfillcolor(RGB(181, 242, 94));
		setlinecolor(RGB(181, 242, 94));
		int w = progress * (width - 15 * 1.5);
		int bar_x = x + (1 - progress) * (width - 15 * 1.5);
		int h = height / 3;
		int bar_y = y + height / 3;
		fillrectangle(bar_x, bar_y, bar_x + w, bar_y + h);
		putimage_t(x, y, img);
	}
};