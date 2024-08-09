#pragma once
#include <iostream>
#include "Scene.h"
#include "PlantsLayer.h"
#include "ZombiesLayer.h"
#include "SunlightLayer.h"
#include "BulletLayer.h"
#include "LawnMowerLayer.h"
#include "CardSlot.h"

extern PlantsLayer plants_layer;
extern ZombiesLayer zombies_layer;
extern SunlightLayer sunlight_layer;
extern BulletLayer bullet_layer;
extern LawnMowerLayer lawn_mower_layer;
extern CardSlot card_slot;
extern IMAGE img_game_background;
extern IMAGE img_lose;
extern IMAGE img_win;
extern IMAGE img_menu;
extern IMAGE img_dark;

class GameScene :public Scene {
public:
	bool is_game_end = false;
	bool is_pause = false;

public:
	
	void on_enter() {
		std::cout << "enter game scene\n";
		lawn_mower_layer.set_lawn_mower();  //设置小推车
		is_game_end = false;
		is_pause = false;
	}

	void on_update(int delta_time) {
		if (is_pause) {
			//std::cout << "pause\n";
			return;
		}
		plants_layer.Update(zombies_layer, delta_time);
		zombies_layer.Update(delta_time);
		bullet_layer.Update();
		lawn_mower_layer.Update();
		card_slot.Update(delta_time);
		sunlight_layer.Update();
		if (zombies_layer.is_game_end) {
			is_game_end = true;
		}
	}

	void on_draw() {
		putimage(0, 0, &img_game_background);
		plants_layer.Draw();
		zombies_layer.Draw();
		lawn_mower_layer.Draw();
		bullet_layer.Draw();
		card_slot.Draw();
		sunlight_layer.Draw();
		card_slot.draw_if_chosen();

		if (is_pause) {
			pause();
		}

		if (zombies_layer.is_lose) {
			lose();
		}
		else if (zombies_layer.is_win) {
			win();
		}

	}

	void on_input(const ExMessage& msg) {
		card_slot.on_input(msg);

		if (is_game_end) {

			if (msg.message == WM_KEYUP) {
				scene_manager.switch_to(SceneManager::SceneType::Level);
			}

		}
		else if (msg.message == WM_KEYUP && msg.vkcode == VK_SPACE) {
			is_pause = is_pause ^ true;
			//std::cout << is_pause << " pause\n";
		}
	}

	void on_exit() {
		plants_layer.reset();
		sunlight_layer.reset();
		bullet_layer.reset();
		zombies_layer.reset();
		lawn_mower_layer.reset();
		std::cout << "exit game scene\n";
	}

private:
	
	void lose() {
		putimage_t(0, 0, &img_lose);
		setbkmode(TRANSPARENT);
		settextstyle(60, 0, _T("IPix"));
		RECT r = { 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT };
		RECT r_shadow = { 0 + 2, WINDOW_HEIGHT / 2 + 2, WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2 };
		settextcolor(LIGHTGRAY);
		drawtext(_T("- Press any key to continue -"), &r_shadow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextcolor(WHITE);
		drawtext(_T("- Press any key to continue -"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	void win() {
		putimage_t(0, 0, &img_win);
		setbkmode(TRANSPARENT);
		
		RECT r1 = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2 };
		RECT r1_shadow = { 3, 3, WINDOW_WIDTH + 3, WINDOW_HEIGHT / 2 + 3 };
		RECT r = { 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT };
		RECT r_shadow = { 0 + 2, WINDOW_HEIGHT / 2 + 2, WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2 };

		settextstyle(60, 0, _T("IPix"));
		settextcolor(LIGHTGRAY);
		drawtext(_T("- Press any key to continue -"), &r_shadow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextcolor(WHITE);
		drawtext(_T("- Press any key to continue -"), &r_shadow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		settextstyle(150, 0, _T("IPix"));
		settextcolor(LIGHTGRAY);
		drawtext(_T("You Win!"), &r1_shadow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextcolor(WHITE);
		drawtext(_T("You Win!"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	void pause() {
		putimage_t(0, 0, &img_dark);
		putimage_t(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3, &img_menu);
		setbkmode(TRANSPARENT);
		RECT r = { WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3,WINDOW_WIDTH / 3 * 2,WINDOW_HEIGHT / 9 * 4 };
		RECT r1 = { WINDOW_WIDTH / 3 + 3, WINDOW_HEIGHT / 3 + 3,WINDOW_WIDTH / 3 * 2 + 3,WINDOW_HEIGHT / 9 * 4 + 3 };
		settextstyle(45, 0, _T("IPix"));
		settextcolor(BLACK);
		drawtext(_T("Pause"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextcolor(WHITE);
		drawtext(_T("Pause"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

};