#pragma once
#include <iostream>
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"

extern SceneManager scene_manager;
extern IMAGE img_startmenu;
extern StartButton start_btn;

class MenuScene :public Scene {
public:
	void on_enter() {
		std::cout << "进入主菜单\n";
	}

	void on_draw() {
		putimage(0, 0, &img_startmenu);
		start_btn.Draw();
	}

	void on_input(const ExMessage& msg) {
		start_btn.ProcessEvent(msg, is_game_start);
		if (is_game_start) {
			scene_manager.switch_to(SceneManager::SceneType::Game);
		}
	}

	void on_exit() {
		std::cout << "退出主菜单\n";
	}

private:
	bool is_game_start = false;
};