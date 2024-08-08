#pragma once
#include <vector>
#include <string.h>
#include "Sunflower.h"
#include "Peashooter.h"
#include "ZombiesLayer.h"
#include "SunlightLayer.h"

extern SunlightLayer sunlight_layer;
extern BulletLayer bullet_layer;

class PlantsLayer {
public:
	int map[8][8];
	std::vector<Sunflower*> sunflower_list;
	std::vector<Peashooter*> peashooter_list;

public:
	PlantsLayer() {
		memset(map, 0, sizeof(map));
	}

	void AddObject(const int& id, int row, int col, int x, int y) {
		Sunflower* new_sunflower;
		Peashooter* new_peashooter;
		switch (id) {
		case SUNFLOWER_ID:
			new_sunflower = new Sunflower(row, col, x, y);
			sunflower_list.push_back(new_sunflower);
			break;
		case PEASHOOTER_ID:
			new_peashooter = new Peashooter(row, col, x, y);
			peashooter_list.push_back(new_peashooter);
			break;
		}
	}

	void Draw() {
		for (int i = 0; i < sunflower_list.size(); i++) {
			sunflower_list[i]->Draw(TIME_INTERVAL);
		}
		for (int i = 0; i < peashooter_list.size(); i++) {
			peashooter_list[i]->Draw(bullet_layer, TIME_INTERVAL);
		}
	}

	void Update(ZombiesLayer& zombies_layer, int delta_time) {
		for (int i = 0; i < sunflower_list.size(); i++) {
			Sunflower* temp = sunflower_list[i];
			temp->Detect(zombies_layer);
			temp->Update(sunlight_layer, delta_time);
			if (temp->is_end) {
				map[temp->row][temp->col] = 0;
				std::swap(sunflower_list[i], sunflower_list.back());
				sunflower_list.pop_back();
				delete temp;
				continue;
			}
		}
		for (int i = 0; i < peashooter_list.size(); i++) {
			Peashooter* temp = peashooter_list[i];
			temp->Detect(zombies_layer);
			temp->Update(bullet_layer, delta_time);
			if (temp->is_end) {
				map[temp->row][temp->col] = 0;
				std::swap(peashooter_list[i], peashooter_list.back());
				peashooter_list.pop_back();
				delete temp;
				continue;
			}
		}

	}

	void reset() {
		memset(map, 0, sizeof(map));

		while (sunflower_list.size() > 0) {
			Sunflower* temp = sunflower_list[sunflower_list.size() - 1];
			sunflower_list.pop_back();
			delete temp;
		}

		while (peashooter_list.size() > 0) {
			Peashooter* temp = peashooter_list[peashooter_list.size() - 1];
			peashooter_list.pop_back();
			delete temp;
		}

	}
};