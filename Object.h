#pragma once

#include "graphics.h"

class Object {
public:
	int x, y, width, height;
	int edge;

	Object(int x, int y, int width, int height, int edge = 0)
		:x(x), y(y), width(width), height(height), edge(edge) {}

	bool is_collision(const Object& obj) {
		return !(x + width < obj.x + obj.edge || y + height < obj.y || obj.x + obj.width - obj.edge < x || obj.y + obj.height < y);
	}

	bool is_click(int xx, int yy) {
		return xx > x && xx < x + width && yy > y && yy < y + height;
	}

};