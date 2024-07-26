#pragma once
#include <string>
#include "Object.h"
#include "Constant.h"
#include "Zombies.h"

class Plant :public Object {
public:
	bool is_end = false;
	int row, col;

public:
	Plant(std::string name, int hp, int row, int col, int x, int y, int width = PLANT_SIZE, int height = PLANT_SIZE)
		:plant_name(name), plant_hp(hp), row(row), col(col), Object(x, y, width, height){}
	
	void DecreaseHP(int damage, Zombie &zombie) {
		plant_hp -= damage;
		if (plant_hp <= 0) {
			is_end = true;
			zombie.status = Zombie::Status::WALK;
		}
	}

protected:
	std::string plant_name;
	int plant_hp;
};