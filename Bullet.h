#pragma once
#include <string>
#include "Transparent.h"
#include "Object.h"
#include "Constant.h"
#include "ZombiesLayer.h"
#include "Animation.h"

extern ZombiesLayer zombies_layer;
extern IMAGE img_bullet_pea;
extern Atlas atlas_pea;

class Bullet :public Object {
public:
	bool is_end = false;
	bool is_hit = false;

public:
	Bullet(int bullet_type, int damage, int row, int col, int x, int y, int size)
		:type(bullet_type), damage(damage), row(row), col(col), Object(x, y, size, size) {
		switch (type) {
		case PEA_ID:
			img = &img_bullet_pea;
			blast.set_atlas(&atlas_pea);
			blast.set_interval(80);
			blast.set_loop(false);
			break;
		}
	}

	void Detect() {
		int num = zombies_layer.zombies_list.size();
		for (int i = 0; i < num; i++) {
			Zombie* temp = zombies_layer.zombies_list[i];
			if (row == temp->row && is_collision(*temp)) {
				is_hit = true;
				temp->DecreaseHP(damage);
				//std::cout << "decrease hp\n";
			}
		}
	}

	void Move() {
		x += is_hit ? 0 : BULLET_SPEED;
	}

	void Draw() {
		if (is_hit) {
			blast.Play(x, y, TIME_INTERVAL);
		}
		else {
			putimage_t(x, y, img);
		}
	}

	void Update() {
		if(!is_hit) Detect();
		Move();
		if (x >= WINDOW_WIDTH) {
			is_end = true;
		}
		if (is_hit && blast.is_finished) {
			is_end = true;
			is_hit = false;
		}
	}

private:
	int type;
	int row, col;
	int damage;
	IMAGE* img;
	Animation blast;
};