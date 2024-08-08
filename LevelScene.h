#pragma once
#include <vector>
#include <iostream>
#include "Scene.h"
#include "SceneManager.h"
#include "ZombiesLayer.h"
#include "Level.h"

extern SceneManager scene_manager;
extern ZombiesLayer zombies_layer;
extern IMAGE img_select_level;
extern IMAGE img_level_1_1_idle;
extern IMAGE img_level_1_1_hover;
//extern IMAGE img_level_1_1_clicked;

class LevelScene :public Scene {
public:
	bool selected = false;

public:
	LevelScene() {
		Level* new_level = new Level();
		new_level->level_id = 0;
		new_level->flag_num = 1;
		new_level->interval = ZOMBIE_EMERGE_INTERVAL;
		new_level->ratio = 1;
		new_level->set_image(&img_level_1_1_idle, &img_level_1_1_hover, &img_level_1_1_idle);
		new_level->set_x(100);
		new_level->set_y(150);
		new_level->set_width(LEVEL_CARD_SIZE);
		new_level->set_height(LEVEL_CARD_SIZE);
		level_list.push_back(new_level);
	}

	void on_enter() {
		std::cout << "enter level select scene\n";
	}

	void on_update(int delta_time) {
		if (selected) {
			scene_manager.switch_to(SceneManager::SceneType::Game);
			selected = false;
		}
	}

	void on_draw() {
		putimage(0, 0, &img_select_level);
		for (int i = 0; i < level_list.size(); i++) {
			level_list[i]->Draw();
		}
	}

	void on_input(const ExMessage& msg) {
		for (int i = 0; i < level_list.size(); i++) {
			Level* temp = level_list[i];
			temp->ProcessEvent(msg, selected);
			if (temp->is_chosen) {
				zombies_layer.set_total_flag(temp->flag_num);
				zombies_layer.set_ratio(temp->ratio);
				zombies_layer.set_interval(temp->interval);
				zombies_layer.set_progress_bar(temp->flag_num);
				temp->is_chosen = false;
			}
		}
	}

	void on_exit() {
		std::cout << "exit level select scene\n";
	}

private:
	std::vector<Level*> level_list;
};