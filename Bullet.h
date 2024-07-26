#pragma once
#include <string>
#include "Transparent.h"
#include "Object.h"
#include "Constant.h"
#include "ZombiesLayer.h"

class Bullet :public Object {
public:
	bool is_end = false;

public:
	Bullet(std::string bullet_type, int damage, int row, int col, int x, int y, int size)
		:type(bullet_type), damage(damage), row(row), col(col), Object(x, y, size, size) {
		std::string path = "pic\\bullet\\" + type + ".png";
		loadimage(&img, path.c_str(), size, size);
	}

	bool Detect(ZombiesLayer &zombies_layer) {
		int num = zombies_layer.zombies_list.size();
		for (int i = 0; i < num; i++) {
			Zombie* temp = zombies_layer.zombies_list[i];
			if (row == temp->row && is_collision(*temp)) {
				is_end = true;	
				temp->DecreaseHP(damage);
			}
		}
		return true;
	}

	void Move() {
		x += BULLET_SPEED;
	}

	void Blast() {

	}

	void Draw() {
		putimage_t(x, y, &img);
	}

	void Update(ZombiesLayer& zombies_layer) {
		if (x >= WINDOW_WIDTH) {
			is_end = true;
		}
		else if (Detect(zombies_layer)) {
			Blast();
			
		}
	}

private:
	std::string type;
	int row, col;
	int damage;
	IMAGE img;
};