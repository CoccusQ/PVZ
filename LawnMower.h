#pragma once
#include "Object.h"
#include "Transparent.h"
#include "Constant.h"
#include "ZombiesLayer.h"

extern ZombiesLayer zombies_layer;
extern IMAGE img_lawn_mower;

class LawnMower :public Object {
public:
	bool is_trigger = false;
	bool is_end = false;

public:
	LawnMower(int row, int col, int x, int y, int size)
		:row(row), col(col), Object(x, y, size, size, 10) {
		img = &img_lawn_mower;
	}

	void Detect() {
		int num = zombies_layer.zombies_list.size();
		for (int i = 0; i < num; i++) {
			Zombie* temp = zombies_layer.zombies_list[i];
			if (row == temp->row && temp->status != Zombie::Status::DIE && is_collision(*temp)) {
				is_trigger = true;
			}
		}
	}

	void Clear() {
		int num = zombies_layer.zombies_list.size();
		for (int i = 0; i < num; i++) {
			Zombie* temp = zombies_layer.zombies_list[i];
			if (row == temp->row && temp->status != Zombie::Status::DIE && is_collision(*temp)) {
				temp->status = Zombie::Status::DIE;
			}
		}
	}

	void Move() {
		x += LAWN_MOWER_SPEED;
	}

	void Draw() {
		putimage_t(x, y, img);
	}

	void Update() {
		if (is_trigger) {
			Move();
			Clear();
		}
		else {
			Detect();
		}
		if (x >= WINDOW_WIDTH) {
			is_end = true;
		}
	}

private:
	IMAGE* img;
	int row, col;
};