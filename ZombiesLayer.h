#pragma once
#include <vector>
#include <string.h>
#include "Zombies.h"
#include "ProgressBar.h"

extern IMAGE img_progress_bar_1flag;

class ZombiesLayer {
public:
	std::vector<Zombie*> zombies_list;
	ProgressBar progress_bar;
	int ratio = 1;//出怪倍数；
	bool is_game_end = false;
	bool is_win = false;
	bool is_lose = false;
	bool stop = false;

public:
	ZombiesLayer() {};

	ZombiesLayer(std::string game_level_type , int total_wave = 10 , int ratio = 1, int interval = ZOMBIE_EMERGE_INTERVAL)
		:total_wave(total_wave), ratio(ratio), interval(interval),
		progress_bar(game_level_type, PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT) {

	}

	void set_progress_bar(int flag_num) {
		progress_bar.set_size(PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT);
		switch (flag_num) {
		case 1:
			progress_bar.set_img(&img_progress_bar_1flag);
			break;
		}
	}

	void set_total_flag(int flag_num) {
		this->total_flag = flag_num;
		this->total_wave = flag_num * 10;
		set_progress_bar(flag_num);
	}

	void set_interval(int interval) {
		this->interval = interval;
	}

	//设置出怪倍数
	void set_ratio(int ratio) {
		this->ratio = ratio;
	}

	void NewZombie() {
		int new_row = rand() % 8;
		int new_x = WINDOW_WIDTH - ZOMBIE_SIZE / 2;
		int new_y = MAP_LEFT_Y + new_row * BLOCK_SIZE + (BLOCK_SIZE - ZOMBIE_SIZE) / 2;//- BLOCK_SIZE / 6;
		Zombie* new_zombie = new Zombie(ZOMBIES_HP, ZOMBIES_DAMAGE, new_row, 16, new_x, new_y);
		zombies_list.push_back(new_zombie);
	}

	void AddZombie(int delta_time) {
		//当前波数达到总波数 且 场上无僵尸，游戏结束
		if (cur_wave == total_wave && zombies_list.size() <= 0) {
			stop = true;
			is_win = true;
			is_game_end = true;
			return;
		}

		//增加计时器时间
		timer += delta_time;
		wave_timer += delta_time;


		//如果每一小波的时间大于波间隔 且 场上僵尸总数为零，进入下一小波
		if (wave_timer >= ZOMBIE_WAVE_INTERVAL && zombies_list.size() <= 0) {
			cur_wave++;
			wave_timer = 0;
			zombie_count = 0;
			is_flag_wave = false;

			//每三个小波，僵尸容量增加
			if ((cur_wave - 1) % 3 == 0) {
				normal_wave_capcity += ratio;
			}

			//每十个小波，出现一面旗帜（一大波僵尸来袭）
			if ((cur_wave) % 10 == 0) {
				is_flag_wave = true;
				flag_wave_capcity += ratio * 2;
				//cur_flag++;
			}

			capcity = is_flag_wave ? flag_wave_capcity : normal_wave_capcity;
			std::cout << "Wave: " << cur_wave << "  Zombie Amount: " << capcity << "\n";
		}

		//游戏未停止 && 计时器时间大于等于出怪间隔 && 出怪数量小于僵尸容量
		if (!stop && timer >= interval && zombie_count < capcity) {
			NewZombie();
			zombie_count++;
			timer = 0;
		}

	}

	void Update(int delta_time) {	
		AddZombie(delta_time);
		for (int i = 0; i < zombies_list.size(); i++) {
			Zombie* temp = zombies_list[i];
			temp->Update(delta_time);

			//僵尸进入后方
			if (temp->x + temp->width <= MAP_LEFT_X) {
				temp->is_end = true;
				stop = true;
				is_lose = true;
				is_game_end = true;
			}

			if (temp->is_end) {
				std::swap(zombies_list[i], zombies_list.back());
				zombies_list.pop_back();
				delete temp;
				continue;
			}
		}
		/*
		if (cur_wave == total_wave && zombies_list.size() <= 0) {
			is_game_end = true;
		}
		*/
	}

	void Draw() {
		for (int i = 0; i < zombies_list.size(); i++) {
			zombies_list[i]->Draw(TIME_INTERVAL);
		}
		double progress = 1.0 * (cur_wave - 1) / total_wave;
		progress_bar.Draw(progress);
	}

	void clear_all_zombies() {
		while (zombies_list.size() > 0) {
			Zombie* temp = zombies_list[zombies_list.size() - 1];
			zombies_list.pop_back();
			delete temp;
		}
	}

	void reset() {
		total_wave = 0;
		total_flag = 0;
		zombie_count = 0;
		is_flag_wave = false;
		capcity = 0;
		cur_wave = 0;
		timer = 0;
		wave_timer = 0;
		normal_wave_capcity = 0;
		flag_wave_capcity = 8;
		is_win = false;
		is_lose = false;
		is_game_end = false;
		stop = false;
		clear_all_zombies();
	}

private:
	int total_wave;
	int total_flag = 1;
	int interval = ZOMBIE_EMERGE_INTERVAL;
	int zombie_count = 0;
	int capcity = 0;
	int cur_wave = 0;
	int normal_wave_capcity = 0;
	int flag_wave_capcity = 8;
	int timer = 0;
	int wave_timer = 0;
	bool is_flag_wave = false;
};