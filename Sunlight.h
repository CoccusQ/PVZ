#pragma once
#include <string>
#include <cmath>
#include "Transparent.h"
#include "Object.h"
#include "Constant.h"

class Sunlight :public Object {
public:
	bool is_end = false;
	//bool is_picked = false;
	int value;
public:
	Sunlight(int value, int row, int col, int x, int y, int size = SUNLIGHT_SIZE)
		:value(value), row(row), col(col), Object(x, y, size, size) {
		std::string path = "pic\\sunlight\\sunlight.png";
		loadimage(&img, path.c_str(), size, size);
	}

	void Move() {
		double dx = x - SUNLIGHT_X;
		double dy = y - SUNLIGHT_Y;
		double angel = atan(dx / dy);
		double v_x = SUNLIGHT_SPEED * sin(angel);
		double v_y = SUNLIGHT_SPEED * cos(angel);
		if (!is_end) {
			x -= v_x;
			y -= v_y;
		}
		if (x >= SUNLIGHT_X - SUNLIGHT_RANGE
			&& x <= SUNLIGHT_X + SUNLIGHT_RANGE
			&& y >= SUNLIGHT_Y - SUNLIGHT_RANGE
			&& y <= SUNLIGHT_Y + SUNLIGHT_RANGE) {
			is_end = true;
		}
	}

	void Draw() {
		putimage_t(x, y, &img);
	}

private:
	int row, col;
	IMAGE img;
};