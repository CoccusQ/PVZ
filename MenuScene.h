#pragma once
#include <iostream>
#include "Constant.h"
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"

extern SceneManager scene_manager;
extern IMAGE img_startmenu;
extern IMAGE img_startbutton_idle;
extern IMAGE img_startbutton_hover;
extern IMAGE img_startbutton_clicked;

class MenuScene :public Scene {
public:
	MenuScene() {
		//≥ı ºªØ∞¥≈•
		start_btn.set_x(START_BUTTON_X);
		start_btn.set_y(START_BUTTON_Y);
		start_btn.set_width(START_BUTTON_WIDTH);
		start_btn.set_height(START_BUTTON_HEIGHT);
		start_btn.set_image(&img_startbutton_idle, &img_startbutton_hover, &img_startbutton_clicked);
	}

	void on_enter() {
		
	}

	void on_draw() {
		putimage(0, 0, &img_startmenu);
		start_btn.Draw();
	}

	void on_input(const ExMessage& msg) {
		start_btn.ProcessEvent(msg, is_game_start);
		if (is_game_start) {
			scene_manager.switch_to(SceneManager::SceneType::Level);
		}
	}

	void on_exit() {
		
	}

private:
	StartButton start_btn;
	bool is_game_start = false;
};