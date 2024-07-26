#pragma once
#include <deque>
#include <vector>
#include "Constant.h"
#include "Animation.h"
#include "Plants.h"
#include "BulletLayer.h"

class Peashooter :public Plant {
public:
	Peashooter(int row, int col, int x, int y)
		:idle("pic\\plants\\peashooter\\idle", PLANT_SIZE, 3, PLANT_FRAME_INTERVAL),
		shoot("pic\\plants\\peashooter\\shoot", PLANT_SIZE, 3, PLANT_FRAME_INTERVAL),
		Plant("peashooter", PEASHOOTER_HP, row, col, x, y) {
		attack_interval = PLANT_FRAME_INTERVAL * 3;
	}

	void Detect(ZombiesLayer &zombies_layer) {
		int num = zombies_layer.zombies_list.size();
		for (int i = 0; i < num; i++) {
			Zombie* temp = zombies_layer.zombies_list[i];
			if (row == temp->row) {
				status = Status::SHOOT;	
				if (is_collision(*temp)) {
					temp->status = Zombie::Status::ATTACK;
					DecreaseHP(temp->damage, *temp);
				}
				return;
			}
		}
		status = Status::IDLE;
	}

	void AddBullet(BulletLayer &bullet_layer) {
		Bullet* new_bullet = new Bullet("pea", PEA_DAMAGE, row, col, x + PLANT_SIZE, y + PLANT_SIZE / 4, PEA_SIZE);
		bullet_layer.bullet_list.push_back(new_bullet);
	}

	void Shoot(BulletLayer &bullet_layer, int delta_time) {
		timer += delta_time;
		if (timer >= attack_interval) {
			AddBullet(bullet_layer);
			timer = 0;
		}
	}

	void Draw(BulletLayer& bullet_layer, int delta_time) {
		switch (status) {
		case Status::IDLE:
			idle.Play(x, y, delta_time);
			break;
		case Status::SHOOT:
			shoot.Play(x, y, delta_time);
			Shoot(bullet_layer, delta_time);
			break;
		default:
			break;
		}
	}

protected:
	enum Status { IDLE, SHOOT };

protected:
	Animation idle, shoot;
	int timer = 0;
	int attack_interval;
	Status status = Status::IDLE;
};