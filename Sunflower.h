#pragma once
#include <deque>
#include "Animation.h"
#include "Plants.h"
#include "Sunlight.h"
#include "SunlightLayer.h"
#include "ZombiesLayer.h"

extern Atlas atlas_sunflower_idle;
extern Atlas atlas_sunflower_produce;

class Sunflower :public Plant {
public:
	Sunflower(int row, int col, int x, int y)
		:idle(&atlas_sunflower_idle, PLANT_FRAME_INTERVAL),
		produce(&atlas_sunflower_produce, PLANT_FRAME_INTERVAL),
		Plant("sunflower", SUNFLOWER_HP, row, col, x, y) {
		produce_interval = PLANT_FRAME_INTERVAL * 30;
		produce.set_loop(false);
	}

	void Detect(ZombiesLayer& zombies_layer) {
		int num = zombies_layer.zombies_list.size();
		for (int i = 0; i < num; i++) {
			Zombie* temp = zombies_layer.zombies_list[i];
			if (row == temp->row) {
				if (is_collision(*temp)) {
					temp->status = Zombie::Status::ATTACK;
					DecreaseHP(temp->damage, *temp);
				}
				return;
			}
		}
	}

	void AddSunlight(SunlightLayer &sunlight_layer) {
		Sunlight* new_sunlight = new Sunlight(SUNLIGHT_VALUE_NORM, row, col, x + (PLANT_SIZE - SUNLIGHT_SIZE) / 2, y);
		sunlight_layer.sunlight_list.push_back(new_sunlight);
	}

	void Update(SunlightLayer &sunlight_layer, int delta_time) {
		switch (status) {
		case Status::PRODUCE:
			produce.Play(x, y, delta_time);
			if (produce.is_finished) {
				AddSunlight(sunlight_layer);
				status = Status::IDLE;
			}
			break;
		case Status::IDLE:
			idle.Play(x, y, delta_time);
			timer += delta_time;
			if (timer >= produce_interval) {
				status = Status::PRODUCE;
				timer = 0;
				produce.reset();
			}
			break;
		}
	}

	void Draw(int delta_time) {
		switch (status) {
		case Status::IDLE:
			idle.Draw(x, y);
			break;
		case Status::PRODUCE:
			produce.Draw(x, y);
			break;
		default:
			break;
		}
	}

protected:
	enum Status { IDLE, PRODUCE };

protected:
	Animation idle, produce;
	int timer = 0;
	int produce_interval;
	Status status = Status::IDLE;
};