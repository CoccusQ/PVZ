#pragma once
#include <vector>
#include <string.h>
#include "Zombies.h"
#include "ProgressBar.h"

class ZombiesLayer {
public:
	std::vector<Zombie*> zombies_list;
	ProgressBar progress_bar;
	int ratio;
	bool is_game_end = false;
public:
	ZombiesLayer(std::string game_level_type = "1flag", int total_wave = 10, int ratio = 1, int interval = ZOMBIE_EMERGE_INTERVAL)
		:total_wave(total_wave), ratio(ratio), interval(interval),
		progress_bar(game_level_type, PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT) {

	}

	void NewZombie() {
		int new_row = rand() % 8;
		int new_x = WINDOW_WIDTH - ZOMBIE_SIZE / 2;
		int new_y = MAP_LEFT_Y + new_row * BLOCK_SIZE + (BLOCK_SIZE - ZOMBIE_SIZE) / 2;
		Zombie* new_zombie = new Zombie(ZOMBIES_HP, ZOMBIES_DAMAGE, new_row, 16, new_x, new_y);
		zombies_list.push_back(new_zombie);
	}

	void AddZombie(int delta_time) {
		
		timer += delta_time;
		wave_timer += delta_time;
		is_big_wave = false;
		int num = zombies_list.size();

		if (wave_timer >= ZOMBIE_WAVE_INTERVAL && num == 0) {
			wave++;
			wave_timer = 0;
			zombie_count = 0;

			if ((wave - 1) % 3 == 0) {
				normal_wave_capcity += ratio;
			}

			if ((wave) % 10 == 0) {
				is_big_wave = true;
			}

			capcity = is_big_wave ? big_wave_capcity : normal_wave_capcity;
			std::cout << wave << " " << num << " " << capcity << "\n";
		}

		if (timer >= interval && zombie_count < capcity) {
			NewZombie();
			zombie_count++;
			timer = 0;
		}

	}

	void Update(int delta_time) {

		AddZombie(delta_time);
		for (int i = 0; i < zombies_list.size(); i++) {
			Zombie* temp = zombies_list[i];

			if (temp->x + temp->width <= MAP_LEFT_X) {
				temp->is_end = true;
			}

			if (temp->is_end) {
				std::swap(zombies_list[i], zombies_list.back());
				zombies_list.pop_back();
				delete temp;
				continue;
			}
		}

		if (wave == total_wave && zombies_list.size() == 0) {
			is_game_end = true;
		}
	}

	void Draw() {
		for (int i = 0; i < zombies_list.size(); i++) {
			zombies_list[i]->Draw(TIME_INTERVAL);
		}
		double progress = 1.0 * (wave - 1) / total_wave;
		progress_bar.Draw(progress);
	}

private:
	int total_wave;
	int interval;
	int zombie_count = 0;
	int capcity = 1;
	int wave = 1;
	int normal_wave_capcity = 1;
	int big_wave_capcity = 10;
	int timer = 0;
	int wave_timer = 0;
	bool is_big_wave = false;
};