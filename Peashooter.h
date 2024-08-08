#pragma once
#include <deque>
#include <vector>
#include "Animation.h"
#include "Plants.h"
#include "BulletLayer.h"

extern Atlas atlas_peashooter_idle;
extern Atlas atlas_peashooter_shoot;

class Peashooter :public Plant {
public:
	Peashooter(int row, int col, int x, int y)
		:idle(&atlas_peashooter_idle, PLANT_FRAME_INTERVAL),
		shoot(&atlas_peashooter_shoot, PLANT_FRAME_INTERVAL),
		Plant("peashooter", PEASHOOTER_HP, row, col, x, y) {
		attack_interval = PLANT_FRAME_INTERVAL * 3;
	}

	void Detect(ZombiesLayer &zombies_layer) {
		int num = zombies_layer.zombies_list.size();
		for (int i = 0; i < num; i++) {
			Zombie* temp = zombies_layer.zombies_list[i];
			if (temp->status != Zombie::Status::DIE && row == temp->row) {
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
		Bullet* new_bullet = new Bullet(PEA_ID, PEA_DAMAGE, row, col, x + PLANT_SIZE, y + PLANT_SIZE / 4, PEA_SIZE);
		bullet_layer.bullet_list.push_back(new_bullet);
	}

	
	void Shoot(BulletLayer &bullet_layer, int delta_time) {
		timer += delta_time;
		if (timer >= attack_interval) {
			AddBullet(bullet_layer);
			timer = 0;
		}
	}
	
	void Update(BulletLayer& bullet_layer, int delta_time) {
		
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

	void Draw(BulletLayer& bullet_layer, int delta_time) {
		switch (status) {
		case Status::IDLE:
			idle.Draw(x, y);
			break;
		case Status::SHOOT:
			shoot.Draw(x, y);
			//Shoot(bullet_layer, delta_time);
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