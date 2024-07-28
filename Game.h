#pragma once
#include <iostream>
#include <vector>
#include <string.h>
#include "Sunflower.h"
#include "Peashooter.h"
#include "ZombiesLayer.h"


class Game {
public:
	char plants_layer[8][8];
	char zombies_layer[8][8];
	std::vector<Sunflower*> sunflower_list;
	std::vector<Peashooter*> peashooter_list;
	IMAGE background;
	bool running = true;
	bool is_game_start = false;

public:
	Game() {
		loadimage(&background, "pic\\background\\background.png", WINDOW_WIDTH, WINDOW_HEIGHT);
		memset(plants_layer, '-', sizeof(plants_layer));
		memset(zombies_layer, '-', sizeof(zombies_layer));
	}

	~Game() {}

	void AddObject(const int &id, int row, int col, int x, int y) {
		Sunflower* new_sunflower;
		Peashooter* new_peashooter;
		switch (id) {
		case SUNFLOWER:
			new_sunflower = new Sunflower(row, col, x, y);
			sunflower_list.push_back(new_sunflower);
			break;
		case PEASHOOTER:
			new_peashooter = new Peashooter(row, col, x, y);
			peashooter_list.push_back(new_peashooter);
			break;
		}
	}

	void Draw(SunlightLayer& sunlight_layer, BulletLayer& bullet_layer, ZombiesLayer& zombies_layer) {
		putimage(0, 0, &background);
		for (int i = 0; i < sunflower_list.size(); i++) {
			sunflower_list[i]->Draw(sunlight_layer, TIME_INTERVAL);
		}
		for (int i = 0; i < peashooter_list.size(); i++) {
			peashooter_list[i]->Draw(bullet_layer, TIME_INTERVAL);
		}
	}

	void Update(ZombiesLayer& zombies_layer) {
		if (zombies_layer.is_game_end) {
			running = false;
			return;
		}

		for (int i = 0; i < sunflower_list.size(); i++) {
			Sunflower* temp = sunflower_list[i];
			temp->Detect(zombies_layer);
			if (temp->is_end) {
				std::swap(sunflower_list[i], sunflower_list.back());
				sunflower_list.pop_back();
				delete temp;
				continue;
			}
		}
		for (int i = 0; i < peashooter_list.size(); i++) {
			Peashooter* temp = peashooter_list[i];
			temp->Detect(zombies_layer);
			if (temp->is_end) {
				std::swap(peashooter_list[i], peashooter_list.back());
				peashooter_list.pop_back();
				delete temp;
				continue;
			}
		}

	}
};